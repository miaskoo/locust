#include "boardView.h"
#include "factoryEntity.h"
#include "transformComponent.h"
#include "textureComponent.h"
#include "constructorWindow.h"
#include "renderSystem.h"
#include "factoryAction.h"
#include "clickComponent.h"
#include "colorComponent.h"
#include "entity.h"

void boardView::init(unsigned int w, unsigned int h, vec2f aChipSize, const swapCallback& callback) {
    if (isInit) {
        return;
    }
    chipSize = aChipSize;
    chipButtons.resize(w);
    chipSprites.resize(w);
    for (auto aW = 0U; aW < w; aW++) {
        chipButtons[aW].reserve(h);
        chipSprites[aW].reserve(h);
        for (auto aH = 0U; aH < h; aH++) {
            auto result = factoryEntity::createSwapZone();
            result->setSize(chipSize);
            result->setAnchor(0.0f, 0.0f);
            result->setPivot(0.5f, 0.5f);
            result->getComponent<colorComponent>()->setColor(0, 0, 0, 0);
            result->getComponent<swapComponent>()->setSwapCallback(callback);
            chipButtons[aW].push_back(result);
            result->setPos(getPosFromId({aW, aH}));
            addChild(result);
            
            auto sprite = factoryEntity::createSprite();
            sprite->setSize(chipSize);
            sprite->setAnchor(0.0f, 0.0f);
            sprite->setPivot(0.5f, 0.5f);
            chipSprites[aW].push_back(sprite);
            addChild(sprite);
        }
    }

    chipSize = aChipSize;
    isInit = true;
}

void boardView::update(const std::vector<std::vector<chip>>& chips) {
    for (auto& aw : chips) {
        for (auto& awh : aw) {
            auto id = awh.getId();
            auto bindId = awh.getBindId();
            auto object = chipSprites[id.first][id.second];
            
            auto iter = states.find(id);
            if (iter == states.end()) {
                states[id] = chipState::IDLE;
            }
            else {
                if (iter->second == awh.getState()) {
                    if (awh.getState() != chipState::FALL) {
                        continue;
                    }
                }
            }
            states[id] = awh.getState();
            
            switch(awh.getState()) {
                case chipState::HIDE: {
                    countAction++;
                    color4b colorFadeOut = {255,255,255,0};
                    object->addAction(factoryAction::createChangeColorAction(colorFadeOut, timeFadeOutAction, [this, awh](){
                        hideChip(awh.getId());
                        countAction--;
                    }));
                    continue;
                    break;
                }
                case chipState::SHOW: {
                    countAction++;
                    showChip(awh.getId()); 
                    initViewChip(&awh);
                    object->getComponent<colorComponent>()->setColor(255,255,255,0);
                    color4b colorFadeIn = {255,255,255,255};
                    object->addAction(factoryAction::createChangeColorAction(colorFadeIn, timeFadeInAction, [this, awh](){
                        countAction--;
                    }));
                    continue;
                    break;
                }
                case chipState::IDLE: {
                    continue;
                    break;
                }
                default: {
                    break;
                }
            }
            
            auto targetPos = getPosFromId(bindId);
            countAction++;
            object->addAction(factoryAction::createMoveToAction(targetPos, timeMoveAction, [this](){
                countAction--;
            }));
        }
    }
}

void boardView::initViewChip(const chip *aChip) {
    if (!aChip) {
        return;
    }
    
    auto id = aChip->getId();
    auto bindId = aChip->getBindId();
    auto sprite = chipSprites[id.first][id.second];
    if (!sprite) {
        return;
    }

    sprite->setPos(getPosFromId(bindId));
    auto texture = getTextureFromColor(aChip->getColor());
    auto textureController = constructorWindow::getInstance()->getTextureController();
    auto normalTextureIdx = textureController->getTextureIdx(texture);
    sprite->getComponent<textureButtonComponent>()->setTexButtonIdx(normalTextureIdx, normalTextureIdx, normalTextureIdx);
}

void boardView::showChip(const pairInt &id) {
    auto object = chipSprites[id.first][id.second];
    if (!object) {
        return;
    }
    
    renderSystem::getInstance()->registerEntity(object.get());
}

void boardView::hideChip(const pairInt &id) {
    auto object = chipSprites[id.first][id.second];
    if (!object) {
        return;
    }
    
    renderSystem::getInstance()->unregisterEntity(object.get());
}


vec3f boardView::getPosFromId(const pairInt& id) {
    auto startX = chipSize.x() * 0.5f;
    auto startY = chipSize.y() * 0.5f;
    return {startX + chipSize.x() * id.first, startY + chipSize.y() * id.second};
}

std::string boardView::getTextureFromColor(chipColor color) {
    std::string result;
    switch(color) {
        case chipColor::GREEN: {
            result = "greenChip.png";
            break;
        }
        case chipColor::PINK: {
            result = "pinkChip.png";
            break;
        }
        case chipColor::RED: {
            result = "redChip.png";
            break;
        }
        case chipColor::YELLOW: {
            result = "yellowChip.png";
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

bool boardView::isHaveAction() {
    return countAction != 0U;
}

std::vector<std::vector<std::shared_ptr<entity>>>& boardView::getChipButtons() {
    return chipButtons;
}
