#include "factoryScene.h"
#include "factoryEntity.h"

#include "struct.h"
#include "scene.h"

#include "srcMatch3/boardScene.h"

std::shared_ptr<scene> factoryScene::createGameScene() {
    auto mainScene = std::make_shared<boardScene>();
    mainScene->setWeakPtrThis(mainScene);
    mainScene->init(10, 10, {50, 50});
    mainScene->startGame();
    
    return mainScene;
}
