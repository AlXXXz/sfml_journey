#pragma once

#include <SFML/Graphics.hpp>

class AssetManager {
    std::map<std::string, sf::Texture> m_Texture;
    static AssetManager* sInstance;

public:
    AssetManager();
    static sf::Texture &GetTexture(std::string const& fileName);
};

