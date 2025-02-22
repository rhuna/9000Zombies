// 9000Zombies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SFML/Graphics.hpp"

#include "Player.h"



int main() {
    //variables
    enum class State {
        PAUSED, LEVELING_UP, GAMEOVER, PLAYING
    };
    State state = State::GAMEOVER;

    //get the resolution and create SFML window
    sf::Vector2f resolution;
    resolution.x = 1920;
    resolution.y = 1080;

    sf::Texture texture;
    texture.loadFromFile("./graphics/player.png");
    Player player(texture);

    ////////////////////////////////////////////////////////

    //window
    sf::VideoMode vm({1920,1080});
    sf::RenderWindow window(vm, "zombies");
    //
    sf::View mainView;
    sf::View hudview;
    mainView.setCenter(player.getCenter());
    mainView.rotate(sf::degrees(45));
    //window.setView(mainView);
    //switch to hudview
    //window.setView(hudview);

    //background
    sf::VertexArray background;
    background.setPrimitiveType(sf::PrimitiveType::Triangles);
    background.resize(10 * 10 * 6);
    sf::Texture texBackground;
    texBackground.loadFromFile("./graphics/background_sheet.png");

    //top triangle
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(49, 0);
    background[2].position = sf::Vector2f(49, 49);
    //bottom triangle
    background[3].position = sf::Vector2f(49, 49);
    background[4].position = sf::Vector2f(0, 49);
    background[5].position = sf::Vector2f(0, 0);
    //top triangle
    background[0].texCoords = sf::Vector2f(0, 0);
    background[1].texCoords = sf::Vector2f(49, 0);
    background[2].texCoords = sf::Vector2f(49, 49);
    //bottom triangle
    background[3].texCoords = sf::Vector2f(49, 49);
    background[4].texCoords = sf::Vector2f(0, 49);
    background[5].texCoords = sf::Vector2f(0, 0);


    /////////////////////////////////////////////////////////////////
    
    //setup non initialized variables
    sf::Clock clock;
    sf::Time totalGameTime;
    //mouse relation to world
    sf::Vector2f mouseWorldPosition;
    //mouse relation to screen
    sf::Vector2i mouseScreenPosition;
    sf::IntRect arena;

    //////////////////////////////////////////////////////////////////



    //game loop
    while (window.isOpen()) {

        //handle input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }
        //handle events
       // while (const std::optional event = window.pollEvent()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && state == State::PLAYING) {
                state = State::PAUSED;
            }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && state == State::PAUSED) {
                state = State::PLAYING;
                clock.restart();
            }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && state == State::GAMEOVER) {
                state = State::LEVELING_UP;
            }
            if (state == State::PLAYING){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    player.moveUp();
                }else {
                    player.stopUp();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    player.moveLeft();
                }else {
                    player.stopLeft();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                    player.moveDown();
                }else {
                    player.stopDown();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    player.moveRight();
                }else {
                    player.stopRight();
                }
            }
       //}

        if (state == State::LEVELING_UP) {
            //handle player leveling up
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
                    state = State::PLAYING;
                }
                if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
                    state = State::PLAYING;
                }
                if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
                    state = State::PLAYING;
                }
                if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
                    state = State::PLAYING;
                }
                if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
                    state = State::PLAYING;
                }
                if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
                    state = State::PLAYING;
                }
                if (state == State::PLAYING) {
                    //prepare the level
                    arena.position.x = 700;
                    arena.position.y = 150;
                    int tileSize = 50;


                    //spawn the player
                    player.spawn(arena, resolution, tileSize);

                    //reset clock
                    clock.reset();
                }
            }

            //update frame
            if (state == State::PLAYING) {
                //update time
                sf::Time dt = clock.restart();
                //update game time total
                totalGameTime += dt;
                float dtasSecconds = dt.asSeconds();
                mouseScreenPosition = sf::Mouse::getPosition();
                mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);
                sf::Vector2f playerPosition(player.getCenter());
                //make the view center around the player
                mainView.setCenter(player.getCenter());
            }
        }


        //draw the scene

        if (state == State::PLAYING) {
            window.clear();
            window.setView(mainView);
            window.draw(player.getSprite());
            window.draw(background, &texBackground);
           
        }
        if (state == State::LEVELING_UP) {
            
            

        }
        if (state == State::PAUSED) {
            
           

        }
        if (state == State::GAMEOVER) {
           
            

        }
      
        window.display();
        
    }//end game loop



}

