#pragma once

#include <utility>
#include "struct.h"

enum class chipColor {RED = 0U, GREEN = 1U, YELLOW = 2U, PINK = 3U, BLUE = 4U, NEGATIVE = 5U, SIZE = 6U, UNKNOWN = 99U};
enum class chipState {SWAP, RETURN, FALL, IDLE, HIDE, SHOW};

class chip {
public:
    chip() = delete;
    chip(const pairInt& aId);
    ~chip() = default;
    
    void setColor(chipColor aColor);
    void setBindId(const pairInt& aBindId);
    
    chipColor getColor() const;
    pairInt getBindId() const;
    pairInt getId() const;
    
    void setState(chipState aState);
    chipState getState() const;
    bool isAnimationProgress = false;
private:
    chipColor color = chipColor::UNKNOWN;
    pairInt bindId;
    pairInt chipId;
    
    chipState state = chipState::IDLE;
};
