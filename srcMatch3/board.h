#pragma once
#include "node.h"
#include "boardController.h"
#include <set>

enum class swapDirection {LEFT, RIGTH, TOP, BOT};

class board : public node {
public:
    board() = default;
    ~board() = default;
    
    void swapChip(chip* caller, swapDirection direction);
    virtual void update(float dt);
private:
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
};
