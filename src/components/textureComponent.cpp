#include "textureComponent.h"
#include "glFunctional.h"

void textureComponent::setTexIdx(unsigned int aTexIdx) {
    texIdx = aTexIdx;
    markDirty();
}

void textureComponent::setShaderIdx(unsigned int aShaderIdx) {
    shaderIdx = aShaderIdx;
    markDirty();
}

unsigned int textureComponent::getTexIdx() const {
    return texIdx;
}

unsigned int textureComponent::getShaderIdx() const {
    return shaderIdx;
}

void textureButtonComponent::setTexButtonIdx(unsigned int normal, unsigned int cover, unsigned int click) {
    texturs[0] = normal;
    texturs[1] = cover;
    texturs[2] = click;
    setTexIdx(normal);
}

void textureButtonComponent::updateTexture(stateButton state) {
    setTexIdx(texturs[static_cast<unsigned int>(state)]);
}
