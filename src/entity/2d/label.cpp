#include "label.h"
#include "transformComponent.h"
#include "colorComponent.h"
#include "renderComponent.h"
#include "renderSystem.h"

#ifdef MACOS
#include "GLUT/glut.h"
#else
#include "glew/glew.h"
#include "freeglut/freeglut.h"
#endif


label::label() {
    addComponent<colorComponent>();
    addComponent<labelComponent>();
    renderSystem::getInstance()->registerEntity(this);
}

void label::createCash() {
    for (size_t n = 0U; n < cashArray.size(); n++) {
        cashArray[n] = std::make_shared<labelCash>();
    }
}

vec2f label::calcAutoSize(const std::string& text, void* font) const {
    if (font == NULL) {
        return {};
    }
    vec2f result;
    for (auto& c : text) {
        result[0] += glutBitmapWidth(font, c);
    }
    result[1] = 18;
    return result;
}

void label::updateCash(size_t freeCashIdx, size_t busyCashIdx) {
    auto busyLabelComponent = getCash(busyCashIdx)->getComponent<labelComponent>();
    auto busyTextLen = busyLabelComponent->getLenText();
    auto currentLabelComponent = getComponent<labelComponent>();
    auto currentTextLen = currentLabelComponent->getLenText();
    
    auto currentTransformComponent = getTransformComponent();

    if (busyTextLen != currentTextLen) {
        auto newSize = calcAutoSize(currentLabelComponent->getText(), currentLabelComponent->getFont());
        currentTransformComponent->setSize(newSize);
    }
    currentTransformComponent->updateCashTransform(wThis);
    auto freeTransformComponent = getCash(freeCashIdx)->getComponent<transformComponent>();
    copyComponent(freeTransformComponent);
    freeTransformComponent->setCashSize(currentTransformComponent->getScale());
    copyComponent(getCash(freeCashIdx)->getComponent<labelComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<colorComponent>());
}

label::labelCash::labelCash() {
    addComponent<colorComponent>();
    addComponent<labelComponent>();
}
