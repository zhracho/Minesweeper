#pragma once
#include <vector>
#include "Tile.h"
#include <SFML/Graphics.hpp>
using namespace std;


class Board {

public:

    vector<vector<Tile*>> allTiles;
    int tileCounter;
    int onesPlace;
    int tensPlace;
    int hundredsPlace;
    bool isDebug;
    int numMines;
    bool isWon;
    bool isStarted;
    sf::Vector2f happyPosition;
    sf::Vector2f sadPosition;
    sf::Vector2f debugPosition;
    sf::Vector2f test1Position;
    sf::Vector2f test2Position;
    sf::Vector2f test3Position;

    sf::Sprite debug;
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    sf::Sprite happyFace;
    sf::Sprite number1;
    sf::Sprite number2;
    sf::Sprite number3;
    sf::Sprite number4;
    sf::Sprite number5;
    sf::Sprite number6;
    sf::Sprite number7;
    sf::Sprite number8;
    sf::Sprite faceLose;
    sf::Sprite faceWin;
    bool gameEnd;

    sf::Sprite flagCounter0;
    sf::Sprite flagCounter1;
    sf::Sprite flagCounter2;
    sf::Sprite flagCounter3;
    sf::Sprite flagCounter4;
    sf::Sprite flagCounter5;
    sf::Sprite flagCounter6;
    sf::Sprite flagCounter7;
    sf::Sprite flagCounter8;
    sf::Sprite flagCounter9;
    sf::Sprite flagCounterNegative;
private:

    int height;
    int width;
    int rows;
    int columns;

public:
    int tileCount;
    bool gameWin();
    void recursiveReveal(Tile* tile);
    void compare(sf::RenderWindow&window, int &place, int position);
    void testWins();
    void loadBoard(string boardName);
    void resetBoard();
    void updateBoard(sf::RenderWindow& window, sf::Vector2i& mousePosition);
    ~Board();
    Board();
    int getHeight();
    int getWidth();
    int getRows();
    int getColumns();
    void drawTiles(sf::RenderWindow& window);
    vector<Tile*> getNeighbors(int x, int y);

};



