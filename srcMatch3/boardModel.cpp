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

void boardModel::setChipFree(chip* aChip) {
    if (!aChip) {
        return;
    }
    freeChipPool.push_back(aChip);
}

void boardModel::setChipBusy(chip* aChip) {
    auto iter = std::remove(freeChipPool.begin(), freeChipPool.end(), aChip);
    if (iter == freeChipPool.end()) {
        return;
    }
    freeChipPool.erase(iter);
}

const std::vector<std::vector<chipPlace>>& boardModel::getChipPlacePool() const {
    return chipPlacePool;
}

chip* boardModel::getChip(const std::pair<unsigned int, unsigned int>& chipId) {
    chip* result = nullptr;
    if (chipPool.size() < chipId.first) {
        if (chipPool[chipId.first].size() < chipId.second) {
            result = &chipPool[chipId.first][chipId.second];
        }
    }
    return result;
}

chipPlace* boardModel::getChipPlace(const std::pair<unsigned int, unsigned int>& chipPlaceId) {
    chipPlace* result = nullptr;
    if (chipPlacePool.size() < chipPlaceId.first) {
        if (chipPlacePool[chipPlaceId.first].size() < chipPlaceId.second) {
            result = &chipPlacePool[chipPlaceId.first][chipPlaceId.second];
        }
    }
    return result;
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
