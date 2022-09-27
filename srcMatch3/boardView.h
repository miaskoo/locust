#pragma once

#include "chipPlace.h"
#include "chip.h"
#include "struct.h"
#include <vector>
#include <map>
#include "node.h"

class boardView : public node {
public:
    boardView() = default;
    ~boardView() = default;
    
    void init(unsigned int w, unsigned int h, vec2f aChipSize, const swapCallback& callback);
    void initViewChip(const chip* aChip);
    void update(const std::vector<std::vector<chip>>& chips);
    bool isHaveAction();
    std::vector<std::vector<std::shared_ptr<entity>>>& getChipButtons();
private:
    void showChip(const pairInt& chipId);
    void hideChip(const pairInt& chipId);
    vec3f getPosFromId(const pairInt& chipId);
    
    std::string getTextureFromColor(chipColor color);
    
    bool isInit = false;
    
    vec2f chipSize;
    
    std::vector<std::vector<std::shared_ptr<entity>>> chipButtons;
    std::vector<std::vector<std::shared_ptr<entity>>> chipSprites;
    std::map<pairInt, chipState> states;
    
    unsigned int countAction = 0U;
    
    const unsigned int timeMoveAction = 250;
    const unsigned int timeFadeInAction = 200;
    const unsigned int timeFadeOutAction = 200;
};
