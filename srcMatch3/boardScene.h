#pragma once
#include "node.h"
#include "boardController.h"
#include <set>
#include <unordered_map>

class boardScene : public node {
public:
    boardScene() = default;
    ~boardScene() = default;
    
    virtual void update(float dt);
    void init(unsigned int w, unsigned int h);
    void startGame();
private:
    void swapCallback(std::shared_ptr<entity> caller, swapDirection direction);
    void swapChip(chip* caller, swapDirection direction);
    
    chip* getChipFromDirection(chip* caller, swapDirection direction);
    std::vector<chip*> getMatch3Chip(chip* caller);
    void setClickableChip(bool value);
    void tryFalling();
    void tryChipFalling(chip* caller);
    
    boardController controller;
    
    std::pair<chip*,chip*> swappingChips {nullptr, nullptr};
    std::set<chip*> fallingChips;
    
    const unsigned int needChipForMatch3 = 3U;
    const swapDirection gravityDirection = swapDirection::BOT;
    
    bool stable = true;
    bool isFalling = false;
    bool isInit = false;
    
    unsigned int widthBoard = 0U;
    unsigned int heightBoard = 0U;
    
    std::vector<std::shared_ptr<entity>> buttons;
    std::unordered_map<std::shared_ptr<entity>, std::pair<unsigned int, unsigned int>> callerToId;
};
