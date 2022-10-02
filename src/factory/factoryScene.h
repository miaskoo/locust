#pragma once

#include <memory>

class scene;

class factoryScene {
public:
    static std::shared_ptr<scene> createGameScene();
    static std::shared_ptr<scene> createTestScene();
private:
    factoryScene() = default;
    ~factoryScene() = default;
};
