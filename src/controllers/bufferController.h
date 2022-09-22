#pragma once
#include "factoryBuffer.h"

class bufferController {
public:
    bufferController() = default;
    ~bufferController() = default;
    
    bufferIdx getTorusBufferIdx(unsigned int countSector);
private:
    std::unordered_map<unsigned int, bufferIdx> torusSectorToBuffers;
};
