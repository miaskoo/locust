#include "chipPlace.h"
#include "chip.h"
chipPlace::chipPlace(const pairInt& aId) : currentId(aId) {}

void chipPlace::bindChip(chip *aChip) {
    if (bindedChip) {
        return;
    }
    bindedChip = aChip;
    bindedChip->setBindId(currentId);
}

void chipPlace::unbindChip() {
    bindedChip = nullptr;
}

chip* chipPlace::getBindedChip() const {
    return bindedChip;
}

pairInt chipPlace::getId() const {
    return currentId;
}
 
