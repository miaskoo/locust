#include "actionRotate.h"
#include "transformComponent.h"

actionRotate::actionRotate(vec3f aAxis, float aAngle, unsigned int aTime, std::function<void()> aCallback) :
actionDelay(aTime, aCallback),
destination(aAngle),
axis(aAxis){}

void actionRotate::update(std::weak_ptr<entity> object, float dt)  {
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
    
    pObject->getTransformComponent()->setRotate(startRotate * quaternion::getFromEuler(axis, destination * getTimeProgress()));
}

void actionRotate::end(std::weak_ptr<entity> object) {
    auto pObject = object.lock();
    
    if (!pObject) {
        return;
    }
    
    pObject->getTransformComponent()->setRotate(startRotate * quaternion::getFromEuler(axis, destination));
    
    actionDelay::end(object);
}

void actionRotate::reset() {
    actionDelay::reset();
    startRotate = startRotate * quaternion::getFromEuler(axis, destination);
}
