#include "boardScene.h"
#include "factoryAction.h"
#include "factoryEntity.h"
#include "clickComponent.h"

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
        }
        else {
            boardController.updateModel();
        }
    }
}

void boardScene::init(unsigned int w, unsigned int h, vec2f chipSize) {
    if (isInit) {
        return;
    }
    isInit = true;
    
    boardController.init(w, h, chipSize, std::bind(&boardScene::swapCallback, this, std::placeholders::_1, std::placeholders::_2));
    boardController.attachViewToEntity(getWeakPtr().lock());
    widthBoard = w;
    heightBoard = h;
    auto chipButtons = boardController.getChipButtons();
    for (int aW = 0; aW < w; aW++) {
        for (int aH = 0; aH < h; aH++) {
            callerToId[chipButtons[aW][aH]] = {aW, aH};
        }
    }
}

void boardScene::startGame() {
    boardController.resetBoard();
}
