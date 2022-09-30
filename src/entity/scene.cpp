#include "scene.h"

scene::scene() : entity(dimension::NONE) {}

void scene::updateCash(size_t freeCashIdx, size_t busyCashIdx) {
    updateCashChilds(freeCashIdx, busyCashIdx, this);
}

void scene::updateCashChilds(size_t freeCashIdx, size_t busyCashIdx, entity* obj) {
    for (auto& child : obj->getChilds()) {
        child->updateCash(freeCashIdx, busyCashIdx);
        if (child->isDirtyComponents()) {
            child->unDirtyComponents();
        }
        updateCashChilds(freeCashIdx, busyCashIdx, child.get());
    }
}

void scene::checkDirty(entity* obj, bool& result) {
    if (result) {
        return;
    }
    for (auto& child : obj->getChilds()) {
        if (child->isDirtyComponents()) {
            result = true;
            break;
        }
        checkDirty(child.get(), result);
        if (result) {
            break;
        }
    }
}

void scene::update(float dt) {
    entity::update(dt);
}
