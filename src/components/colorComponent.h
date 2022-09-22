#pragma once

#include "componentBase.h"
#include "struct.h"

class colorComponent : public componentBase<componentId::COLOR> {
public:
    colorComponent() = default;
    ~colorComponent() = default;
    void setAlphaMode(bool value);
    void setColor(unsigned char r, unsigned char g, unsigned char b);
    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    const color4b& getColor() const;
    bool isAlphaMode() const;
private:
    color4b color = {MAX_COLOR, MAX_COLOR, MAX_COLOR, MAX_COLOR};
    bool alphaMode = true;
};
