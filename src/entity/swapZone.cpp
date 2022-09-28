#include "swapZone.h"
#include "transformComponent.h"
#include "colorComponent.h"
#include "clickComponent.h"
#include "textureComponent.h"
#include "renderSystem.h"
#include "mouseSystem.h"
#include "renderComponent.h"

swapZone::swapZone() {
    addComponent<colorComponent>();
    addComponent<textureButtonComponent>();
    addComponent<swapComponent>();
    addComponent<spriteComponent>();
}

void swapZone::updateCash(size_t freeCashIdx, size_t busyCashIdx) {
    node::updateCash(freeCashIdx, busyCashIdx);
    copyComponent(getCash(freeCashIdx)->getComponent<colorComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<textureComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<swapComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<spriteComponent>());
}

void swapZone::createCash() {
    for (size_t n = 0U; n < cashArray.size(); n++) {
        cashArray[n] = std::make_shared<swapZoneCash>();
    }
}

swapZone::swapZoneCash::swapZoneCash() {
    addComponent<colorComponent>();
    addComponent<textureComponent>();
    addComponent<swapComponent>();
    addComponent<spriteComponent>();
}
