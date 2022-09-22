#pragma once

#include "actionBase.h"
#include <vector>

class actionSequence : public actionBase {
public:
    actionSequence() = delete;
    actionSequence(std::function<void()> aCallback = nullptr);
    
    void addAction(actionBase* action);
    virtual void update(std::weak_ptr<entity> object, float dt) override;
    virtual void end(std::weak_ptr<entity> object) override;
    virtual bool isEnd() const override;
    virtual void reset() override;
private:
    std::vector<std::unique_ptr<actionBase>> actions;
};
