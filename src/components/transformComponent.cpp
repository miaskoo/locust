#include "transformComponent.h"
#include "entity.h"

transformComponent::transformComponent() {
    for (size_t n = 0; n < 16; n++) {
        cashRotate[n] = 0.0f;
    }
}

const vec3f& transformComponent::getCashPos() const {
    return cashPos;
}

const vec3f& transformComponent::getCashSize() const {
    return cashSize;
}

float const* transformComponent::getCashRotate() const {
    return cashRotate;
}

void transformComponent::setCashPos(vec3f aPos) {
    cashPos = aPos;
}

void transformComponent::setCashSize(vec3f aSize) {
    cashSize = aSize;
}

void transformComponent::setCashRotate(float *aRotate) {
    for (size_t n = 0; n < 16; n++) {
        cashRotate[n] = aRotate[n];
    }
}
