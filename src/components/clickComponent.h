#pragma once

#include "componentBase.h"
#include "struct.h"
#include <functional>

enum class typeClickComponent {BUTTON, SWAP, UNKNOWN};

class entity;

class clickComponent : public componentBase<componentId::CLICK> {
public:
    void setState(stateButton aState);
    void setClickable(bool value);
    bool isClickable() const;
    stateButton getState() const;
    typeClickComponent getTypeClickComponent() const;
protected:
    clickComponent() = delete;
    clickComponent(typeClickComponent aType);
    ~clickComponent() = default;
private:
    stateButton state;
    bool clickable = true;
    typeClickComponent type = typeClickComponent::UNKNOWN;
};

class buttonComponent : public clickComponent {
public:
    buttonComponent();
    ~buttonComponent() = default;
    void setClickCallback(clickCallback aCallback);
    const clickCallback& getClickCallback() const;
private:
    clickCallback callback;
};

class swapComponent : public clickComponent  {
public:
    swapComponent();
    ~swapComponent() = default;
    void setSwapCallback(swapCallback aCallback);
    const swapCallback& getSwapCallback() const;
private:
    swapCallback callback;
};
