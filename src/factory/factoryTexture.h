#pragma once

#include <unordered_map>
#include <string>

class factoryTexture {
public:
    static unsigned int createDefaultShaderProgram();
    static unsigned int createTexture(const std::string& dir);
private:
    factoryTexture() = default;
    ~factoryTexture() = default;
};
