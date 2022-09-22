#include "actionSequence.h"

actionSequence::actionSequence(std::function<void()> aCallback) :
actionBase(aCallback) {}

void actionSequence::addAction(actionBase* action) {
    actions.emplace_back(std::move(action));
}

void actionSequence::update(std::weak_ptr<entity>object, float dt) {
    for (auto& action : actions) {
        if (!action->isEnd()) {
            action->update(object, dt);
            return;
        }
    }
}

void actionSequence::end(std::weak_ptr<entity> object) {
    for (auto& action : actions) {
        if (!action->isEnd()) {
            action->end(object);
        }
    }
    if (callback) {
        callback();
    }
}

bool actionSequence::isEnd() const {
    for (const auto& action : actions) {
        if (!action->isEnd()) {
            return false;
        }
    }
    return true;
}

void actionSequence::reset() {
    for (auto& action : actions) {
        action->reset();
    }
}
