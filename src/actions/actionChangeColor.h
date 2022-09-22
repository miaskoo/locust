#pragma once

#include "actionDelay.h"
#include "struct.h"

class actionChangeColor : public actionDelay {
public:
    actionChangeColor() = delete;
    actionChangeColor(color4b aColor, unsigned int aTime, std::function<void()> aCallback = nullptr);
    ~actionChangeColor() = default;
    
    virtual void update(std::weak_ptr<entity> object, float dt) override;
    virtual void end(std::weak_ptr<entity> object) override;
    virtual void reset() override;
private:
    color4b startColor;
    color4b newColor;
    vec4f stepColor;
    
    bool init = false;
};
