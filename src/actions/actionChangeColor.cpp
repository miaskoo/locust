#include "actionChangeColor.h"
#include "colorComponent.h"
#include "entity.h"

actionChangeColor::actionChangeColor(color4b aColor, unsigned int aTime, std::function<void()> aCallback) :
actionDelay(aTime, aCallback),
newColor(aColor) {}


void actionChangeColor::update(std::weak_ptr<entity> object, float dt)  {
    auto pObject = object.lock();
    
    if (!pObject) {
        return;
    }
    
    if (!init) {
        auto color = pObject->getComponent<colorComponent>()->getColor();
        for (size_t n = 0U; n < 4U; n++) {
            startColor[n] = color[n];
            if (newColor[n] > startColor[n]) {
                stepColor[n] = newColor[n] - startColor[n];
            }
            else {
                stepColor[n] = startColor[n] - newColor[n];
            }
        }
        init = true;
    }
    
    actionDelay::update(object, dt);
    if (isEnd()) {
        return;
    }
    
    auto percent = getTimeProgress();
    color4b resultColor;
    for (int n = 0; n < 4U; n++) {
        if (newColor[n] == startColor[n]) {
            resultColor[n] = startColor[n];
            continue;
        }
        if (newColor[n] > startColor[n]) {
            resultColor[n] = startColor[n] + stepColor[n] * percent;
        }
        else {
            resultColor[n] = startColor[n] - stepColor[n] * percent;
        }
    }
    pObject->getComponent<colorComponent>()->setColor(resultColor[0], resultColor[1], resultColor[2], resultColor[3]);
}

void actionChangeColor::end(std::weak_ptr<entity> object) {
    auto pObject = object.lock();
    
    if (!pObject) {
        return;
    }
    
    pObject->getComponent<colorComponent>()->setColor(newColor[0], newColor[1], newColor[2], newColor[3]);
    
    actionDelay::end(object);
}

void actionChangeColor::reset() {
    actionDelay::reset();
    init = false;
}
