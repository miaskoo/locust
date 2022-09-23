#pragma once
#include <utility>

enum class chipColor {RED, BLUE, GREEN, PURPURE, UNKNOWN};

class chip {
public:
    chip() = delete;
    chip(const std::pair<unsigned int, unsigned int>& aId);
    ~chip() = default;
    
    void setColor(chipColor aColor);
    void setBindId(const std::pair<unsigned int, unsigned int>& aBindId);
    
    chipColor getColor() const;
    std::pair<unsigned int, unsigned int> getBindId() const;
    std::pair<unsigned int, unsigned int> getId() const;
private:
    chipColor color = chipColor::UNKNOWN;
    std::pair<unsigned int, unsigned int> bindId;
    std::pair<unsigned int, unsigned int> id;
};
