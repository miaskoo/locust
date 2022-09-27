#pragma once

#include "boardView.h"
#include "boardModel.h"

class boardController {
public:
    boardController() = default;
    ~boardController() = default;
    
    void init(unsigned int w, unsigned int h, vec2f aChipSize, const swapCallback& callback);
    void resetBoard();
    void attachViewToEntity(std::shared_ptr<entity> scene);
    void deattachView();
    void hideBoard();
    void showBoard();
    
    void updateView();
    void updateModel();
    
    chipPlace* getChipPlaceById(const pairInt& where);
    chipPlace* getChipPlaceByDirection(chip* object, swapDirection direction);
    
    void swapChip(chip* caller, chip* receiver);
    bool boardIsStable();
    void setLock(bool value);
    bool isLock();
    
    bool isHaveAnim();
    bool isHaveSwapMove();
    
    std::vector<std::vector<std::shared_ptr<entity>>>& getChipButtons();
private:
    void generateBoardColor();
    void setDefaultBind();
    void initViewAllChips();
    
    std::shared_ptr<boardView> view;
    boardModel model;
    
    bool lock = false;
    bool boardIsHide = false;
};
