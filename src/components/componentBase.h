#pragma once

enum class componentId {TRANSFORM = 0U, COLOR = 1U, TEXTURE = 2U, RENDER = 3U, CLICK = 4U, SIZE = 5U};
enum class stateButton {WAIT = 0U, COVER = 1U, PRESS = 2U, LOCK = 0U};

class componentBaseInterface {
public:
    virtual ~componentBaseInterface() = default;
    virtual bool isDirty() const = 0;
    virtual void markDirty() = 0;
    virtual void unDirty() = 0;
protected:
    componentBaseInterface() = default;
};

template <componentId aType>
class componentBase : public componentBaseInterface {
public:
    ~componentBase() = default;
    static componentId getType() {return type;};
    virtual bool isDirty() const override {return dirty;};
    virtual void markDirty() override {dirty = true;};
    virtual void unDirty() override {dirty = false;};
protected:
    componentBase() = default;
    static constexpr componentId type = aType;
private:
    bool dirty = false;
};
