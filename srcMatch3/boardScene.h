#pragma once
#include "scene.h"
#include "boardController.h"
#include <set>
#include <unordered_map>

enum class boardSceneState {MAIN, GAME, END};

class boardScene : public scene {
public:
    boardScene() = default;
    ~boardScene() = default;
    
    virtual void update(float dt);
    void init(unsigned int w, unsigned int h, vec2f chipSize);
    void startGame();
private:
    void initMainMenu();
    void initEndGameMenu();
    void destroyMenu();
    void swapCallback(std::shared_ptr<entity> caller, swapDirection direction);
    
    boardController boardController;
    std::shared_ptr<entity> menu;
    
    bool isInit = false;
    
    std::unordered_map<std::shared_ptr<entity>, pairInt> callerToId;
    
    boardSceneState currentState = boardSceneState::MAIN;
    boardSceneState newState = boardSceneState::MAIN;
};
