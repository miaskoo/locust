#pragma once

#include "actionDelay.h"
#include "struct.h"

class actionMoveTo : public actionDelay {
public:
    actionMoveTo(vec3f aTargetPos, unsigned int aTime, std::function<void()> aCallback);
    ~actionMoveTo() = default;
    
    virtual void update(std::weak_ptr<entity>object, float dt) override;
    virtual void end(std::weak_ptr<entity>object) override;
    virtual void reset() override;
private:
    vec3f startPos;
    vec3f targetPos;
    
    bool init = false;
};
