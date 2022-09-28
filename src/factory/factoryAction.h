#pragma once

#include <functional>
#include "struct.h"

namespace action {
    class actionBase;
}

class factoryAction {
public:
    static action::actionBase* rotate(vec3f axis, float angle, unsigned int time, std::function<void()> callback = nullptr);
    static action::actionBase* delay(unsigned int time, std::function<void()> callback = nullptr);
    static action::actionBase* repeat(action::actionBase* action, int count, std::function<void()> callback = nullptr);
    static action::actionBase* repeatInfinity(action::actionBase* action, std::function<void()> callback = nullptr);
    static action::actionBase* changeColor(color4b targetColor, unsigned int time, std::function<void()> callback = nullptr);
    static action::actionBase* sequence(std::vector<action::actionBase*> actions, std::function<void()> callback = nullptr);
    static action::actionBase* rotateTo(quaternion targetRotate, unsigned int time, std::function<void()> callback = nullptr);
    static action::actionBase* moveTo(vec3f targetPos, unsigned int time, std::function<void()> callback = nullptr);
private:
    factoryAction() = default;
    ~factoryAction() = default;
};
