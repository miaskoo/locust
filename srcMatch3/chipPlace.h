#pragma once

#include <utility>
#include "struct.h"

class chip;

class chipPlace {
public:
    chipPlace() = delete;
    chipPlace(const pairInt& aId);
    ~chipPlace() = default;
    
    void bindChip(chip* aChip);
    void unbindChip();
    chip* getBindedChip() const;
    chip* getBindedChipC() const;
    pairInt getId() const;
private:
    chip* bindedChip = nullptr;
    
    const pairInt currentId;
};
