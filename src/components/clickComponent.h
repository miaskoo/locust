#pragma once

#include "componentBase.h"
#include <functional>

class clickComponent : public componentBase<componentId::CLICK> {
public:
    clickComponent() = default;
    ~clickComponent() = default;
    void setClickCallback(std::function<void()>&& aClickCallback);
    void setState(stateButton aState);
    void setClickable(bool value);
    bool isClickable() const;
    stateButton getState() const;
    const std::function<void()>& getClickCallback() const;
private:
    std::function<void()> clickCallback;
    stateButton state;
    bool clickable = true;
};
