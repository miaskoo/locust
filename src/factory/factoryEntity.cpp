#include "factoryEntity.h"
#include "node.h"
#include "label.h"
#include "object3d.h"
#include "sprite.h"
#include "button.h"
#include "transformComponent.h"
#include "renderComponent.h"
#include "textureComponent.h"

#include "textureController.h"
#include "bufferController.h"
#include "constructorWindow.h"

#include "struct.h"

#ifdef MACOS
#include "GLUT/glut.h"
#else
#include "glew/glew.h"
#include "freeglut/freeglut.h"
#endif

std::shared_ptr<entity> factoryEntity::createNode() {
    auto result = std::make_shared<node>();
    result->setWeakPointerThis(result);
    auto component = result->getTransformComponent();
    component->setAnchor({0.5f, 0.5f});
    component->setPivot({0.5f, 0.5f});
    component->setScale({1.f, 1.f});
    result->createCash();
    return result;
}

std::shared_ptr<entity> factoryEntity::createLabel(const std::string& text) {
    auto result = std::make_shared<label>();
    result->setWeakPointerThis(result);
    auto component = result->getTransformComponent();
    component->setAnchor({0.5f, 0.5f});
    component->setPivot({0.5f, 0.5f});
    component->setScale({1.f, 1.f});
    result->getComponent<labelComponent>()->setText(text);
    result->getComponent<labelComponent>()->setFont(GLUT_BITMAP_HELVETICA_18);
    result->createCash();
    return result;
}

std::shared_ptr<entity> factoryEntity::createQuadrilateral() {
    auto result = std::make_shared<object3d>();
    result->setWeakPointerThis(result);
    auto component = result->getTransformComponent();
    component->setScale({1.f, 1.f, 1.f});
    component->setAnchor(vec3f({0.5f,0.5f,0.0f}));
    component->setPivot(vec3f({0.5f,0.5f,0.0f}));
    result->createCash();
    return result;
}

std::shared_ptr<entity> factoryEntity::createTorus(size_t countSector) {
    auto result = std::make_shared<object3d>();
    result->setWeakPointerThis(result);
    auto component = result->getTransformComponent();
    component->setScale({1.f, 1.f, 1.f});
    component->setAnchor(vec3f({0.5f,0.5f,0.0f}));
    component->setPivot(vec3f({0.5f,0.5f,0.0f}));
    result->createCash();
    
    auto buff = constructorWindow::getInstance()->getBufferController()->getTorusBufferIdx(countSector);
    result->getComponent<bufferComponent>()->setBuffIdx(buff.vao);
    result->getComponent<bufferComponent>()->setBuffSize(buff.countIdx);
    result->getComponent<bufferComponent>()->setCullFaceMode(true);
    return result;
}

std::shared_ptr<entity> factoryEntity::createSprite(const std::string& dirTexture) {
    auto result = std::make_shared<sprite>();
    result->setWeakPointerThis(result);
    auto component = result->getTransformComponent();
    component->setAnchor({0.5f,0.5f});
    component->setPivot({0.5f,0.5f});
    component->setScale({1.f,1.f});
    
    result->getComponent<textureComponent>()->setTexIdx(constructorWindow::getInstance()->getTextureController()->getTextureIdx(dirTexture));
    result->createCash();
    return result;
}

std::shared_ptr<entity> factoryEntity::createButton(const std::string& dirTextureNormal, const std::string& dirTextureCover, const std::string& dirTextureClick) {
    std::shared_ptr<entity> result = std::make_shared<button>();
    result->setWeakPointerThis(result);
    auto component = result->getTransformComponent();
    component->setScale({1.f, 1.f});
    component->setAnchor({0.5, 0.5});
    component->setPivot({0.5, 0.5});
    
    auto texController = constructorWindow::getInstance()->getTextureController();
    result->getComponent<textureButtonComponent>()->setTexButtonIdx(
        texController->getTextureIdx(dirTextureNormal),
        texController->getTextureIdx(dirTextureCover),
        texController->getTextureIdx(dirTextureClick));
    result->createCash();
    return result;
}
