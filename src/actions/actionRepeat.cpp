#include "actionRepeat.h"
#include "entity.h"

actionRepeat::actionRepeat(actionBase* actionForRepeat, std::function<void()> callback) :
actionBase(callback),
fullTimes(0),
times(0),
action(std::move(actionForRepeat)),
type(typeRepeat::INFINITELY) {}

actionRepeat::actionRepeat(actionBase* actionForRepeat, int aTimes, std::function<void()> callback) :
actionBase(callback),
fullTimes(aTimes),
times(0),
action(std::move(actionForRepeat)),
type(typeRepeat::FINITELY) {}

bool actionRepeat::isEnd() const {
    if (!action) {
        return true;
    }
    if (type == typeRepeat::INFINITELY) {
        return false;
    }
    return times < fullTimes;
}

void actionRepeat::update(std::weak_ptr<entity> object, float dt) {
    if (isEnd()) {
        return;
    }
    if (type == typeRepeat::INFINITELY) {
        action->update(object, dt);
        if (action->isEnd()) {
            action->end(object);
            action->reset();
        }
        return;
    }
    action->update(object, dt);
    if (action->isEnd()) {
        action->end(object);
        times--;
        if (!isEnd()) {
            action->reset();
        }
    }
}

void actionRepeat::end(std::weak_ptr<entity> object) {
    action->end(object);
    if (callback) {
        callback();
    }
}

void actionRepeat::reset() {
    times = 0;
}
