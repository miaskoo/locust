#include "board.h"
#include "factoryAction.h"

void board::swapChip(chip* caller, swapDirection direction) {
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

void board::update(float dt) {
    node::update(dt);
    if (!stable) {
        stable = !isFalling;
    }
}

void board::tryFalling() {
    
}

void board::tryChipFalling(chip *caller) {
    
}

void board::setClickableChip(bool value) {
    
}

std::vector<chip*> board::getMatch3Chip(chip* caller) {
    return {};
}

chip* board::getChipFromDirection(chip* caller, swapDirection direction) {
    return nullptr;
}
