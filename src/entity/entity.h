#pragma once

#include <vector>
#include <array>
#include "struct.h"
#include "componentContainer.h"
#include "actionBase.h"

class transformComponentInterface;

class entityCash : public componentContainer {
protected:
    ~entityCash() = default;
    entityCash() = default;
};

class entity : public componentContainer {
    friend class factoryEntity;
public:
    ~entity();
    dimension getDimension() const;
    
    std::shared_ptr<entity> getParent();
    const std::vector<std::shared_ptr<entity>>& getChilds();
    
    void reserveChild(size_t count);
    void addChild(std::shared_ptr<entity>& child);
    
    void addAction(action::actionBase* action);
    size_t getCountAction();
    void clearAllActions();
    
    bool isDirtyComponents() const;
    void unDirtyComponents();
    
    bool isDirty() const;
    void markDirty();
    void markDirtyChilds();
    void unDirty();
    
    void setIgnoreSorting(bool value);
    bool isIgnoreSorting() const;
    
    virtual void updateCash(size_t freeCashIdx, size_t busyCashIdx) = 0;
    
    std::shared_ptr<entityCash> getCash(size_t cashIdx);
    
    void setPos(vec3f pos);
    void setSize(vec3f size);
    void setRotate(vec3f rotate);
    void setAnchor(vec2f anchor);
    void setPivot(vec2f pivot);
    void setScale(vec3f scale);
    void setPos(float x, float y);
    void setSize(float x, float y, float z = 0.f);
    void setRotate(float x, float y, float z = 0.f);
    void setAnchor(float x, float y);
    void setPivot(float x, float y);
    void setScale(float x, float y, float z = 0.f);
    transformComponentInterface* getTransformComponent();
    
    std::weak_ptr<entity> getWeakPtr();
    void setWeakPtrThis(std::weak_ptr<entity> aWThis);
    
    virtual void update(float dt);
    
    void markDelete();
    void unMarkDelete();
    bool isNeedDelete();
    
    void setZOrder(unsigned int aZOrder);
    unsigned int getZOrder();
    
    void registerSystems();
    void unregisterSystems();
protected:
    entity() = delete;
    entity(dimension aType);
    
    void setParent(std::weak_ptr<entity> aParent);
    
    virtual void createCash() {}
    
    std::array<std::shared_ptr<entityCash>, static_cast<size_t>(typeCash::COUNT)> cashArray;
    std::weak_ptr<entity> wThis;
    
    void unregisterSystemsChilds();
    void setSystemRegister(bool value);
    bool isSystemRegister();
private:
    void removeChild(entity* child);
    
    const dimension type;
    
    std::weak_ptr<entity> parent;
    std::vector<std::shared_ptr<entity>> childs;

    std::vector<std::shared_ptr<action::actionBase>> actions;
    
    bool dirty = false;
    bool ignoreSorting = false;
    bool needDelete = false;
    unsigned int zOrder = 0U;
    bool systemRegister = false;
};
