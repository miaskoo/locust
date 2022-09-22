#include "bufferController.h"

bufferIdx bufferController::getTorusBufferIdx(unsigned int countSector) {
    auto iter = torusSectorToBuffers.find(countSector);
    if (iter != torusSectorToBuffers.end()) {
        return iter->second;
    }
    auto result = factoryBuffer::createTorusBuffer(countSector);
    torusSectorToBuffers[countSector] = result;
    return torusSectorToBuffers[countSector];
}
