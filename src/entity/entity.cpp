#include "entity.h"
#include "transformComponent.h"
#include "textureComponent.h"
#include "transformComponent.h"
#include "renderSystem.h"
#include "mouseSystem.h"

entity::entity(dimension aType) : type(aType) {}

entity::~entity() {
    renderSystem::getInstance()->unregisterEntity(this);
    mouseSystem::getInstance()->unregisterEntity(this);
}

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
    markDirty();
}

void entity::removeChild(entity* child) {
    if (!child) {
        return;
    }
    
    auto iter = std::find_if(childs.begin(), childs.end(), [&child](auto& element){
        return child == element.get();
    });
    if (iter == childs.end()) {
        return;
    }
    
    child->setParent({});
    childs.erase(iter);
    markDirty();
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

void entity::removeFromParent() {
    if (parent.expired()) {
        parent.lock()->removeChild(this);
        parent.lock()->markDirty();
    }
}

void entity::setWeakPointerThis(std::weak_ptr<entity> aWThis) {
    wThis = aWThis;
}

void entity::update(float dt) {
    for (auto& action : actions) {
        action->update(wThis, dt);
    }
    for (auto& child : childs) {
        child->update(dt);
    }
    auto forRemove = std::remove_if(actions.begin(), actions.end(), [this](auto& element){
        if (element->isEnd()) {
            element->end(wThis);
            return true;
        }
        return false;
    });
    if (forRemove != actions.end()) {
        actions.erase(forRemove);
    }
}

void entity::addAction(actionBase *action) {
    actions.emplace_back(std::move(action));
}

void entity::clearAllActions() {
    actions.clear();
}

bool entity::isDirty() const {
    for (const auto& component : components) {
        if (component) {
            if (component->isDirty()) {
                return true;
            }
        }
    }
    return dirty;
}

void entity::markDirty() {
    dirty = true;
}

void entity::unDirty() {
    dirty = false;
    for (const auto& component : components) {
        if (component) {
            component->unDirty();
        }
    }
}

void entity::setIgnoreSorting(bool value) {
    ignoreSorting = value;
}

bool entity::isIgnoreSorting() const {
    return ignoreSorting;
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
