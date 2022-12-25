#include <fstream>
#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
using namespace std;
#include <vector>

Tile::Tile() {

    this->isHidden = true;
    this->revealMine = false;
    this->isRevealed = false;
    this->isFlag = false;
    this->isMine = false;
    this->mineCount = 0;
    this->position = sf::Vector2f(0,0);
}

Tile::Tile(bool isFlag, bool isMine, int mineCount, float x, float y) {
    this->isFlag = isFlag;
    this->isMine = isMine;
    this->mineCount = mineCount;
    this->position = sf::Vector2f(x,y);


}



bool Tile::isMined() {
    return isMine;
}

bool Tile::isFlagged() {
    return isFlag;
}

int Tile::GetMineCount() {
    return mineCount;
}


