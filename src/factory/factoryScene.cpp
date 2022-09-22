#include "factoryScene.h"

#include "struct.h"
#include "scene.h"

#include "transformComponent.h"
#include "clickComponent.h"
#include "colorComponent.h"
#include "renderComponent.h"
#include "textureComponent.h"

#include "factoryAction.h"
#include "factoryEntity.h"
#include "textureController.h"

#include <iostream>
#include <math.h>
#include <vector>

std::shared_ptr<scene> factoryScene::createGameScene() {
    auto mainScene = std::make_shared<scene>();
    mainScene->setWeakPointerThis(mainScene);
    
    return mainScene;
}
