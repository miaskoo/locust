#include "boardView.h"
#include "factoryEntity.h"
#include "transformComponent.h"
#include "textureComponent.h"
#include "constructorWindow.h"
#include "renderSystem.h"
#include "factoryAction.h"
#include "entity.h"

void boardView::init(unsigned int w, unsigned int h) {
    chipSprite.reserve(w);
    for (auto aW = 0U; aW < w; aW++) {
        chipSprite[aW].reserve(h);
        for (auto aH = 0U; aH < h; aH++) {
            chipSprite[aW].push_back(factoryEntity::createSprite());
        }
    }
}

void boardView::update(const std::vector<std::vector<chipPlace>>& places) {
    for (auto& placeW : places) {
        for (auto& placeWH : placeW) {
            auto bindedChip = placeWH.getBindedChip();
            if (!bindedChip) {
                continue;
            }
            auto id = bindedChip->getId();
            auto bindId = bindedChip->getBindId();
            auto sprite = chipSprite[id.first][id.second];
            
            if (sprite->getCountAction() > 0U) {
                continue;
            }
            
            auto supposedPos = getPosFromId(bindId);
            auto realPos = sprite->getTransformComponent()->getPos();
            if (!isValidPos(supposedPos, realPos)) {
                sprite->addAction(factoryAction::createMoveToAction());
            }
        }
    }
}

void boardView::initSprite(chip *aChip) {
    if (!aChip) {
        return;
    }
    
    auto id = aChip->getId();
    auto bindId = aChip->getBindId();
    auto sprite = chipSprite[id.first][id.second];
    if (!sprite) {
        return;
    }
    
    sprite->setPos(getPosFromId(bindId));
    auto texture = getTextureFromColor(aChip->getColor());
    sprite->getComponent<textureComponent>()->setTexIdx(constructorWindow::getInstance()->getTextureController()->getTextureIdx(texture));
}

void boardView::showSprite(const std::pair<unsigned int, unsigned int> &id) {
    auto sprite = chipSprite[id.first][id.second];
    if (!sprite) {
        return;
    }
    
    renderSystem::getInstance()->unregisterEntity(sprite.get());
}

void boardView::hideSprite(const std::pair<unsigned int, unsigned int> &id) {
    auto sprite = chipSprite[id.first][id.second];
    if (!sprite) {
        return;
    }
    
    renderSystem::getInstance()->registerEntity(sprite.get());
}


vec3f boardView::getPosFromId(const std::pair<unsigned int, unsigned int>& id) {
    return {chipSize.x() * id.first, chipSize.y() * id.second};
}

bool boardView::isValidPos(vec3f &a, vec3f &b) {
    return a.x() + 1.f > b.x() && a.x() - 1.f < b.x() && a.y() + 1.f > b.y() && a.y() - 1.f < b.x();
}

std::string boardView::getTextureFromColor(chipColor color) {
    std::string result;
    switch(color) {
        case chipColor::RED: {
            result = "red.png";
            break;
        }
        case chipColor::BLUE: {
            result = "blue.png";
            break;
        }
        case chipColor::PURPURE: {
            result = "purpure.png";
            break;
        }
        case chipColor::GREEN: {
            result = "green.png";
            break;
        }
        default: {
            break;
        }
    }
}
