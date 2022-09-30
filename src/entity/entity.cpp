#include "entity.h"
#include "transformComponent.h"
#include "textureComponent.h"
#include "transformComponent.h"
#include "renderSystem.h"
#include "mouseSystem.h"
#include <iterator>

using namespace action;

entity::entity(dimension aType) : type(aType) {}

dimension entity::getDimension() const {
    return type;
}

void entity::reserveChild(size_t count) {
    childs.reserve(count);
}

void entity::addChild(std::shared_ptr<entity>& child) {
    if (!child) {
        return;
    }
    auto d = getDimension();
    if (d != dimension::NONE) {
        if (child->getDimension() != getDimension()) {
            return;
        }
    }
    childs.push_back(child);
    child->setParent(wThis);
    child->markDirty();
    child->markDirtyChilds();
}

void entity::setParent(std::weak_ptr<entity> aParent) {
    parent = aParent;
}

std::shared_ptr<entity> entity::getParent() {
    return parent.lock();
}

std::shared_ptr<entityCash> entity::getCash(size_t cashIdx) {
    return cashArray[cashIdx];
}

const std::vector<std::shared_ptr<entity>>& entity::getChilds() {
    return childs;
}

void entity::setWeakPtrThis(std::weak_ptr<entity> aWThis) {
    if (auto ptr = wThis.lock()) {
        return;
    }
    wThis = aWThis;
}

void entity::update(float dt) {
    std::vector<std::shared_ptr<actionBase>> localCopyAction;
    std::copy(actions.begin(), actions.end(), std::back_inserter(localCopyAction));
    for (auto& action : localCopyAction) {
        action->update(wThis, dt);
    }
    for (auto& child : childs) {
        child->update(dt);
    }
    for (auto& action : localCopyAction) {
        if (action->isEnd()) {
            action->end(wThis);
        }
    }
    
    auto forRemove = std::remove_if(actions.begin(), actions.end(), [this](auto& element){
        return element->isEnd();
    });
    if (forRemove != actions.end()) {
        actions.erase(forRemove, actions.end());
    }
}

void entity::addAction(actionBase *action) {
    actions.emplace_back(std::move(action));
}

void entity::clearAllActions() {
    actions.clear();
}

bool entity::isDirtyComponents() const {
    for (const auto& component : components) {
        if (component) {
            if (component->isDirty()) {
                return true;
            }
        }
    }
    return false;
}

void entity::markDirty() {
    dirty = true;
}

bool entity::isDirty() const {
    return dirty;
}

void entity::unDirty() {
    dirty = false;
}

void entity::unDirtyComponents() {
    for (const auto& component : components) {
        if (component) {
            component->unDirty();
        }
    }
}

transformComponentInterface* entity::getTransformComponent() {
    auto component = getComponent<transformComponent>();
    return dynamic_cast<transformComponentInterface*>(component);
}

void entity::setPos(vec3f pos) {
    getTransformComponent()->setPos(pos);
}

void entity::setSize(vec3f size) {
    getTransformComponent()->setSize(size);
}

void entity::setPivot(vec2f pivot) {
    getTransformComponent()->setPivot(pivot);
}

void entity::setScale(vec3f scale) {
    getTransformComponent()->setScale(scale);
}

void entity::setAnchor(vec2f anchor) {
    getTransformComponent()->setAnchor(anchor);
}

void entity::setRotate(vec3f rotate) {
    getTransformComponent()->setRotate(rotate);
}

void entity::setPos(float x, float y) {
    setPos({x,y});
}

void entity::setSize(float x, float y, float z) {
    setSize({x,y,z});
}

void entity::setRotate(float x, float y, float z) {
    setRotate({x,y,z});
}

void entity::setAnchor(float x, float y) {
    setAnchor({x,y});
}

void entity::setPivot(float x, float y) {
    setPivot({x,y});
}

void entity::setScale(float x, float y, float z) {
    setScale({x,y,z});
}

size_t entity::getCountAction() {
    return actions.size();
}

std::weak_ptr<entity> entity::getWeakPtr() {
    return wThis;
}

void entity::markDelete() {
    needDelete = true;
}

bool entity::isNeedDelete() {
    return needDelete;
}

void entity::unMarkDelete() {
    needDelete = false;
}

void entity::setZOrder(unsigned int aZOrder) {
    zOrder = aZOrder;
}

unsigned int entity::getZOrder() {
    return zOrder;
}

void entity::markDirtyChilds() {
    for (auto& child : childs) {
        child->markDirtyChilds();
    }
}

void entity::removeEntity(std::list<std::shared_ptr<entity>>& removedEntity, bool withoutCheck) {
    if (withoutCheck) {
        std::copy(childs.begin(), childs.end(), std::back_inserter(removedEntity));
        for (auto& child : childs) {
            child->removeEntity(removedEntity, withoutCheck);
        }
    }
    else {
        auto forRemoveChild = std::remove_if(childs.begin(), childs.end(), [&removedEntity, this](auto& element){
            if (element->isNeedDelete()) {
                removedEntity.push_back(element);
                element->removeEntity(removedEntity, true);
                return true;
            }
            return false;
        });
        childs.erase(forRemoveChild, childs.end());
    }
}

void entity::getAddedEntity(std::list<std::shared_ptr<entity>> &addedEntity, bool withoutCheck) {
    if (withoutCheck) {
        std::copy(childs.begin(), childs.end(), std::back_inserter(addedEntity));
        for (auto& child : childs) {
            child->getAddedEntity(addedEntity, true);
        }
    }
    else {
        for (auto& child : childs) {
            if (child->isDirty()) {
                addedEntity.push_back(child);
                child->getAddedEntity(addedEntity, true);
            }
        }
    }
}
