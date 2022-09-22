#include "object3d.h"
#include "math.h"
#include "transformComponent.h"
#include "textureComponent.h"
#include "renderComponent.h"
#include "renderSystem.h"

object3d::object3d() : entity(dimension::THREE) {
    addComponent<transformComponentMain<vec3f>>();
    addComponent<textureComponent>();
    addComponent<bufferComponent>();
    renderSystem::getInstance()->registerEntity(this);
}

void object3d::createCash() {
    for (size_t n = 0U; n < cashArray.size(); n++) {
        cashArray[n] = std::make_shared<object3dCash>();
    }
}

void object3d::updateCash(size_t freeCashIdx, size_t busyCashIdx) {
    getTransformComponent()->updateCashTransform(wThis);
    
    copyComponent(getCash(freeCashIdx)->getComponent<transformComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<textureComponent>());
    copyComponent(getCash(freeCashIdx)->getComponent<bufferComponent>());
}

object3d::object3dCash::object3dCash() {
    addComponent<transformComponent>();
    addComponent<textureComponent>();
    addComponent<bufferComponent>();
}
