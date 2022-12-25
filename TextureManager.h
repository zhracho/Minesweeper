#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#include <string>
class TextureManager {

    //Only one unordered map of this instance is created in memory
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);


public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear(); //Acts as a destructor called at the end of main

};



