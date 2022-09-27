#pragma once

#include "node.h"

class swapZone : public node {
public:
    swapZone();
    ~swapZone() = default;
    virtual void createCash() override;
    virtual void updateCash(size_t freeCashIdx, size_t busyCashIdx) override;
protected:
    class swapZoneCash : public nodeCash {
    public:
        swapZoneCash();
        ~swapZoneCash() = default;
    };
};

