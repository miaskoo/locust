#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include "struct.h"

struct bufferIdx {
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    unsigned int countIdx;
};

class factoryBuffer {
public:
    static bufferIdx createTorusBuffer(int countSector);
    static bufferIdx createMesh(const std::vector<vec3f>& points);
private:
    static bufferIdx generateBufferIdx(const std::vector<vec3f>& verticesVector, const std::vector<vec2f>& textureCoordinateVector, const std::vector<unsigned int>& indicesVector);
    factoryBuffer() = default;
    ~factoryBuffer() = default;
};
