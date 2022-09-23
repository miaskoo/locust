#pragma once

#include "chipPlace.h"
#include "chip.h"
#include "struct.h"
#include <vector>

class entity;

class boardView {
public:
    boardView() = default;
    ~boardView() = default;
    
    void init(unsigned int w, unsigned int h);
    void initSprite(chip* aChip);
    void showSprite(const std::pair<unsigned int, unsigned int>& id);
    void hideSprite(const std::pair<unsigned int, unsigned int>& id);
    void update(const std::vector<std::vector<chipPlace>>& places);
   
private:
    vec3f getPosFromId(const std::pair<unsigned int, unsigned int>& id);
    
    bool isValidPos(vec3f& a, vec3f& b);
    std::string getTextureFromColor(chipColor color);
    
    std::vector<std::vector<std::shared_ptr<entity>>> chipSprite;
    vec2f chipSize;
};
