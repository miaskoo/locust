#pragma once
#include <memory>

class scene;

class factoryScene {
public:
    static std::shared_ptr<scene> createGameScene();
private:
    factoryScene() = default;
    ~factoryScene() = default;
};
