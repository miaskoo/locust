#pragma once
#include "entity.h"
#include <list>

class scene : public entity {
public:
    scene();
    ~scene() = default;
    virtual void createCash() override {}
    virtual void updateCash(size_t freeCashIdx, size_t busyCashIdx) override;
    void createNewCash(entity* obj, std::list<std::shared_ptr<entityCash>>& cashList);
    void checkDirty(entity* obj, bool& result);
protected:
    void updateCashChilds(size_t freeCashIdx, size_t busyCashIdx, entity* obj);
};
