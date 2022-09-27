#include "boardModel.h"

void boardModel::init(unsigned int w, unsigned int h) {
    freeChipPool.clear();
    chipPool.clear();
    chipPlacePool.clear();
    
    chipPool.resize(w);
    for (auto aW = 0U; aW < h; aW++) {
        chipPool[aW].reserve(h);
        for (auto aH = 0U; aH < h; aH++) {
            chipPool[aW].emplace_back(chip(std::make_pair(aW, aH)));
        }
    }
    
    chipPlacePool.resize(w);
    for (int aW = 0U; aW < h; aW++) {
        chipPlacePool[aW].reserve(h);
        for (auto aH = 0U; aH < h; aH++) {
            chipPlacePool[aW].emplace_back(chipPlace(std::make_pair(aW, aH)));
        }
    }
    
    freeChipPool.reserve(w*h);
}

void boardModel::setDefaultBind() {
    for (auto w = 0U; w < chipPlacePool.size(); w++) {
        for (auto h = 0U; h < chipPlacePool[w].size(); h++) {
            auto& place = chipPlacePool[w][h];
            place.unbindChip();
            place.bindChip(&chipPool[w][h]);
        }
    }
    clearFree();
}

void boardModel::generateBoardColor() {
    auto maxColor = static_cast<size_t>(chipColor::SIZE);
    for (auto aW = 0U; aW < chipPool.size(); aW++) {
        for (auto aH = 0U; aH < chipPool[aW].size(); aH++) {
            auto& chipObj = chipPool[aW][aH];
            auto color = static_cast<chipColor>(rand()%maxColor);
            chipObj.setColor(color);
            if (!getMatch3Chips(&chipObj).empty()) {
                for (auto n = 0U; n < maxColor; n++) {
                    color = static_cast<chipColor>(n);
                    chipObj.setColor(color);
                    if (getMatch3Chips(&chipObj).empty()) {
                        break;
                    }
                }
            }
        }
    }
}

const std::vector<std::vector<chip>>& boardModel::getChipPool() const {
    return chipPool;
}

const std::vector<std::vector<chipPlace>>& boardModel::getChipPlacePool() const {
    return chipPlacePool;
}

bool boardModel::isStable() const {
    return dirtyChips.empty() && fallRows.empty() && freeChipPool.empty();
}

chip* boardModel::getChipById(const pairInt& chipId) {
    chip* result = nullptr;
    if (chipPool.size() > chipId.first) {
        if (chipPool[chipId.first].size() > chipId.second) {
            result = &chipPool[chipId.first][chipId.second];
        }
    }
    return result;
}

chipPlace* boardModel::getChipPlaceById(const pairInt& chipPlaceId) {
    chipPlace* result = nullptr;
    if (chipPlacePool.size() > chipPlaceId.first) {
        if (chipPlacePool[chipPlaceId.first].size() > chipPlaceId.second) {
            result = &chipPlacePool[chipPlaceId.first][chipPlaceId.second];
        }
    }
    return result;
}


chipPlace* boardModel::getPlaceForFall(chip* object) {
    auto chipPlace = getChipPlaceFromDirection(object, swapDirection::BOT);
    if (!chipPlace) {
        return nullptr;
    }
    return chipPlace->getBindedChip() ? nullptr : chipPlace;
}

void boardModel::swapChipMove(chip* caller, chip* receiver) {
    caller->setState(chipState::SWAP);
    receiver->setState(chipState::SWAP);
    addChipToDirty(caller);
    addChipToDirty(receiver);
    swapChips(caller, receiver);
}

void boardModel::update() {
    updateDirtyChips();
    updateFallRows();
    createNewChips();
    removeСleanСhipsFromDirty();
}

//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------

pairInt boardModel::getChipPlaceIdByDirection(chip *object, swapDirection direction) {
    auto id = object->getBindId();
    switch(direction) {
        case swapDirection::RIGTH: {
            id.first++;
            break;
        }
        case swapDirection::LEFT: {
            id.first--;
            break;
        }
        case swapDirection::TOP: {
            id.second--;
            break;
        }
        case swapDirection::BOT: {
            id.second++;
            break;
        }
        default: {
            break;
        }
    }
    return id;
}


chipPlace* boardModel::getChipPlaceFromDirection(chip* object, swapDirection direction) {
    return getChipPlaceById(getChipPlaceIdByDirection(object, direction));
}


void boardModel::addChipToFree(chip* aChip) {
    freeChipPool.push_back(aChip);
}

void boardModel::removeChipFromFree(chip* aChip) {
    auto iter = std::remove(freeChipPool.begin(), freeChipPool.end(), aChip);
    if (iter == freeChipPool.end()) {
        return;
    }
    freeChipPool.erase(iter);
}

chip* boardModel::getFreeChip() {
    if (freeChipPool.empty()) {
        return nullptr;
    }
    return freeChipPool.front();
}

void boardModel::clearFree() {
    freeChipPool.clear();
}


void boardModel::addChipToDirty(chip *dirty) {
    auto iter = std::find(dirtyChips.begin(), dirtyChips.end(), dirty);
    if (iter == dirtyChips.end()) {
        dirtyChips.push_back(dirty);
    }
}

void boardModel::removeСleanСhipsFromDirty() {
    auto iter = std::remove_if(dirtyChips.begin(), dirtyChips.end(), [](auto& element){
        return element->getState() == chipState::IDLE;
    });
    if (iter == dirtyChips.end()) {
        return;
    }
    dirtyChips.erase(iter);
}

chipPlace* boardModel::getPlaceForCreate(unsigned int column) {
    auto object = getChipPlaceById({column, 0});
    return object->getBindedChip() ? nullptr : object;
}

void boardModel::swapChips(chip *caller, chip *receiver) {
    auto placeCaller = getChipPlaceById(caller->getBindId());
    auto placeReceiver = getChipPlaceById(receiver->getBindId());
    placeCaller->unbindChip();
    placeReceiver->unbindChip();
    placeCaller->bindChip(receiver);
    placeReceiver->bindChip(caller);
}

void boardModel::fallChip(chipPlace* from, chipPlace* to) {
    to->bindChip(from->getBindedChip());
    from->unbindChip();
}

void boardModel::createNewChip(chip *what, chipPlace *where) {
    where->bindChip(what);
}

void boardModel::updateDirtyChips() {
    chip* invalidSpawChip = nullptr;
    auto localDirtyChips = dirtyChips;
    for (auto& dirtyChip : localDirtyChips) {
        switch (dirtyChip->getState()) {
            case chipState::SWAP: {
                if (!initMatch3ForDirtyChip(dirtyChip)) {
                    if (!invalidSpawChip) {
                        invalidSpawChip = dirtyChip;
                    }
                    else {
                        invalidSpawChip->setState(chipState::RETURN);
                        dirtyChip->setState(chipState::RETURN);
                        swapChips(invalidSpawChip, dirtyChip);
                        invalidSpawChip = nullptr;
                    }
                }
                break;
            }
            case chipState::HIDE: {
                dirtyChip->setState(chipState::IDLE);
                addChipToFree(dirtyChip);
                addToFallRow(dirtyChip);
                break;
            }
            case chipState::SHOW: {
                dirtyChip->setState(chipState::IDLE);
                addToFallRow(dirtyChip);
                break;
            }
            case chipState::FALL: {
                addToFallRow(dirtyChip);
                break;
            }
            case chipState::RETURN: {
                dirtyChip->setState(chipState::IDLE);
                break;
            }
            default: {
                break;
            }
        }
    }
    if (invalidSpawChip) {
        invalidSpawChip->setState(chipState::IDLE);
    }
}

void boardModel::addToFallRow(chip* object) {
    fallRows.insert(object->getBindId().first);
}

bool boardModel::initMatch3ForDirtyChip(chip *dirtyChip) {
    auto match3Chips = getMatch3Chips(dirtyChip);
    bool result = !match3Chips.empty();
    if (result) {
        for (auto& match3Chip : match3Chips) {
            addChipToDirty(match3Chip);
            match3Chip->setState(chipState::HIDE);
            getChipPlaceById(match3Chip->getBindId())->unbindChip();
        }
    }
    return result;
}

void boardModel::updateFallRows() {
    for (auto& fallRow : fallRows) {
        auto& placesChip = chipPlacePool[fallRow];
        for (int n = static_cast<int>(placesChip.size()) - 1; n > -1; n--) {
            auto& placeChip = placesChip[n];
            auto bindedChip = placeChip.getBindedChip();
            if (!bindedChip) {
                continue;
            }
            auto placeForFall = getPlaceForFall(bindedChip);
            if (placeForFall) {
                addChipToDirty(bindedChip);
                bindedChip->setState(chipState::FALL);
                fallChip(&placeChip, placeForFall);
            }
            else if (bindedChip->getState() == chipState::FALL) {
                if(!initMatch3ForDirtyChip(bindedChip)) {
                    bindedChip->setState(chipState::IDLE);
                }
            }
        }
    }
    fallRows.clear();
}


void boardModel::createNewChips() {
    for (auto n = 0U; n < chipPool.size(); n++) {
        if (auto emptyPlace = getPlaceForCreate(n)) {
            if (auto freeChip = getFreeChip()) {
                freeChip->setColor(static_cast<chipColor>(rand() % static_cast<unsigned int>(chipColor::SIZE)));
                addChipToDirty(freeChip);
                createNewChip(freeChip, emptyPlace);
                freeChip->setState(chipState::SHOW);
                removeChipFromFree(freeChip);
            }
        }
    }
}


//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------

std::list<chip*> boardModel::getMatch3Chips(chip *caller) {
    std::list<chip*> resultW;
    std::list<chip*> resultH;
    std::list<chip*> result;
    const auto dirW = {swapDirection::LEFT, swapDirection::RIGTH};
    const auto dirH = {swapDirection::TOP, swapDirection::BOT};
    for (auto& dir : dirW) {
        auto dirResult = getMatch3ChipsByDirection(caller, dir);
        std::copy(dirResult.begin(), dirResult.end(), std::back_inserter(resultW));
    }
    
    for (auto& dir : dirH) {
        auto dirResult = getMatch3ChipsByDirection(caller, dir);
        std::copy(dirResult.begin(), dirResult.end(), std::back_inserter(resultH));
    }
    
    if (resultW.size() >= needChipForMatch3) {
        std::copy(resultW.begin(), resultW.end(), std::back_inserter(result));
    }
    
    if (resultH.size() >= needChipForMatch3) {
        std::copy(resultH.begin(), resultH.end(), std::back_inserter(result));
    }
    
    if (result.size() >= needChipForMatch3) {
        result.push_back(caller);
    }
    
    return result;
}

std::list<chip*> boardModel::getMatch3ChipsByDirection(chip *caller, swapDirection direction) {
    const auto ignoreStates = {chipState::FALL, chipState::HIDE, chipState::SHOW};
    std::list<chip*> result;
    chip* directionChip = caller;
    auto place = getChipPlaceFromDirection(directionChip, direction);
    while (place) {
        directionChip = place->getBindedChip();
        if (!directionChip) {
            break;
        }
        if (std::find(ignoreStates.begin(), ignoreStates.end(), directionChip->getState()) != ignoreStates.end()) {
            break;
        }
        if (directionChip->getColor() == caller->getColor()) {
            result.push_back(directionChip);
            place = getChipPlaceFromDirection(directionChip, direction);
        }
        else {
            break;
        }
    }
    
    return result;
}
