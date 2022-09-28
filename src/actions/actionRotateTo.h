#pragma once

#include "struct.h"
#include "actionDelay.h"

namespace action {
    class actionRotateTo : public actionDelay {
    public:
        actionRotateTo() = delete;
        actionRotateTo(quaternion aTargetRotate, unsigned int aTime, std::function<void()> aCallback);
        ~actionRotateTo() = default;
        
        virtual void update(std::weak_ptr<entity> object, float dt) override;
        virtual void end(std::weak_ptr<entity> object) override;
        virtual void reset() override;
    private:
        quaternion startRotate;
        quaternion targetRotate;
        
        bool init = false;
    };
}
