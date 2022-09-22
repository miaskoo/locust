#include "node.h"
#include "transformComponent.h"

node::node() : entity(dimension::TWO) {
    addComponent<transformComponentMain<vec2f>>();
}

void node::updateCash(size_t freeCashIdx, size_t busyCashIdx) {
    getTransformComponent()->updateCashTransform(wThis);
    if (auto cash = getCash(freeCashIdx)) {
        copyComponent(cash->getComponent<transformComponent>());
    }
}

node::nodeCash::nodeCash() {
    addComponent<transformComponent>();
}
