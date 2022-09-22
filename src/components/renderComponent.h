#pragma once

#include "componentBase.h"
#include <string>

enum class typeRenderComponent {SPRITE = 0U, BUFFER = 1U, LABEL = 2U, BUTTON = 3U, NONE = 3U};

struct bufferData {
    size_t buffIdx = 0U;
    size_t buffSize = 0U;
    bool cullFaceMode = false;
};

struct labelData {
    std::string text;
    void* font = nullptr;
};

class renderComponent : public componentBase<componentId::RENDER> {
public:
    typeRenderComponent getRenderType() const;
protected:
    renderComponent() = delete;
    renderComponent(typeRenderComponent aType);
    ~renderComponent() = default;
private:
    typeRenderComponent type;
};


class labelComponent : public renderComponent {
public:
    labelComponent();
    ~labelComponent() = default;
    void setText(const std::string& text);
    void setFont(void* font);
    
    const std::string& getText() const;
    size_t getLenText() const;
    void* getFont() const;
private:
    labelData data;
};

class bufferComponent : public renderComponent {
public:
    bufferComponent();
    ~bufferComponent() = default;
    void setBuffIdx(size_t idx);
    void setBuffSize(size_t size);
    void setCullFaceMode(bool value);
    
    size_t getBuffIdx() const;
    size_t getBuffSize() const;
    bool isCullFaceMode() const;
private:
    bufferData data;
};

class spriteComponent : public renderComponent {
public:
    spriteComponent();
    ~spriteComponent() = default;
};
