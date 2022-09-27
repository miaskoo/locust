#include "boardScene.h"
#include "factoryAction.h"
#include "factoryEntity.h"
#include "clickComponent.h"

void boardScene::swapCallback(std::shared_ptr<entity> caller, swapDirection direction) {
    swapChip(controller.getChipById(callerToId[caller]), direction);
}

void boardScene::swapChip(chip* caller, swapDirection direction) {
    setClickableChip(false);
    auto receiver = getChipFromDirection(caller, direction);
    if (!receiver) {
        return;
    }
    controller.swapChip(caller->getBindId(), receiver->getBindId());
    swappingChips.first = caller;
    swappingChips.second = receiver;
    
    addAction(factoryAction::createDelayAction(150, [this](){
        auto first = getMatch3Chip(swappingChips.first);
        auto second = getMatch3Chip(swappingChips.second);
        if (!first.empty()) {
            for (auto& currentChip : first) {
                controller.removeChip(currentChip->getBindId());
            }
            stable = false;
        }
        if (!second.empty()) {
            for (auto& currentChip : first) {
                controller.removeChip(currentChip->getBindId());
            }
            stable = false;
        }
        if (stable) {
            controller.swapChip(swappingChips.first->getBindId(), swappingChips.second->getBindId());
            addAction(factoryAction::createDelayAction(150, [this](){
                setClickableChip(true);
            }));
        }
        else {
            tryFalling();
        }
        swappingChips = {nullptr, nullptr};
    }));
}

void boardScene::update(float dt) {
    node::update(dt);
    if (!stable) {
        stable = !isFalling;
    }
}

void boardScene::init(unsigned int w, unsigned int h) {
    if (isInit) {
        return;
    }
    isInit = true;
    
    auto size = w*h;
    buttons.resize(size);
    for (auto aW = 0U; aW < w; aW++) {
        for (auto aH = 0U; aH < h; aH++) {
            auto result = factoryEntity::createButton();
            callerToId[result] = {aW, aH};
            result->getComponent<swapComponent>()->setSwapCallback(std::bind(&boardScene::swapCallback, this, std::placeholders::_1, std::placeholders::_2));
            buttons.push_back(result);
        }
    }
    
    std::vector<std::vector<std::shared_ptr<entity>>> chipSprite;
    chipSprite.resize(w);
    for (auto aW = 0U; aW < w; aW++) {
        chipSprite[aW].reserve(h);
        for (auto aH = 0U; aH < h; aH++) {
            auto spriteObject = factoryEntity::createSprite();
            chipSprite[aW].push_back(spriteObject);
            addChild(spriteObject);
        }
    }
    
    controller.initModel(w, h);
    controller.initView(chipSprite);
    widthBoard = w;
    heightBoard = h;
}

void boardScene::startGame() {
    unsigned int maxColor = 4;
    std::vector<std::vector<chipColor>> colors;
    colors.resize(widthBoard);
    for (auto aW = 0U; aW < widthBoard; aW++) {
        colors[aW].reserve(heightBoard);
        for (auto aH = 0U; aH < heightBoard; aH++) {
            colors[aW].push_back(static_cast<chipColor>(rand()%maxColor));
        }
    }
    controller.initNewGame(colors);
}

void boardScene::tryFalling() {
    
}

void boardScene::tryChipFalling(chip *caller) {
    
}

void boardScene::setClickableChip(bool value) {
    
}

std::vector<chip*> boardScene::getMatch3Chip(chip* caller) {
    return {};
}

chip* boardScene::getChipFromDirection(chip* caller, swapDirection direction) {
    return nullptr;
}
