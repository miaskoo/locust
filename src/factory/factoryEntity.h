#pragma once
#include <string>
#include <memory>

class entity;

class factoryEntity {
public:
    static std::shared_ptr<entity> createNode();
    static std::shared_ptr<entity> createLabel(const std::string& text = "");
    static std::shared_ptr<entity> createQuadrilateral();
    static std::shared_ptr<entity> createTorus(size_t countSector);
    static std::shared_ptr<entity> createSprite(const std::string& dirTexture = "");
    static std::shared_ptr<entity> createButton(const std::string& dirTextureNormal = "", const std::string& dirTextureCover = "", const std::string& dirTextureClick = "");
private:
    factoryEntity() = default;
    ~factoryEntity() = default;
};
