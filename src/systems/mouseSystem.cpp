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

void mouseSystem::update(int xPos, int yPos) {
    mousePosX = xPos;
    mousePosY = yPos;
    vec2f posMouse(static_cast<float>(xPos), static_cast<float>(yPos));
    if (supervisedEntity) {
        if (mouseState != stateMouse::CLICK_OUT) {
            return;
        }
        auto component = supervisedEntity->getComponent<clickComponent>();
        auto typeComponent = component->getTypeClickComponent();
        if (typeComponent == typeClickComponent::BUTTON) {
            auto callback = static_cast<buttonComponent*>(component)->getClickCallback();
            if (callback) {
                callback(supervisedEntity);
            }
        }
        else if (typeComponent == typeClickComponent::SWAP) {
            auto transform = supervisedEntity->getComponent<transformComponent>();
            auto callback = static_cast<swapComponent*>(component)->getSwapCallback();
            if (callback) {
                auto dir = functionHelper::getDirectionFromPoint(transform->getCashPos(), posMouse, transform->getCashSize()[0]);
                if (dir != swapDirection::UNKNOWN) {
                    callback(supervisedEntity, dir);
                }

            }
        }
        supervisedEntity = nullptr;
        return;
    }
    for (auto& obj : objects) {
        auto component = obj->getComponent<clickComponent>();
        auto newState = component->getState();
        if (component->isClickable()) {
            auto tComponent = obj->getComponent<transformComponent>();
            bool isCover = functionHelper::poinInQuad2d(tComponent->getCashPos(), tComponent->getCashSize(), posMouse);
            if (isCover) {
                if (mouseState == stateMouse::CLICK && !supervisedEntity) {
                    newState = stateButton::PRESS;
                    supervisedEntity = obj->getWeakPtr().lock();
                }
                else {
                    newState = stateButton::COVER;
                }
            }
            else {
                newState = stateButton::WAIT;
            }
        }
        else {
            newState = stateButton::LOCK;
        }
        
        
        if (component->getState() != newState) {
            component->setState(newState);
            obj->getComponent<textureButtonComponent>()->updateTexture(component->getState());
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
    if (iter == objects.end()) {
        return;
    }
    objects.erase(iter);
}

void mouseSystem::setMouseState(const stateMouse &aMouseState) {
    mouseState = aMouseState;
}

stateMouse mouseSystem::getMouseState() {
    return mouseState;
}

std::shared_ptr<entity> mouseSystem::getSupervisedEntity() {
    return supervisedEntity;
}

int mouseSystem::getMousePosX() {
    return mousePosX;
}

int mouseSystem::getMousePosY() {
    return mousePosY;
}
