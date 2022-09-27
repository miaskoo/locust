#include "boardScene.h"
#include "factoryAction.h"
#include "factoryEntity.h"
#include "clickComponent.h"
#include "constructorWindow.h"
#include "colorComponent.h"

void boardScene::swapCallback(std::shared_ptr<entity> caller, swapDirection direction) {
    auto callerChipPlace = boardController.getChipPlaceById(callerToId[caller]);
    auto receiverChipPlace = boardController.getChipPlaceByDirection(callerChipPlace->getBindedChip(), direction);
    if (receiverChipPlace) {
        boardController.setLock(true);
        boardController.swapChip(callerChipPlace->getBindedChip(), receiverChipPlace->getBindedChip());
    }
   
}

void boardScene::update(float dt) {
    scene::update(dt);
    if (boardController.isLock()) {
        if (boardController.isHaveAnim()) {
            return;
        }
        boardController.updateView();
        if (boardController.boardIsStable()) {
            boardController.setLock(false);
            newState = boardController.isHaveSwapMove() ? newState : boardSceneState::END;
        }
        else {
            boardController.updateModel();
        }
    }
    else {
        if (currentState != newState) {
            switch (newState) {
                case boardSceneState::MAIN: {
                    destroyMenu();
                    initMainMenu();
                    break;
                }
                case boardSceneState::END: {
                    boardController.deattachView();
                    boardController.hideBoard();
                    initEndGameMenu();
                    break;
                }
                case boardSceneState::GAME: {
                    destroyMenu();
                    boardController.resetBoard();
                    boardController.attachViewToEntity(wThis.lock());
                    boardController.showBoard();
                }
            }
            newState = currentState;
        }
        
    }
}

void boardScene::init(unsigned int w, unsigned int h, vec2f chipSize) {
    if (isInit) {
        return;
    }
    isInit = true;
    
    boardController.init(w, h, chipSize, std::bind(&boardScene::swapCallback, this, std::placeholders::_1, std::placeholders::_2));
    auto chipButtons = boardController.getChipButtons();
    for (int aW = 0; aW < w; aW++) {
        for (int aH = 0; aH < h; aH++) {
            callerToId[chipButtons[aW][aH]] = {aW, aH};
        }
    }
}

void boardScene::startGame() {
    initMainMenu();
}

void boardScene::initMainMenu() {
    menu = factoryEntity::createNode();
    addChild(menu);
    menu->setSize(constructorWindow::getInstance()->getScreenW(), constructorWindow::getInstance()->getScreenH());
    
    auto buttonStartGame = factoryEntity::createButton();
    buttonStartGame->getComponent<buttonComponent>()->setClickCallback([this](auto object) {
        newState = boardSceneState::GAME;
    });
    buttonStartGame->setSize(200, 100);
    buttonStartGame->setAnchor(vec2f(0.5f, 0.3f));
    menu->addChild(buttonStartGame);
    
    color4b blackColor = {0,0,0,255};
    
    auto labelStartGame = factoryEntity::createLabel("Start Game");
    labelStartGame->getComponent<colorComponent>()->setColor(blackColor);
    buttonStartGame->addChild(labelStartGame);
    
    auto buttonExitGame = factoryEntity::createButton();
    buttonExitGame->getComponent<buttonComponent>()->setClickCallback([](auto) {
        std::exit(0);
    });
    buttonExitGame->setSize(200, 100);
    buttonExitGame->setAnchor(vec2f(0.5f, 0.7f));
    menu->addChild(buttonExitGame);

    auto labelExitGame = factoryEntity::createLabel("Exit Game");
    labelExitGame->getComponent<colorComponent>()->setColor(blackColor);
    buttonExitGame->addChild(labelExitGame);
}

void boardScene::destroyMenu() {
    menu->markDelete();
    menu.reset();
}

void boardScene::initEndGameMenu() {
    menu = factoryEntity::createNode();
    addChild(menu);
    menu->setSize(constructorWindow::getInstance()->getScreenW(), constructorWindow::getInstance()->getScreenH());
    
    auto buttonStartGame = factoryEntity::createButton();
    buttonStartGame->getComponent<buttonComponent>()->setClickCallback([this](auto object) {
        newState = boardSceneState::GAME;
    });
    buttonStartGame->setSize(200, 100);
    buttonStartGame->setAnchor(vec2f(0.5f, 0.3f));
    menu->addChild(buttonStartGame);
    
    color4b blackColor = {0,0,0,255};
    
    auto labelStartGame = factoryEntity::createLabel("Restart Game");
    labelStartGame->getComponent<colorComponent>()->setColor(blackColor);
    buttonStartGame->addChild(labelStartGame);
    
    auto buttonExitGame = factoryEntity::createButton();
    buttonExitGame->getComponent<buttonComponent>()->setClickCallback([this](auto) {
        std::exit(0);
    });
    buttonExitGame->setSize(200, 100);
    buttonExitGame->setAnchor(vec2f(0.5f, 0.7f));
    menu->addChild(buttonExitGame);

    auto labelExitGame = factoryEntity::createLabel("Exit Game");
    labelExitGame->getComponent<colorComponent>()->setColor(blackColor);
    buttonExitGame->addChild(labelExitGame);
}
