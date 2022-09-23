#include "chip.h"

chip::chip(const std::pair<unsigned int, unsigned int>& aId) : id(aId) {}

void chip::setColor(chipColor aColor) {
    color = aColor;
}

void chip::setBindId(const std::pair<unsigned int, unsigned int>& aBindId) {
    bindId = aBindId;
}

chipColor chip::getColor() const {
    return color;
}

std::pair<unsigned int, unsigned int> chip::getBindId() const {
    return bindId;
}

std::pair<unsigned int, unsigned int> chip::getId() const {
    return id;
}
