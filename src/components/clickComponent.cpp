#include "clickComponent.h"

void clickComponent::setClickCallback(std::function<void()>&& aClickCallback) {
    clickCallback = std::move(aClickCallback);
    markDirty();
}

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

const std::function<void()>& clickComponent::getClickCallback() const {
    return clickCallback;
}

stateButton clickComponent::getState() const {
    return state;
}
