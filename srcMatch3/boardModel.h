#pragma once
#include "chip.h"
#include "chipPlace.h"
#include <vector>
#include <list>
#include <set>
#include "struct.h"

class boardModel {
public:
    boardModel() = default;
    ~boardModel() = default;
    
    void init(unsigned int w, unsigned int h);
    void setDefaultBind();
    void generateBoardColor();
    
    const std::vector<std::vector<chip>>& getChipPool() const;
    const std::vector<std::vector<chipPlace>>& getChipPlacePool() const;
    bool isStable() const;
    
    chip* getChipById(const pairInt& chipId);
    chipPlace* getChipPlaceById(const pairInt& chipPlaceId);
    chipPlace* getChipPlaceFromDirection(chip* object, swapDirection direction);
    
    void swapChipMove(chip* caller, chip* receiver);
    
    void update();
    
    bool isHaveSwapMove();
private:
    pairInt getChipPlaceIdByDirection(chip* object, swapDirection direction);
    
    void addChipToFree(chip* aChip);
    void removeChipFromFree(chip* aChip);
    chip* getFreeChip();
    void clearFree();
    
    void addChipToDirty(chip* dirty);
    void removeСleanСhipsFromDirty();
    
    void swapChips(chip* caller, chip* receiver);
    void fallChip(chipPlace* from, chipPlace* to);
    void createNewChip(chip *what, chipPlace *where);
    void addToFallRow(chip* object);
    
    chipPlace* getPlaceForFall(chip* object);
    chipPlace* getPlaceForCreate(unsigned int column);
    
    void removeChip(const pairInt& where);
    
    void updateDirtyChips();
    void updateFallRows();
    void createNewChips();
    
    bool initMatch3ForDirtyChip(chip* dirtyChip);
    void initFallRow(int column);
    
    std::list<chip*> getMatch3Chips(chip* caller);
    std::list<chip*> getMatch3ChipsByDirection(chip* caller, swapDirection direction);
    
    std::vector<std::vector<chip>> chipPool;
    std::vector<chip*> freeChipPool;
    std::vector<std::vector<chipPlace>> chipPlacePool;
    
    std::vector<chip*> dirtyChips;
    std::set<int> fallRows;
    
    const unsigned int needChipForMatch3 = 2U;
    const swapDirection gravityDirection = swapDirection::BOT;
    const unsigned int maxColor = static_cast<unsigned int>(chipColor::SIZE);
};
