#include "colorComponent.h"
#include "glFunctional.h"

void colorComponent::setColor(unsigned char r, unsigned char g, unsigned char b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    markDirty();
}

void colorComponent::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
    markDirty();
}

void colorComponent::setAlphaMode(bool value) {
    alphaMode = value;
    markDirty();
}

bool colorComponent::isAlphaMode() const {
    return alphaMode;
}

const color4b& colorComponent::getColor() const {
    return color;
}
