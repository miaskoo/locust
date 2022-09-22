#pragma once
#include <map>
#include <atomic>
#include <memory>
#include <vector>
#include "componentContainer.h"

class entityCash;
class entity;
class colorComponent;
class textureComponent;
class transformComponent;

class renderSystem {
public:
    static renderSystem* getInstance();
    static void cleanup();
    
    void update(size_t cashIdx);
    void setWindowSize(int w, int h);
    void registerEntity(entity* entity);
    void unregisterEntity(entity* entity);
private:
    renderSystem() = default;
    ~renderSystem() = default;
    void setOrthographic();
    void setPerspective();
    void updateWindowSize();
    void renderEntity(entity* object, size_t cashIdx);
    void bindColor(colorComponent* component);
    void unbindColor();
    void bindTexture(textureComponent* component);
    void unbindTexture();
    void bindMatrix(transformComponent* component);
    void unbindMatrix();
    void renderSprite();
    void renderBuffer(size_t buffIdx, size_t buffSize, bool cullfaceMode);
    void renderLabel(const std::string& text, void* font);
    void sortEntityForRender();
    
    std::vector<entity*> objects;
    
    int screenW = 0;
    int screenH = 0;
    bool windowSizeDirty = false;
    bool ortho = false;
    bool dirty = false;
    
    static inline renderSystem* instance = nullptr;
};
