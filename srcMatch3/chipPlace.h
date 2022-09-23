#pragma once
#include <utility>

class chip;

class chipPlace {
public:
    chipPlace() = delete;
    chipPlace(const std::pair<unsigned int, unsigned int>& aId);
    ~chipPlace() = default;
    
    void bindChip(chip* aChip);
    void unbindChip();
    chip* getBindedChip() const;
    chip* getBindedChipC() const;
    std::pair<unsigned int, unsigned int> getId() const;
private:
    chip* bindedChip = nullptr;
    
    const std::pair<unsigned int, unsigned int> id;
};
