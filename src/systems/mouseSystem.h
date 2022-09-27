#pragma once

#include "struct.h"
#include <list>
#include <memory>

class entity;

class mouseSystem {
public:
    static mouseSystem* getInstance();
    static void cleanup();
    void registerEntity(entity* object);
    void unregisterEntity(entity* object);
    void update(int xPos, int yPos);
    void setMouseState(const stateMouse& aMouseState);
    stateMouse getMouseState();
    std::shared_ptr<entity> getSupervisedEntity();
    int getMousePosX();
    int getMousePosY();
private:
    
    stateMouse mouseState = stateMouse::IDLE;
    int mousePosX = 0;
    int mousePosY = 0;
    
    std::list<entity*> objects;
    
    std::shared_ptr<entity> supervisedEntity = nullptr;
     
    static inline mouseSystem* instance = nullptr;
};
