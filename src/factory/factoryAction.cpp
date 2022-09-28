#include "factoryAction.h"
#include "actionRotateBy.h"
#include "actionDelay.h"
#include "actionRepeat.h"
#include "actionChangeColor.h"
#include "actionSequence.h"
#include "actionRotateTo.h"
#include "actionMoveTo.h"

using namespace action;

actionBase* factoryAction::rotate(vec3f axis, float angle, unsigned int time, std::function<void()> callback) {
    return new actionRotateBy(axis, angle, time, callback);
}

actionBase* factoryAction::delay(unsigned int time, std::function<void()> callback) {
    return new actionDelay(time, callback);
}

actionBase* createRepeatAction(actionBase* action, int count, std::function<void()> callback) {
    if (!action) {
        return nullptr;
    }
    return new actionRepeat(action, count, callback);
}

actionBase* factoryAction::repeatInfinity(actionBase* action, std::function<void()> callback) {
    if (!action) {
        return nullptr;
    }
    return new actionRepeat(action, callback);
}

actionBase* factoryAction::changeColor(color4b targetColor, unsigned int time, std::function<void()> callback) {
    return new actionChangeColor(targetColor, time, callback);
}

actionBase* factoryAction::sequence(std::vector<actionBase *> actions, std::function<void()> callback) {
    auto actionSeq = new actionSequence(callback);
    for (auto& action : actions) {
        if (action) {
            actionSeq->addAction(action);
        }
    }
    return actionSeq;
}

actionBase* factoryAction::rotateTo(quaternion targetRotate, unsigned int time, std::function<void()> callback) {
    return new actionRotateTo(targetRotate, time, callback);
}

actionBase* factoryAction::moveTo(vec3f targetPos, unsigned int time, std::function<void()> callback) {
    return new actionMoveTo(targetPos, time, callback);
}
