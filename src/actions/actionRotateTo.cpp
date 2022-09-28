#include "actionRotateTo.h"
#include "entity.h"
#include "transformComponent.h"

using namespace action;

actionRotateTo::actionRotateTo(quaternion aTargetRotate, unsigned int aTime, std::function<void()> aCallback) :
actionDelay(aTime, aCallback),
targetRotate(aTargetRotate) {}

void actionRotateTo::update(std::weak_ptr<entity> object, float dt) {
    auto pObject = object.lock();
    
    if (!pObject) {
        return;
    }
    
    if (!init) {
        startRotate = pObject->getTransformComponent()->getRotate();
        init = true;
    }
    
    actionDelay::update(object, dt);
    if (isEnd()) {
        return;
    }
    
    auto currentRotate = quaternion::getLerp(startRotate, targetRotate, getTimeProgress());
    pObject->getTransformComponent()->setRotate(currentRotate);
}

void actionRotateTo::end(std::weak_ptr<entity> object) {
    auto pObject = object.lock();
    
    if (!pObject) {
        return;
    }
    
    pObject->getTransformComponent()->setRotate(targetRotate);
    
    actionDelay::end(object);
}

void actionRotateTo::reset() {
    init = false;
    actionDelay::reset();
}
