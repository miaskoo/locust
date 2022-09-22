#include "actionDelay.h"

actionDelay::actionDelay(unsigned int aTime, std::function<void()> aCallback) :
actionBase(aCallback),
fullTime(aTime),
currentTime(0.0f) {}


bool actionDelay::isEnd() const {
    return currentTime > fullTime;
}

void actionDelay::update(std::weak_ptr<entity> object, float dt)  {
    currentTime += dt;
}

void actionDelay::end(std::weak_ptr<entity> object) {
    currentTime = fullTime;
    if (callback) {
        callback();
    }
}

void actionDelay::reset() {
    currentTime = 0.f;
}

float actionDelay::getTimeProgress() {
    return static_cast<float>(currentTime) / static_cast<float>(fullTime);
}

