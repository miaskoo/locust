#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class textureController {
public:
    textureController() = default;
    ~textureController() = default;
    
    void init(const std::vector<std::string>& dirs);
    unsigned int getTextureIdx(const std::string& dir);
    unsigned int getDefaultShaderProgramIdx();
private:
    bool inited = false;
    
    std::unordered_map<std::string, unsigned int> nameToTex;
    unsigned int defaultShaderProgramIdx = 0U;
};
