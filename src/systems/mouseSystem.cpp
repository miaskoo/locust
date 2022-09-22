#include "mouseSystem.h"
#include "clickComponent.h"
#include "transformComponent.h"
#include "textureComponent.h"

mouseSystem* mouseSystem::getInstance() {
    if (!instance) {
        instance = new mouseSystem();
    }
    return instance;
}

void mouseSystem::cleanup() {
    delete instance;
    instance = nullptr;
}

void mouseSystem::update(int xPos, int yPos, stateMouse state) {
    if (supervisedEntity) {
        if (state == stateMouse::CLICK_OUT) {
            if (auto callback = supervisedEntity->getComponent<clickComponent>()->getClickCallback()) {
                callback();
            }
            supervisedEntity = nullptr;
        }
        return;
    }
    
    for (auto& obj : objects) {
        auto bComponent = obj->getComponent<clickComponent>();
        auto prevState = bComponent->getState();
        auto newState = stateButton::WAIT;
        auto component = obj->getComponent<transformComponent>();
        vec3f pos = component->getCashPos();
        vec3f size = component->getCashSize();
        auto x1 = pos[0];
        auto y1 = pos[1] - size[1];
        auto x2 = pos[0] + size[0];
        auto y2 = pos[1];
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        if (y1 > y2) {
            std::swap(y1, y2);
        }
        if (bComponent->isClickable()) {
            if (xPos > x1 && xPos < x2 && yPos > y1 && yPos < y2) {
                if (state == stateMouse::CLICK) {
                    newState = stateButton::PRESS;
                    if (!supervisedEntity && prevState != newState) {
                        supervisedEntity = obj;
                    }
                }
                else {
                    newState = stateButton::COVER;
                }
            }
        }
        else {
            newState = stateButton::LOCK;
        }

        if (prevState != newState) {
            bComponent->setState(newState);
            obj->getComponent<textureButtonComponent>()->updateTexture(newState);
        }
        if (newState != stateButton::WAIT) {
            break;
        }
    }
}


void mouseSystem::registerEntity(entity* object) {
    if (!object || std::find(objects.begin(), objects.end(), object) != objects.end()) {
        return;
    }
    if (auto component = object->getComponent<clickComponent>()) {
        objects.push_front(object);
    }
}

void mouseSystem::unregisterEntity(entity* object) {
    auto iter = std::remove_if(objects.begin(), objects.end(), [object](const auto& element){
        return object == element;
    });
    objects.erase(iter);
}
