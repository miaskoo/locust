#include "textureController.h"
#include "factoryTexture.h"
#include <assert.h>


unsigned int textureController::getTextureIdx(const std::string& dir) {
    auto iter = nameToTex.find(dir);
    if (iter != nameToTex.end()) {
        return iter->second;
    }
    return 0;
}

unsigned int textureController::getDefaultShaderProgramIdx() {
    return defaultShaderProgramIdx;
}

void textureController::init(const std::vector<std::string>& dirs) {
    if (inited) {
        return;
    }
    for (const auto& dir : dirs) {
        nameToTex[dir] = factoryTexture::createTexture(dir);
    }
    
    for (const auto& texIdx : nameToTex) {
        if (texIdx.second == 0) {
            assert(false && (texIdx.first + " texture not load").c_str());
        }
    }
    
    defaultShaderProgramIdx = factoryTexture::createDefaultShaderProgram();
    
    inited = true;
}
