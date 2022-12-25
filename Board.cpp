#include "Board.h"
#include "Random.h"
#include <fstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <cmath>

Board::Board() {
    isWon = true;

    isStarted = false;
    gameEnd = false;

    ifstream file;
    file.open("boards/config.cfg");

    string columns;
    string rows;
    string mines;
    if(file.is_open()) {
        getline(file, columns);
        getline(file, rows);
        getline(file, mines);
    }

    this->columns = stoi(columns);
    this->rows = stoi(rows);
    this->isDebug = false;


    width = stoi(columns) * 32;
    height = (stoi(rows) * 32) + 100;
    numMines = stoi(mines);

    this->tileCounter = numMines;


    int temp = tileCounter;
    this->onesPlace = temp % 10;
    temp /=10;

    this->tensPlace = tileCounter % 10;
    temp/=10;

    this->hundredsPlace = temp%10;

    vector<vector<Tile*>> copyTiles(this->columns);
    allTiles = copyTiles;

    for(int i = 0; i< getColumns(); i++){
        for(int j = 0; j < getRows(); j++){
            allTiles.at(i).push_back(new Tile());
        }
    }

    int mineCounter = 0;

    while(mineCounter != numMines){

        int randomPosX = Random::Int(0,getColumns()-1);
        int randomPosY = Random::Int(0,getRows()-1);

        if(!allTiles.at(randomPosX).at(randomPosY)->isMine){
            allTiles.at(randomPosX).at(randomPosY)->isMine = true;
            mineCounter++;

        }

    }
}

int Board::getHeight() {
    return height;
}

int Board::getWidth() {
    return width;
}

int Board::getRows() {
    return rows;
}

int Board::getColumns() {
    return columns;
}
vector<Tile*> Board::getNeighbors(int x, int y) {

    vector<Tile*> neighborTiles;

    if(x -1 >= 0 && y-1>= 0) {
        //Bottom of left grid
        neighborTiles.push_back(allTiles.at(x - 1).at(y - 1));
    }

    if(x >= 0 && y-1 >=0) {

        //Bottom middle of grid
        neighborTiles.push_back(allTiles.at(x).at(y - 1));
    }

    if(x+1 <= getColumns() -1 && y -1 >= 0) {

        //Bottom right of the grid
        neighborTiles.push_back(allTiles.at(x + 1).at(y - 1));
    }

    if(x+1 <= getColumns() -1) {
        //Leftmost neighbor grid
        neighborTiles.push_back(allTiles.at(x + 1).at(y));
    }

    if(x-1 >=0) {

        //Rightmost neighbor grid
        neighborTiles.push_back(allTiles.at(x - 1).at(y));
    }

    if(y+1 <= getRows()-1) {
        //Top middle of the grid
        neighborTiles.push_back(allTiles.at(x).at(y + 1));
    }

    if(x-1 >= 0 && y+1 <= getRows()-1) {

        //Top left of the grid
        neighborTiles.push_back(allTiles.at(x - 1).at(y + 1));
    }

    if(x+1 <= getColumns()-1 && y+1 <= getRows()-1){

        //Top right of the grid
        neighborTiles.push_back(allTiles.at(x + 1).at(y + 1));
    }

    return neighborTiles;


}
void Board::drawTiles(sf::RenderWindow& window) {

    this->flagCounter0.setTexture(TextureManager::GetTexture("digits"));
    flagCounter0.setTextureRect(sf::IntRect(0,0,21,32));

    this->flagCounter1.setTexture(TextureManager::GetTexture("digits"));
    flagCounter1.setTextureRect(sf::IntRect(21,0,21,32));

    this->flagCounter2.setTexture(TextureManager::GetTexture("digits"));
    flagCounter2.setTextureRect(sf::IntRect(21*2,0,21,32));

    this->flagCounter3.setTexture(TextureManager::GetTexture("digits"));
    flagCounter3.setTextureRect(sf::IntRect(21*3,0,21,32));

    this->flagCounter4.setTexture(TextureManager::GetTexture("digits"));
    flagCounter4.setTextureRect(sf::IntRect(21*4,0,21,32));

    this->flagCounter5.setTexture(TextureManager::GetTexture("digits"));
    flagCounter5.setTextureRect(sf::IntRect(21*5,0,21,32));

    this->flagCounter6.setTexture(TextureManager::GetTexture("digits"));
    flagCounter6.setTextureRect(sf::IntRect(21*6,0,21,32));

    this->flagCounter7.setTexture(TextureManager::GetTexture("digits"));
    flagCounter7.setTextureRect(sf::IntRect(21*7,0,21,32));

    this->flagCounter8.setTexture(TextureManager::GetTexture("digits"));
    flagCounter8.setTextureRect(sf::IntRect(21*8,0,21,32));

    this->flagCounter9.setTexture(TextureManager::GetTexture("digits"));
    flagCounter9.setTextureRect(sf::IntRect(21*9,0,21,32));

    this->flagCounterNegative.setTexture(TextureManager::GetTexture("digits"));
    flagCounterNegative.setTextureRect(sf::IntRect(21*10,0,21,32));



    int temp = abs(tileCounter);

    this->onesPlace = temp % 10;
    temp /=10;


    this->tensPlace = temp % 10;
    temp/=10;

    this->hundredsPlace = temp%10;

    compare(window,onesPlace, 3);
    compare(window, tensPlace,2);


    if(tileCounter < 0) {
        flagCounterNegative.setPosition(0, getHeight() - 100);
        window.draw(flagCounterNegative);
    }
        compare(window, hundredsPlace, 1);




    vector<sf::Sprite> tiles;
    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));

    this->happyFace.setTexture(TextureManager::GetTexture("face_happy"));
    happyFace.setOrigin(happyFace.getLocalBounds().width/2, happyFace.getLocalBounds().height/2);
    happyFace.setPosition(window.getSize().x/2, getHeight()-68);
    happyPosition = happyFace.getPosition();

    this->debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setOrigin(debug.getLocalBounds().width/2, debug.getLocalBounds().height/2);
    debug.setPosition(window.getSize().x/2 +128, getHeight()-68);
    debugPosition =debug.getPosition();

    this->test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setOrigin(test1.getLocalBounds().width/2, test1.getLocalBounds().height/2);
    test1.setPosition(debug.getPosition().x +64, getHeight()-68);
    test1Position = test1.getPosition();

    this->test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setOrigin(test2.getLocalBounds().width/2, test2.getLocalBounds().height/2);
    test2.setPosition(test1.getPosition().x +64, getHeight()-68);
    test2Position = test2.getPosition();

    this->test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.setOrigin(test3.getLocalBounds().width/2, test3.getLocalBounds().height/2);
    test3.setPosition(test2.getPosition().x +64, getHeight()-68);
    test3Position = test3.getPosition();

    sf::Sprite revealedTile(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));

    for(int i = 0; i < getColumns(); i++){
        for(int j = 0; j < getRows(); j++){

            if(allTiles.at(i).at(j)->isHidden ){
                this->allTiles.at(i).at(j)->position.x = i*32;
                this->allTiles.at(i).at(j)->position.y = j*32;
                hiddenTile.setPosition(i*32,j*32);
                tiles.push_back(hiddenTile);
            }else{

                revealedTile.setPosition(i*32,j*32);
                this->allTiles.at(i).at(j)->position.x = i*32;
                this->allTiles.at(i).at(j)->position.y = j*32;
                tiles.push_back(revealedTile);

                vector<Tile*> neighbors = getNeighbors(i,j);
                int count = 0;

                for(unsigned int z = 0; z < neighbors.size(); z++){
                    if(neighbors.at(z)->isMine){
                        count++;
                    }
                }

                if(!allTiles.at(i).at(j)->isMine && !allTiles.at(i).at(j)->isFlag) {
                    switch (count) {
                        case 1:
                            this->number1.setTexture(TextureManager::GetTexture("number_1"));
                            number1.setPosition(revealedTile.getPosition());
                            tiles.push_back(number1);
                            break;
                        case 2:
                            this->number2.setTexture(TextureManager::GetTexture("number_2"));
                            number2.setPosition(revealedTile.getPosition());
                            tiles.push_back(number2);
                            break;
                        case 3:
                            this->number3.setTexture(TextureManager::GetTexture("number_3"));
                            number3.setPosition(revealedTile.getPosition());

                            tiles.push_back(number3);
                            break;
                        case 4:
                            this->number4.setTexture(TextureManager::GetTexture("number_4"));
                            number4.setPosition(revealedTile.getPosition());

                            tiles.push_back(number4);
                            break;
                        case 5:
                            this->number5.setTexture(TextureManager::GetTexture("number_5"));
                            number5.setPosition(revealedTile.getPosition());

                            tiles.push_back(number5);
                            break;
                        case 6:
                            this->number6.setTexture(TextureManager::GetTexture("number_6"));
                            number6.setPosition(revealedTile.getPosition());

                            tiles.push_back(number6);
                            break;
                        case 7:
                            this->number7.setTexture(TextureManager::GetTexture("number_7"));
                            number7.setPosition(revealedTile.getPosition());

                            tiles.push_back(number7);
                            break;

                        case 8:
                            this->number8.setTexture(TextureManager::GetTexture("number_8"));
                            number8.setPosition(revealedTile.getPosition());
                            tiles.push_back(number8);
                            break;

                        default:
                            recursiveReveal(allTiles.at(i).at(j));

                    }
                }

            }

            if(allTiles.at(i).at(j)->isFlag){
                flag.setPosition(i*32,j*32);
                tiles.push_back(flag);

            }

            if(allTiles.at(i).at(j)->isMine && (allTiles.at(i).at(j)->revealMine || isDebug)){
                mine.setPosition(i*32,j*32);
                tiles.push_back(mine);
            }


        }
    }

    for(unsigned int i = 0; i < tiles.size(); i++){
        window.draw(tiles.at(i));
    }


    if(isWon == false && isStarted){

        this->faceLose.setTexture(TextureManager::GetTexture("face_lose"));
        faceLose.setOrigin(faceLose.getLocalBounds().width/2, faceLose.getLocalBounds().height/2);
        faceLose.setPosition(window.getSize().x/2, getHeight()-68);
        window.draw(faceLose);

        for(int i = 0 ; i < getColumns(); i++){
            for(int j = 0; j < getRows(); j++){
                if(allTiles.at(i).at(j)->revealMine == false && allTiles.at(i).at(j)->isMine && isStarted){
                    allTiles.at(i).at(j)->revealMine = true;
                    allTiles.at(i).at(j)->isHidden = false;
                    allTiles.at(i).at(j)->isRevealed = true;
                }
            }
        }
    }else if(!isStarted && isWon && !gameWin()){
        window.draw(happyFace);
    }else if(gameWin()){
        for(int i = 0; i < getColumns(); i++){
            for(int j = 0; j < getRows(); j++){
                if(allTiles.at(i).at(j)->isMine){
                    allTiles.at(i).at(j)->isFlag = true;
                }
            }
        }

        tileCounter = 0;

        this->faceWin.setTexture(TextureManager::GetTexture("face_win"));
        faceWin.setOrigin(faceWin.getLocalBounds().width/2, faceWin.getLocalBounds().height/2);
        faceWin.setPosition(window.getSize().x/2, getHeight()-68);
        window.draw(faceWin);

    }

    window.draw(debug);
    window.draw(test1);
    window.draw(test2);
    window.draw(test3);

}

void Board::loadBoard(string boardName) {

    ifstream file;
    file.open(boardName);

    char tileSetup;
    unsigned int i = 0;
    unsigned int j = 0;

    numMines = 0;
    tileCounter = 0;

    if(file.is_open()){
        while(file >> tileSetup){

            if(tileSetup == '0'){
                allTiles.at(i).at(j)->isHidden = true;
                allTiles.at(i).at(j)->isMine = false;
            }else{
                allTiles.at(i).at(j)->isMine = true;
                numMines++;
                tileCounter++;
            }

            i++;

            if(tileSetup == '\n' || i >= getColumns()){
                i = 0;
                j++;
            }

        }

    }
    file.close();

}

Board::~Board() {

    for(int i = 0; i < getColumns(); i++){
        for(int j = 0; j < getRows(); j++){
            delete allTiles.at(i).at(j);
        }
    }
}

void Board::updateBoard(RenderWindow &window, sf::Vector2i& mousePosition) {
    mousePosition = sf::Mouse::getPosition(window);


    try {

        if (mousePosition.y / 32 < getRows() && !gameEnd && !gameWin()) {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                !allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isFlagged()) {

                allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isHidden = false;

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isMine &&
                !allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isFlag) {
                allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->revealMine = true;

                isStarted = true;
                isWon = false;
                gameEnd = true;

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
                allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isHidden) {

                if (allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isFlag) {
                    allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isFlag = false;
                    tileCounter++;

                }else if(allTiles.at(mousePosition.x/32).at(mousePosition.y/32)->isRevealed && allTiles.at(mousePosition.x/32).at(mousePosition.y/32)->isFlag){
                    allTiles.at(mousePosition.x/32).at(mousePosition.y/32)->isRevealed = false;
                }
                else {
                    allTiles.at(mousePosition.x / 32).at(mousePosition.y / 32)->isFlag = true;
                    tileCounter--;

                }


            }
        } else {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                (debug.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) && !gameWin()) {
                isDebug = !isDebug;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                (happyFace.getGlobalBounds().contains(mousePosition.x, mousePosition.y))) {

                resetBoard();

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                (test1.getGlobalBounds().contains(mousePosition.x, mousePosition.y))) {

                resetBoard();
                loadBoard("boards/testboard1.brd");

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                (test2.getGlobalBounds().contains(mousePosition.x, mousePosition.y))) {
                resetBoard();
                loadBoard("boards/testboard2.brd");
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                (test3.getGlobalBounds().contains(mousePosition.x, mousePosition.y))) {
                resetBoard();
                loadBoard("boards/testboard3.brd");
            }
        }
    }
    catch (exception) {
        cout << "Out of bounds" << endl;

    }

}

void Board::resetBoard() {
    isStarted = false;
    isWon = true;
    gameEnd = false;

    ifstream file("boards/config.cfg");

    string columns;
    string rows;
    string mines;

    if(file.is_open()){
        getline(file,columns);
        getline(file,rows);
        getline(file,mines);
    }

    this->numMines = stoi(mines);
    this->tileCounter = numMines;
    for (int i = 0; i < getColumns(); i++) {
        for (int j = 0; j < getRows(); j++) {
            allTiles.at(i).at(j)->isFlag = false;
            allTiles.at(i).at(j)->isHidden = true;
            allTiles.at(i).at(j)->isRevealed = false;
            allTiles.at(i).at(j)->isMine = false;
            allTiles.at(i).at(j)->revealMine = false;
        }
    }
    int mineCounter = 0;

    while(mineCounter != numMines){

        int randomPosX = Random::Int(0,getColumns()-1);
        int randomPosY = Random::Int(0,getRows()-1);

        if(!allTiles.at(randomPosX).at(randomPosY)->isMine){
            allTiles.at(randomPosX).at(randomPosY)->isMine = true;
            mineCounter++;

        }

    }
}


bool Board::gameWin() {

    int hiddenCount = 0;
    int mines = numMines;

    for(int i = 0; i < getColumns(); i++){
        for(int j = 0; j < getRows();j++){
            if(allTiles.at(i).at(j)->isHidden){
                hiddenCount++;
            }

        }
    }

    if(hiddenCount == mines){
        return true;
    }
    return false;
}

void Board::compare(sf::RenderWindow &window, int& place, int position) {
    switch (place) {
        case 0:
            flagCounter0.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter0);
            break;

        case 1:
            flagCounter1.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter1);
            break;

        case 2:

            flagCounter2.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter2);
            break;

        case 3:
            flagCounter3.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter3);
            break;
        case 4:
            flagCounter4.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter4);
            break;
        case 5:
            flagCounter5.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter5);
            break;
        case 6:
            flagCounter6.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter6);
            break;
        case 7:
            flagCounter7.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter7);
            break;
        case 8:
            flagCounter8.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter8);
            break;
        case 9:
            flagCounter9.setPosition(21*position, getHeight()-100);
            window.draw(flagCounter9);
            break;


    }
}

void Board::recursiveReveal(Tile* tile) {

    vector<Tile*> compare = getNeighbors(tile->position.x/32,tile->position.y/32);

    if(tile->isMine || tile->isRevealed || tile->isFlag){

        return;
    }

    if(!tile->isFlag){
        tile->isRevealed = true;
        tile->isHidden = false;
    }

    for(int i = 0; i < compare.size(); i++){
        if(compare.at(i)->isMine){
            return;
        }
    }

    for(int i = 0; i < compare.size(); i++) {

        recursiveReveal(compare.at(i));

    }
}