#include "factoryScene.h"
#include "factoryEntity.h"

#include "struct.h"
#include "scene.h"

#include "srcMatch3/boardScene.h"

std::shared_ptr<scene> factoryScene::createGameScene() {
    auto mainScene = std::make_shared<boardScene>();
    mainScene->setWeakPtrThis(mainScene);
    mainScene->init(4, 4, {100, 100});
    mainScene->startGame();
    
    return mainScene;
}
