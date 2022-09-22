#include "button.h"
#include "transformComponent.h"
#include "colorComponent.h"
#include "clickComponent.h"
#include "textureComponent.h"
#include "renderSystem.h"
#include "mouseSystem.h"
#include "renderComponent.h"

button::button() {
    addComponent<colorComponent>();
    addComponent<textureButtonComponent>();
    addComponent<clickComponent>();
    addComponent<spriteComponent>();
    renderSystem::getInstance()->registerEntity(this);
    mouseSystem::getInstance()->registerEntity(this);
}

void button::updateCash(size_t freeCashIdx, size_t busyCashIdx) {
    node::updateCash(freeCashIdx, busyCashIdx);
    copyComponent(getCash(freeCashIdx)->getComponent<colorComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<textureComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<clickComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<spriteComponent>());
}

void button::createCash() {
    for (size_t n = 0U; n < cashArray.size(); n++) {
        cashArray[n] = std::make_shared<buttonCash>();
    }
}

button::buttonCash::buttonCash() {
    addComponent<colorComponent>();
    addComponent<textureComponent>();
    addComponent<clickComponent>();
    addComponent<spriteComponent>();
}

button::~button() {
    renderSystem::getInstance()->unregisterEntity(this);
}
