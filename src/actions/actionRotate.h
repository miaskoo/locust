#pragma once
#include "actionDelay.h"
#include "struct.h"

class entity;

class actionRotate : public actionDelay {
public:
    actionRotate() = delete;
    actionRotate(vec3f aAxis, float aAngle, unsigned int aTime, std::function<void()> aCallback = nullptr);
    ~actionRotate() = default;
    
    virtual void update(std::weak_ptr<entity>object, float dt) override;
    virtual void end(std::weak_ptr<entity>object) override;
    virtual void reset() override;
    
private:
    int destination;
    vec3f axis;
    quaternion startRotate;
    
    bool init = false;
};
