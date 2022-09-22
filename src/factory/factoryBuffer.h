#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <vector>

struct bufferIdx {
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    unsigned int countIdx;
};

class factoryBuffer {
public:
    static bufferIdx createTorusBuffer(int countSector);
private:
    factoryBuffer() = default;
    ~factoryBuffer() = default;
};
