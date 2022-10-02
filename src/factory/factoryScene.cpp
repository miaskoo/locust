#include "factoryScene.h"
#include "factoryEntity.h"

#include "struct.h"
#include "scene.h"

#include "srcMatch3/boardScene.h"

#include "renderComponent.h"
#include "textureComponent.h"

std::shared_ptr<scene> factoryScene::createGameScene() {
    auto mainScene = std::make_shared<boardScene>();
    mainScene->setWeakPtrThis(mainScene);
    mainScene->init(4, 4, {100, 100});
    mainScene->startGame();
    
    return mainScene;
}

std::shared_ptr<scene> factoryScene::createTestScene() {
    auto mainScene = std::make_shared<scene>();
    mainScene->setWeakPtrThis(mainScene);
    
    auto torus = factoryEntity::createTorus(10);
    torus->setRotate(vec3f(0, 45, 0));
    torus->setSize(vec3f(5,5,5));
    mainScene->addChild(torus);
    
    return mainScene;
}
