#pragma once
#include <SFML/Graphics.hpp>
class Tile {

public:
    sf::Vector2f position;
    bool isFlag;
    bool isMine;
    int mineCount;
    bool revealMine;
    bool debugMine;

public:

    bool isHidden;
    bool isRevealed;

    Tile();
    Tile(bool isFlag, bool isMine, int mineCount, float x, float y);
    int getWidth();
    int getHeight();

    bool isMined();
    bool isFlagged();
    int GetMineCount();



};


