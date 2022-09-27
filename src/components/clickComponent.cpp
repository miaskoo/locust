#include "clickComponent.h"

clickComponent::clickComponent(typeClickComponent aType) : type(aType) {}

void clickComponent::setState(stateButton aState) {
    state = aState;
    markDirty();
}

void clickComponent::setClickable(bool value) {
    clickable = value;
    markDirty();
}

bool clickComponent::isClickable() const {
    return clickable;
}

stateButton clickComponent::getState() const {
    return state;
}

typeClickComponent clickComponent::getTypeClickComponent() const {
    return type;
}

buttonComponent::buttonComponent() : clickComponent(typeClickComponent::BUTTON) {}

void buttonComponent::setClickCallback(clickCallback aCallback) {
    callback = std::move(aCallback);
    markDirty();
}

const clickCallback& buttonComponent::getClickCallback() const {
    return callback;
}

swapComponent::swapComponent() : clickComponent(typeClickComponent::SWAP) {}

void swapComponent::setSwapCallback(swapCallback aCallback) {
    callback = std::move(aCallback);
    markDirty();
}

const swapCallback& swapComponent::getSwapCallback() const {
    return callback;
}
