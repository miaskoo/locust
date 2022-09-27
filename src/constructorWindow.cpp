#include "constructorWindow.h"

#include "renderComponent.h"
#include "transformComponent.h"
#include "clickComponent.h"
#include "colorComponent.h"
#include "scene.h"

#include "renderSystem.h"
#include "mouseSystem.h"

#include "factoryEntity.h"

#include <stdio.h>
#include <chrono>
#include <ctime>
#include <thread>

#ifdef MACOS
#include "GLUT/glut.h"
#else
#include "glew/glew.h"
#include "freeglut/freeglut.h"
#endif

void constructorWindow::initWindow(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(screenW,screenH);
    renderSystem::getInstance()->setWindowSize(screenW, screenH);
    srand(time(0U));
    glutCreateWindow("test");
#ifndef MACOS
    glewInit();
#endif
}

void constructorWindow::initTextures(const std::vector<std::string>& dirs) {
    cTexture.init(dirs);
}

void constructorWindow::updateWindow() {
    long long time = 0;
    float dt = 0.0f;
    
    while(true) {
        auto lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
        if (fpsLabel) {
            fpsLabel->getComponent<labelComponent>()->setText("Fps: " + std::to_string(lastFps));
        }
        if (timeLabel) {
            timeLabel->getComponent<labelComponent>()->setText("Time: " + std::to_string(time / 1000.f));
        }
        if (mousePosLabel) {
            mousePosLabel->getComponent<labelComponent>()->setText("X: " + std::to_string(mouseX.load()) + " Y: " + std::to_string(mouseY.load()));
        }
        if (dt > 0.f) {
            updateScene(dt);
        }
        if (swapLine) {
            if (auto supervisedEntity = mouseSystem::getInstance()->getSupervisedEntity()) {
                renderSystem::getInstance()->registerEntity(swapLine.get());
                auto mouseSystemInstane = mouseSystem::getInstance();
                if (auto component = supervisedEntity->getComponent<clickComponent>()) {
                    if (component->getTypeClickComponent() == typeClickComponent::SWAP) {
                        auto transform = supervisedEntity->getComponent<transformComponent>();
                        auto pos = transform->getCashPos() + transform->getCashSize() / 2.f;
                        swapLine->setPos(pos);
                        auto mousePos = vec3f(mouseSystemInstane->getMousePosX(), mouseSystemInstane->getMousePosY());
                        auto sizeX = std::abs(std::abs(mousePos.x()) - std::abs(pos.x()));
                        auto sizeY = std::abs(std::abs(mousePos.y()) - std::abs(pos.y()));
                        auto size = vec3f(2, sizeX + sizeY);
                        swapLine->setSize(size);
                        auto angle = vec3f::getAngle(pos, mousePos);
                        swapLine->setRotate(0, 0, angle);
                    }
                }
            }
            else {
                renderSystem::getInstance()->unregisterEntity(swapLine.get());
                swapLine->setSize(0, 0);
            }
        }
        
        
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dt = currentTime - lastTime;
        if (dt < minDtUpdateMs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(minDtUpdateMs - dt)));
            dt = minDtUpdateMs;
        }
        time+= dt;
    }
}

void constructorWindow::updateScene(float dt) {
    auto clickState = click.load();
    mouseSystem::getInstance()->setMouseState(clickState);
    mouseSystem::getInstance()->update(mouseX.load(), mouseY.load());
    if (clickState == stateMouse::CLICK_OUT) {
        click.store(stateMouse::IDLE);
    }
    mainScene->update(dt);
    if (cashDirty.load()) {
        return;
    }
    bool dirty = false;
    mainScene->checkDirty(mainScene.get(), dirty);
    if (dirty) {
        mainScene->updateCash(getCashIdx(typeCash::FREE), getCashIdx(typeCash::BUSY));
        switchCash.store(!switchCash.load());
        cashDirty.store(true);
    }
}

size_t constructorWindow::getCashIdx(typeCash type) {
    if (switchCash.load()) {
        if (type == typeCash::FREE) {
            return static_cast<size_t>(typeCash::BUSY);
        }
        return static_cast<size_t>(typeCash::FREE);
    }
    return static_cast<size_t>(type);
}

void constructorWindow::renderScene() {
    if (currentFps < lockFps) {
        if (cashDirty.load()) {
            cashDirty.store(false);
        }
        renderSystem::getInstance()->update(getCashIdx(typeCash::BUSY));
        currentFps++;
    }
}

void constructorWindow::idleScene() {
    auto currentIdleTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto dt = currentIdleTime - lastIdleTime;
    if (dt < minDtFpsMs) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(minDtFpsMs - dt)));
        dt = minDtFpsMs;
    }
    
    lastTimeCheckFps += dt;
    if (lastTimeCheckFps >= 1000) {
        lastTimeCheckFps = 0;
        lastFps = currentFps;
        currentFps = 0;
    }
    glutPostWindowRedisplay(currentWindow);
    lastIdleTime = currentIdleTime;
}

void constructorWindow::clickWindow(int button, int state, int x, int y) {
    constructorWindow::getInstance()->setMousePos(x, y);
    click.store(state == 0 ? stateMouse::CLICK : stateMouse::CLICK_OUT);
}

void glutPassiveMotionFuncForwarder(int x, int y) {
    constructorWindow::getInstance()->setMousePos(x, y);
}

void constructorWindow::startUpdateThread() {
    std::thread updateScene([](){
        getInstance()->updateWindow();
    });
    updateScene.detach();
}

void constructorWindow::startMainLoop() {
    glutMainLoop();
}

void constructorWindow::setMousePos(int x, int y) {
    mouseX.store(x);
    mouseY.store(y);
}

void glutDisplayFuncForwarder() {
    constructorWindow::getInstance()->renderScene();
}

void glutIdleFuncForwarder() {
    constructorWindow::getInstance()->idleScene();
}

void glutMouseFuncForwarder(int button, int state, int x, int y) {
    constructorWindow::getInstance()->clickWindow(button, state, x, y);
}

void constructorWindow::initGlutFunc() {
    glutDisplayFunc(glutDisplayFuncForwarder);
    glutIdleFunc(glutIdleFuncForwarder);
    glutMouseFunc(glutMouseFuncForwarder);
    glutPassiveMotionFunc(glutPassiveMotionFuncForwarder);
    glutMotionFunc(glutPassiveMotionFuncForwarder);
    currentWindow = glutGetWindow();
}

int constructorWindow::getScreenW() {
    return screenW;
}

int constructorWindow::getScreenH() {
    return screenH;
}

constructorWindow* constructorWindow::getInstance() {
    if (!instance) {
        instance = new constructorWindow();
    }
    return instance;
}

void constructorWindow::cleanup() {
    delete instance;
    instance = nullptr;
}

void constructorWindow::setGameScene(std::shared_ptr<scene> aScene) {
    mainScene = aScene;
}

void constructorWindow::createInfoNode() {
    if (!mainScene || uiNode) {
        return;
    }
    uiNode = factoryEntity::createNode();
    uiNode->setPos(-200.f,-100.f);
    uiNode->setAnchor(1.f, 1.f);
    fpsLabel = factoryEntity::createLabel();
    timeLabel = factoryEntity::createLabel();
    timeLabel->setPos(0.f,-20.f);
    mousePosLabel = factoryEntity::createLabel();
    mousePosLabel->setPos(0.f, 20.f);
    mainScene->addChild(uiNode);

    fpsLabel->getTransformComponent()->setPivot(tPivot::x, 1.f);
    timeLabel->getTransformComponent()->setPivot(tPivot::x, 1.f);
    mousePosLabel->getTransformComponent()->setPivot(tPivot::x, 1.f);

    uiNode->addChild(fpsLabel);
    uiNode->addChild(timeLabel);
    uiNode->addChild(mousePosLabel);
    
    swapLine = factoryEntity::createSprite("whitePixel.png");
    swapLine->setAnchor(vec2f(0.0f,0.0f));
    swapLine->setPivot(vec2f(1.0f,1.0f));
    swapLine->getComponent<colorComponent>()->setAlphaMode(false);
    mainScene->addChild(swapLine);
}

void constructorWindow::destroyInfoNode() {
    if (mainScene) {
        mainScene->markDelete();
    }
    uiNode.reset();
    fpsLabel.reset();
    timeLabel.reset();
    mousePosLabel.reset();
}

bufferController* constructorWindow::getBufferController() {
    return &cBuffer;
}

textureController* constructorWindow::getTextureController() {
    return &cTexture;
}
