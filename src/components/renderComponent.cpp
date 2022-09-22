#include "renderComponent.h"
#include "glFunctional.h"

renderComponent::renderComponent(typeRenderComponent aType) : type(aType) {}

typeRenderComponent renderComponent::getRenderType() const {
    return type;
}

labelComponent::labelComponent() : renderComponent(typeRenderComponent::LABEL) {}

void labelComponent::setText(const std::string& text) {
    data.text = text;
    markDirty();
}

void labelComponent::setFont(void *font) {
    data.font = font;
    markDirty();
}

const std::string& labelComponent::getText() const {
    return data.text;
}

size_t labelComponent::getLenText() const {
    return data.text.length();
}

void* labelComponent::getFont() const {
    return data.font;
}

bufferComponent::bufferComponent() : renderComponent(typeRenderComponent::BUFFER) {}

void bufferComponent::setBuffIdx(size_t idx) {
    data.buffIdx = idx;
}

void bufferComponent::setBuffSize(size_t size) {
    data.buffSize = size;
}

void bufferComponent::setCullFaceMode(bool value) {
    data.cullFaceMode = value;
}

size_t bufferComponent::getBuffIdx() const {
    return data.buffIdx;
}

size_t bufferComponent::getBuffSize() const {
    return data.buffSize;
}

bool bufferComponent::isCullFaceMode() const {
    return data.cullFaceMode;
}

spriteComponent::spriteComponent() : renderComponent(typeRenderComponent::SPRITE) {}
