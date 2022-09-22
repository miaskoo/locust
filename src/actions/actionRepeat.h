#pragma once

#include "actionBase.h"

enum class typeRepeat {INFINITELY = 0U, FINITELY = 1U};

class actionRepeat : public actionBase {
public:
    actionRepeat() = delete;
    actionRepeat(actionBase* aActionForRepeat, std::function<void()> aCallback = nullptr);
    actionRepeat(actionBase* aActionForRepeat, int aTimes, std::function<void()> aCallback = nullptr);
    ~actionRepeat() = default;
    
    virtual void update(std::weak_ptr<entity> object, float dt) override;
    virtual void end(std::weak_ptr<entity> object) override;
    virtual bool isEnd() const override;
    virtual void reset() override;
private:
    std::unique_ptr<actionBase> action;
    typeRepeat type;
    const int fullTimes;
    int times;
};
