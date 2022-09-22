#include "renderSystem.h"
#include "entity.h"
#include "colorComponent.h"
#include "textureComponent.h"
#include "renderComponent.h"
#include "transformComponent.h"

#ifdef MACOS
#include "GLUT/glut.h"
#else
#include "freeglut/glut.h"
#endif
#include "glFunctional.h"

void renderSystem::setOrthographic() {
    if (ortho) {
        return;
    }
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenW, screenH, 0);
    glMatrixMode(GL_MODELVIEW);
    ortho = true;
}

void renderSystem::setPerspective() {
    if (!ortho) {
        return;
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    ortho = false;
}

void renderSystem::updateWindowSize() {
    setPerspective();
    
    float ratio =  screenW * 1.0 / screenH;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, screenW, screenH);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(
        0.0, 0.0, 10.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);
}

void renderSystem::update(size_t cashIdx) {
    if (dirty) {
        sortEntityForRender();
        dirty = false;
    }
    if (windowSizeDirty) {
        updateWindowSize();
        windowSizeDirty = false;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto object : objects) {
        if (object->getDimension() == dimension::TWO) {
           setOrthographic();
        }
        else {
           setPerspective();
        }
        renderEntity(object, cashIdx);
    }
    
    glutSwapBuffers();
}

void renderSystem::renderEntity(entity* object, size_t cashIdx) {
    auto cash = object->getCash(cashIdx);
    
    bindColor(cash->getComponent<colorComponent>());
    bindTexture(cash->getComponent<textureComponent>());
    bindMatrix(cash->getComponent<transformComponent>());
    
    auto component = cash->getComponent<renderComponent>();
    switch (component->getRenderType()) {
        case typeRenderComponent::SPRITE: {
            renderSprite();
            break;
        }
        case typeRenderComponent::BUFFER: {
            auto castComponent = static_cast<bufferComponent*>(component);
            renderBuffer(castComponent->getBuffIdx(), castComponent->getBuffSize(), castComponent->isCullFaceMode());
            break;
        }
        case typeRenderComponent::LABEL: {
            auto castComponent = static_cast<labelComponent*>(component);
            renderLabel(castComponent->getText(), castComponent->getFont());
            break;
        }
        default: {
            break;
        }
    }
    unbindMatrix();
    unbindTexture();
    unbindColor();
}

void renderSystem::bindColor(colorComponent *component) {
    if (!component) {
        return;
    }
    auto color = component->getColor();
    if (component->isAlphaMode()) {
        glForwarder::setAlphaMode(true);
        glForwarder::setColor4(color[0], color[1], color[2], color[3]);
    }
    else {
        glForwarder::setColor3(color[0], color[1], color[2]);
    }
}

void renderSystem::unbindColor() {
    glForwarder::setColor4(MAX_COLOR, MAX_COLOR, MAX_COLOR, MAX_COLOR);
}

void renderSystem::bindTexture(textureComponent *component) {
    if (!component) {
        return;
    }
    glForwarder::bind2DTexture(component->getTexIdx());
    glForwarder::bindShaderProgram(component->getShaderIdx());
}

void renderSystem::unbindTexture() {
    glForwarder::unbindShaderProgram();
    glForwarder::unbind2DTexture();
}

void renderSystem::renderBuffer(size_t buffIdx, size_t buffSize, bool cullfaceMode) {
    glForwarder::bindVertexArray(buffIdx);
    glForwarder::setCullfaceMode(cullfaceMode);
    glForwarder::drawTriangleElements(buffSize);
    glForwarder::setCullfaceMode(false);
    glForwarder::unbindVertexArray();
}

void renderSystem::renderLabel(const std::string &text, void *font) {
    glForwarder::drawBitmapText(text.c_str(), text.length(), font);
}

void renderSystem::renderSprite() {
    glForwarder::drawTextureQuad(1);
}

void renderSystem::setWindowSize(int w, int h) {
    screenW = w;
    screenH = h;
    windowSizeDirty = true;
}

void renderSystem::registerEntity(entity* object) {
    if (!object || std::find(objects.begin(), objects.end(), object) != objects.end()) {
        return;
    }
    if (auto component = object->getComponent<renderComponent>()) {
        objects.push_back(object);
    }
    dirty = true;
}

void renderSystem::unregisterEntity(entity* object) {
    auto iter = std::remove_if(objects.begin(), objects.end(), [object](const auto& element){
        return object == element;
    });
    objects.erase(iter);
}

renderSystem* renderSystem::getInstance() {
    if (!instance) {
        instance = new renderSystem();
    }
    return instance;
}

void renderSystem::cleanup() {
    delete instance;
    instance = nullptr;
}


void renderSystem::bindMatrix(transformComponent* component) {
    glPushMatrix();
    auto& pos = component->getCashPos();
    auto rotate = component->getCashRotate();
    auto& size = component->getCashSize();
    glTranslatef(pos[0], pos[1], pos[2]);
    glMultMatrixf(rotate);
    glScalef(size[0], size[1], size[2]);
}

void renderSystem::unbindMatrix() {
    glPopMatrix();
}

void renderSystem::sortEntityForRender() {
    std::sort(objects.begin(), objects.end(), [](const auto& a, const auto& b){
        if (a->isIgnoreSorting()) {
            return true;
        }
        if (b->isIgnoreSorting()) {
            return false;
        }
        return static_cast<size_t>(a->getDimension()) > static_cast<size_t>(b->getDimension());
    });
}
