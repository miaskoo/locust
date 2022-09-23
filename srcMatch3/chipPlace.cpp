#include "chipPlace.h"

chipPlace::chipPlace(const std::pair<unsigned int, unsigned int>& aId) : id(aId) {}

void chipPlace::bindChip(chip *aChip) {
    if (bindedChip) {
        return;
    }
    bindedChip = aChip;
}

void chipPlace::unbindChip() {
    bindedChip = nullptr;
}

chip* chipPlace::getBindedChip() const {
    return bindedChip;
}

std::pair<unsigned int, unsigned int> chipPlace::getId() const {
    return id;
}
 
