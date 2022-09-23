#pragma once

#include "boardView.h"
#include "boardModel.h"

class boardController {
public:
    boardController() = default;
    ~boardController() = default;
    
    void init(unsigned int w, unsigned int h);
    void initNewGame(const std::vector<std::vector<chipColor>>& colors);
    
    void updateView();
    void swapChip(const std::pair<unsigned int, unsigned int>& from, const std::pair<unsigned int, unsigned int>& to);
    void removeChip(const std::pair<unsigned int, unsigned int>& where);
    void spawnChip(const std::pair<unsigned int, unsigned int>& where);
    
    const std::vector<std::vector<chip>>& getChipPool();
    const std::vector<std::vector<chipPlace>>& getChipPlacePool();
private:
    boardView visual;
    boardModel model;
    
    unsigned int countColor = 0U;
};
