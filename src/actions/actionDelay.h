#pragma once

#include "actionBase.h"

class actionDelay : public actionBase {
public:
    actionDelay(unsigned int aTime, std::function<void()> aCallback);
protected:
    actionDelay() = delete;
    ~actionDelay() = default;
    
    virtual void update(std::weak_ptr<entity> object, float dt) override;
    virtual void end(std::weak_ptr<entity> object) override;
    virtual bool isEnd() const override;
    virtual void reset() override;
    
    float getTimeProgress();
private:
    const unsigned int fullTime;
    unsigned int currentTime;
};
