#pragma once

#include "struct.h"
#include "actionDelay.h"

class actionLerpRotate : public actionDelay {
public:
    actionLerpRotate(quaternion aTargetRotate, unsigned int aTime, std::function<void()> aCallback);
    ~actionLerpRotate() = default;
    
    virtual void update(std::weak_ptr<entity> object, float dt) override;
    virtual void end(std::weak_ptr<entity> object) override;
    virtual void reset() override;
private:
    quaternion startRotate;
    quaternion targetRotate;
    
    bool init = false;
};
