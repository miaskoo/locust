#include "node.h"

class button : public node {
public:
    button();
    ~button();
    virtual void createCash() override;
    virtual void updateCash(size_t freeCashIdx, size_t busyCashIdx) override;
protected:
    class buttonCash : public nodeCash {
    public:
        buttonCash();
        ~buttonCash() = default;
    };
};
