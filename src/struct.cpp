#include "struct.h"

bool functionHelper::poinInQuad2d(const vec3f& pos, const vec3f& size, const vec3f& checkPoint) {
    return checkPoint[0] > pos[0] && checkPoint[0] < pos[0] + size[0] && checkPoint[1] > pos[1] && checkPoint[1] < pos[1] + size[1];
}

swapDirection functionHelper::getDirectionFromPoint(const vec3f& start, const vec3f& end, float distance) {
    
    bool seX = poinInQuad2d({start[0] - distance, start[1]}, {distance, distance}, end);
    bool esX = poinInQuad2d({start[0] + distance, start[1]}, {distance, distance}, end);
    bool seY = poinInQuad2d({start[0], start[1] - distance}, {distance, distance}, end);
    bool esY = poinInQuad2d({start[0], start[1] + distance}, {distance, distance}, end);
    
    if (seX || esX) {
        if (seY || esY) {
            return swapDirection::UNKNOWN;
        }
        return seX ? swapDirection::LEFT : swapDirection::RIGTH;
    }
    if (seY || esY) {
        if (seX || esX) {
            return swapDirection::UNKNOWN;
        }
        return seY ? swapDirection::TOP : swapDirection::BOT;
    }
    return swapDirection::UNKNOWN;
}
