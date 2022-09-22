#pragma once

#include <functional>
#include "struct.h"

class actionBase;

class factoryAction {
public:
    static actionBase* createRotateAction(vec3f axis, float angle, unsigned int time, std::function<void()> callback = nullptr);
    static actionBase* createDelayAction(unsigned int time, std::function<void()> callback = nullptr);
    static actionBase* createRepeatAction(actionBase* action, int count, std::function<void()> callback = nullptr);
    static actionBase* createRepeatInfinityAction(actionBase* action, std::function<void()> callback = nullptr);
    static actionBase* createChangeColorAction(color4b targetColor, unsigned int time, std::function<void()> callback = nullptr);
    static actionBase* createActionSequence(std::vector<actionBase*> actions, std::function<void()> callback = nullptr);
    static actionBase* createRotateLerpAction(quaternion targetRotate, unsigned int time, std::function<void()> callback = nullptr);
private:
    factoryAction() = default;
    ~factoryAction() = default;
};
