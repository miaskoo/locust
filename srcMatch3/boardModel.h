#pragma once
#include "chip.h"
#include "chipPlace.h"
#include <vector>

class boardModel {
public:
    boardModel() = default;
    ~boardModel() = default;
    
    void init(unsigned int w, unsigned int h);
    void setChipFree(chip* aChip);
    void setChipBusy(chip* aChip);
    void clearFree();
    
    chip* getChip(const std::pair<unsigned int, unsigned int>& chipId);
    chipPlace* getChipPlace(const std::pair<unsigned int, unsigned int>& chipPlaceId);
    chip* getFreeChip();
    const std::vector<std::vector<chipPlace>>& getChipPlacePool() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
private:
    std::vector<std::vector<chip>> chipPool;
    std::vector<chip*> freeChipPool;
    std::vector<std::vector<chipPlace>> chipPlacePool;
};
