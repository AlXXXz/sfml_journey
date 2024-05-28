#include "AssetManager.hpp"
#include <assert.h>

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager() {
    assert(sInstance == nullptr);
    sInstance = this;
}

sf::Texture& AssetManager::GetTexture(std::string const& fileName) {
    auto& texMap = sInstance->m_Texture;
    auto pairFound = texMap.find(fileName);

    if (pairFound != texMap.end())
        return pairFound->second;
    else {
        auto& texture = texMap[fileName];
        texture.loadFromFile(fileName);
        return texture;
    }
}