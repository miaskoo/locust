#pragma once

#include "struct.h"
#include <list>

class entity;

class mouseSystem {
public:
    static mouseSystem* getInstance();
    static void cleanup();
    void registerEntity(entity* object);
    void unregisterEntity(entity* object);
    void update(int xPos, int yPos, stateMouse state);
private:
    std::list<entity*> objects;
    
    entity* supervisedEntity = nullptr;
     
    static inline mouseSystem* instance = nullptr;
};
