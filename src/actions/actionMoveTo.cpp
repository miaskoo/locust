#include "actionMoveTo.h"
#include "transformComponent.h"

using namespace action;

actionMoveTo::actionMoveTo(vec3f aTargetPos, unsigned int aTime, std::function<void()> aCallback) : actionDelay(aTime, aCallback), targetPos(aTargetPos) {}

void actionMoveTo::update(std::weak_ptr<entity> object, float dt) {
    auto pObject = object.lock();
    
    if (!pObject) {
        return;
    }
    
    if (!init) {
        startPos = pObject->getTransformComponent()->getPos();
        init = true;
    }
    
    actionDelay::update(object, dt);
    if (isEnd()) {
        return;
    }
    
    auto pos = targetPos - startPos;
    pObject->getTransformComponent()->setPos(startPos + pos * getTimeProgress());
}

void actionMoveTo::end(std::weak_ptr<entity> object) {
    auto pObject = object.lock();
    
    if (!pObject) {
        return;
    }
    
    pObject->getTransformComponent()->setPos(targetPos);
    
    actionDelay::end(object);
}

void actionMoveTo::reset() {
    actionDelay::reset();
    init = false;
}
