#include "sprite.h"
#include "colorComponent.h"
#include "textureComponent.h"
#include "renderComponent.h"
#include "renderSystem.h"

sprite::sprite() {
    addComponent<colorComponent>();
    addComponent<textureComponent>();
    addComponent<spriteComponent>();
    renderSystem::getInstance()->registerEntity(this);
}


void sprite::updateCash(size_t freeCashIdx, size_t busyCashIdx) {
    node::updateCash(freeCashIdx, busyCashIdx);
    copyComponent(getCash(freeCashIdx)->getComponent<colorComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<spriteComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<textureComponent>());
}


void sprite::createCash() {
    for (size_t n = 0U; n < cashArray.size(); n++) {
        cashArray[n] = std::make_shared<spriteCash>();
    }
}

sprite::spriteCash::spriteCash() {
    addComponent<colorComponent>();
    addComponent<textureComponent>();
    addComponent<spriteComponent>();
}
