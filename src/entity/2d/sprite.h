#pragma once

#include "node.h"

class sprite : public node {
public:
    sprite();
    ~sprite() = default;
    virtual void createCash() override;
    virtual void updateCash(size_t freeCashIdx, size_t busyCashIdx) override;
protected:
    class spriteCash : public nodeCash {
    public:
        spriteCash();
        ~spriteCash() = default;
    };
};
