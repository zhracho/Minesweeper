#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include "Random.h"
#include "Tile.h"
#include "Board.h"
using namespace std;
using namespace sf;

int main()
{
    //Initialize all of the sprites and textures before anything


    //Gets input from the config file in order to get the proper dimensions for the window
    Board board;

    sf::RenderWindow window(sf::VideoMode(board.getWidth(), board.getHeight()), "Minesweeper!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            board.updateBoard(window,mousePosition);

        }

        window.clear(sf::Color(255,255,255));



        board.drawTiles(window);
        window.display();
    }

    //Clear out any textures for debug mode
    TextureManager::Clear();
    return 0;
}