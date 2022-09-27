#include "boardController.h"
#include "clickComponent.h"
#include <memory>

void boardController::updateView() {
    view->update(model.getChipPool());
}

void boardController::updateModel() {
    model.update();
}

void boardController::init(unsigned int w, unsigned int h, vec2f aChipSize, const swapCallback& callback) {
    model.init(w, h);
    
    view = std::make_shared<boardView>();
    view->setWeakPtrThis(view);
    view->setAnchor(0.5f, 0.5f);
    view->setPivot(0.5f, 0.5f);
    view->setScale(1.f, 1.f);
    view->setSize(aChipSize.x() * w, aChipSize.y() * h);
    view->init(w, h, aChipSize, callback);
}

void boardController::setDefaultBind() {
    model.setDefaultBind();
}

void boardController::generateBoardColor() {
    model.generateBoardColor();
}

void boardController::attachViewToEntity(std::shared_ptr<entity> scene) {
    if (!scene) {
        return;
    }
    view->removeFromParent();
    std::shared_ptr<entity> child = view;
    scene->addChild(child);
}

void boardController::swapChip(chip *caller, chip *receiver) {
    model.swapChipMove(caller, receiver);
}

chipPlace* boardController::getChipPlaceById(const pairInt &where) {
    return model.getChipPlaceById(where);
}

chipPlace* boardController::getChipPlaceByDirection(chip *object, swapDirection direction) {
    return model.getChipPlaceFromDirection(object, direction);
}

bool boardController::boardIsStable() {
    return model.isStable();
}

bool boardController::isHaveAnim() {
    return view->isHaveAction();
}

bool boardController::isLock() {
    return lock;
}

void boardController::setLock(bool value) {
    lock = value;
    for (auto& buttons : view->getChipButtons()) {
        for (auto& button : buttons) {
            button->getComponent<swapComponent>()->setClickable(!value);
        }
    }
}

std::vector<std::vector<std::shared_ptr<entity>>>& boardController::getChipButtons() {
    return view->getChipButtons();
}

void boardController::resetBoard() {
    setDefaultBind();
    generateBoardColor();
    initViewAllChips();
}

void boardController::initViewAllChips() {
    auto& chips = model.getChipPool();
    for (auto aW = 0U; aW < chips.size(); aW++) {
        for (auto aH = 0U; aH < chips[aW].size(); aH++) {
            view->initViewChip(&chips[aW][aH]);
        }
    }
}
