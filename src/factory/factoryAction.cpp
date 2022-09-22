#include "factoryAction.h"
#include "actionRotate.h"
#include "actionDelay.h"
#include "actionRepeat.h"
#include "actionChangeColor.h"
#include "actionSequence.h"
#include "actionLerpRotate.h"

actionBase* factoryAction::createRotateAction(vec3f axis, float angle, unsigned int time, std::function<void()> callback) {
    return new actionRotate(axis, angle, time, callback);
}

actionBase* factoryAction::createDelayAction(unsigned int time, std::function<void()> callback) {
    return new actionDelay(time, callback);
}

actionBase* createRepeatAction(actionBase* action, int count, std::function<void()> callback) {
    if (!action) {
        return nullptr;
    }
    return new actionRepeat(action, count, callback);
}

actionBase* factoryAction::createRepeatInfinityAction(actionBase* action, std::function<void()> callback) {
    if (!action) {
        return nullptr;
    }
    return new actionRepeat(action, callback);
}

actionBase* factoryAction::createChangeColorAction(color4b targetColor, unsigned int time, std::function<void()> callback) {
    return new actionChangeColor(targetColor, time, callback);
}

actionBase* factoryAction::createActionSequence(std::vector<actionBase *> actions, std::function<void()> callback) {
    auto actionSeq = new actionSequence(callback);
    for (auto& action : actions) {
        if (action) {
            actionSeq->addAction(action);
        }
    }
    return actionSeq;
}

actionBase* factoryAction::createRotateLerpAction(quaternion targetRotate, unsigned int time, std::function<void()> callback) {
    return new actionLerpRotate(targetRotate, time, callback);
     
}
