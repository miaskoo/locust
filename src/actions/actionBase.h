#pragma once
#include <memory>
#include <functional>

class entity;

class actionBase {
public:
    virtual ~actionBase() = default;
    
    virtual void update(std::weak_ptr<entity> object, float dt) = 0;
    virtual void end(std::weak_ptr<entity> object) = 0;
    virtual bool isEnd() const = 0;
    virtual void reset() = 0;
protected:
    actionBase() = delete;
    actionBase(std::function<void()> aCallback = nullptr);
    std::function<void()> callback = nullptr;
};

