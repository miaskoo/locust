#pragma once

#include "componentBase.h"

class textureComponent : public componentBase<componentId::TEXTURE> {
public:
    textureComponent() = default;
    ~textureComponent() = default;
    void setTexIdx(unsigned int aTexIdx);
    void setShaderIdx(unsigned int aShaderIdx);
    unsigned int getTexIdx() const;
    unsigned int getShaderIdx() const;
protected:
    unsigned int texIdx = 0;
    unsigned int shaderIdx = 0;
};

class textureButtonComponent : public textureComponent {
public:
    textureButtonComponent() = default;
    ~textureButtonComponent() = default;
    void setTexButtonIdx(unsigned int normal, unsigned int cover, unsigned int click);
    void updateTexture(stateButton state);
protected:
    unsigned int texturs[3] {0};
};
