#include "chip.h"

chip::chip(const pairInt& aId) : chipId(aId) {}

void chip::setColor(chipColor aColor) {
    color = aColor;
}

void chip::setBindId(const pairInt& aBindId) {
    bindId = aBindId;
}

chipColor chip::getColor() const {
    return color;
}

pairInt chip::getBindId() const {
    return bindId;
}

pairInt chip::getId() const {
    return chipId;
}

void chip::setState(chipState aState) {
    state = aState;
}

chipState chip::getState() const {
    return state;
}
