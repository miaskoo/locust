#pragma once
#include "node.h"
#include <string>

class label : public node {
public:
    label();
    ~label() = default;
    virtual void createCash() override;
protected:
    void updateCash(size_t freeCashIdx, size_t busyCashIdx) override;
    
    class labelCash : public nodeCash {
    public:
        labelCash();
        ~labelCash() = default;
    };
private:
    vec2f calcAutoSize(const std::string& text, void* font) const;
};
