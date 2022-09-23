#include "factoryScene.h"
#include "factoryEntity.h"

#include "struct.h"
#include "scene.h"

#include "srcMatch3/board.h"

std::shared_ptr<scene> factoryScene::createGameScene() {
    auto mainScene = std::make_shared<scene>();
    mainScene->setWeakPointerThis(mainScene);
    
    auto b = std::make_shared<board>();
    b->setWeakPointerThis(b);
    mainScene->addChild(b);
    
    return mainScene;
}
