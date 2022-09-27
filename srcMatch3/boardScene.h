#pragma once
#include "scene.h"
#include "boardController.h"
#include <set>
#include <unordered_map>

class boardScene : public scene {
public:
    boardScene() = default;
    ~boardScene() = default;
    
    virtual void update(float dt);
    void init(unsigned int w, unsigned int h, vec2f chipSize);
    void startGame();
private:
    void swapCallback(std::shared_ptr<entity> caller, swapDirection direction);
    
    boardController boardController;
    
    bool isInit = false;
    
    unsigned int widthBoard = 0U;
    unsigned int heightBoard = 0U;
    
    std::unordered_map<std::shared_ptr<entity>, pairInt> callerToId;
};
