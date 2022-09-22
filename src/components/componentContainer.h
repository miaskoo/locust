#pragma once
#include <array>
#include <memory>
#include "componentBase.h"

class componentContainer {
public:
    template<typename T>
    T* getComponent() {
        auto idx = static_cast<size_t>(T::getType());
        if (!components[idx]) {
            return nullptr;
        }
        return static_cast<T*>(components[idx].get());
    }
    
    template<typename T>
    T* addComponent() {
        auto idx = static_cast<size_t>(T::getType());
        if (components[idx]) {
            return static_cast<T*>(components[idx].get());
        }
        components[idx] = std::make_shared<T>();
        return static_cast<T*>(components[idx].get());
     }
    
    template<typename T>
    void copyComponent(T* dst) {
        if (!dst) {
            return;
        }
        auto head = getComponent<T>();
        *dst = *head;
    }
protected:
    componentContainer() = default;
    virtual ~componentContainer() = default;
    std::array<std::shared_ptr<componentBaseInterface>, static_cast<size_t>(componentId::SIZE)> components;
};
