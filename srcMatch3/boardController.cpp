#include "boardController.h"

void boardController::updateView() {
    visual.update(model.getChipPlacePool());
}

void boardController::init(unsigned int w, unsigned int h) {
    model.init(w, h);
    visual.init(w, h);
}

void boardController::initNewGame(const std::vector<std::vector<chipColor>>& colors) {
    model.clearFree();
    for (auto aW = 0U; aW < colors.size(); aW++) {
        for (auto aH = 0U; aH < colors[aW].size(); aH++) {
            auto chip = model.getChip({aW, aH});
            auto place = model.getChipPlace({aW, aH});
            place->unbindChip();
            place->bindChip(chip);
            chip->setColor(colors[aW][aH]);
            visual.initSprite(chip);
            visual.showSprite(chip->getId());
        }
    }
}

void boardController::swapChip(const std::pair<unsigned int, unsigned int> &from, const std::pair<unsigned int, unsigned int> &to) {
    auto fromPlace = model.getChipPlace(from);
    auto toPlace = model.getChipPlace(to);
    auto chipFrom = fromPlace->getBindedChip();
    auto chipTo = fromPlace->getBindedChip();
    fromPlace->unbindChip();
    toPlace->unbindChip();
    fromPlace->bindChip(chipTo);
    toPlace->bindChip(chipFrom);
    updateView();
}

void boardController::removeChip(const std::pair<unsigned int, unsigned int>& where) {
    auto place = model.getChipPlace(where);
    auto someChip = place->getBindedChip();
    place->unbindChip();
    model.setChipFree(someChip);
    visual.hideSprite(someChip->getId());
}

void boardController::spawnChip(const std::pair<unsigned int, unsigned int>& where) {
    auto place = model.getChipPlace(where);
    auto chip = model.getFreeChip();
    if (chip) {
        place->bindChip(chip);
        model.setChipBusy(chip);
        visual.showSprite(chip->getId());
    }
}
