// 9000Zombies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//




//int main() {
 //   //variables
 //   enum class State {
 //       PAUSED, LEVELING_UP, GAMEOVER, PLAYING
 //   };
 //   State state = State::GAMEOVER;
 //
 //   //get the resolution and create SFML window
 //   sf::Vector2f resolution;
 //   resolution.x = 1920;
 //   resolution.y = 1080;
 //
 //   sf::Texture texture;
 //   texture.loadFromFile("./graphics/player.png");
 //   Player player(texture);
 //
 //   ////////////////////////////////////////////////////////
 //
 //   //window
 //   sf::VideoMode vm({1920,1080});
 //   sf::RenderWindow window(vm, "zombies");
 //   //
 //   sf::View mainView;
 //   sf::View hudview;
 //   //mainView.setCenter(player.getCenter());
 //   //mainView.rotate(sf::degrees(45));
 //   //window.setView(mainView);
 //   //switch to hudview
 //   //window.setView(hudview);
 //
 //   //background
 //   sf::VertexArray background;
 //   background.setPrimitiveType(sf::PrimitiveType::Triangles);
 //   background.resize(10 * 10 * 6);
 //   sf::Texture texBackground;
 //   texBackground.loadFromFile("./graphics/background_sheet.png");
 //
 //   //top triangle background 
 //   background[0].position = sf::Vector2f(0, 0);
 //   background[1].position = sf::Vector2f(49, 0);
 //   background[2].position = sf::Vector2f(49, 49);
 //   //bottom triangle background
 //   background[3].position = sf::Vector2f(49, 49);
 //   background[4].position = sf::Vector2f(0, 49);
 //   background[5].position = sf::Vector2f(0, 0);
 //   //top triangle background
 //   background[0].texCoords = sf::Vector2f(0, 0);
 //   background[1].texCoords = sf::Vector2f(49, 0);
 //   background[2].texCoords = sf::Vector2f(49, 49);
 //   //bottom triangle background
 //   background[3].texCoords = sf::Vector2f(49, 49);
 //   background[4].texCoords = sf::Vector2f(0, 49);
 //   background[5].texCoords = sf::Vector2f(0, 0);
 //
 //
 //   /////////////////////////////////////////////////////////////////
 //   
 //   //setup non initialized variables
 //   sf::Clock clock;
 //   sf::Time totalGameTime;
 //   //mouse relation to world
 //   sf::Vector2f mouseWorldPosition;
 //   //mouse relation to screen
 //   sf::Vector2i mouseScreenPosition;
 //   sf::IntRect arena;
 //
 //   //////////////////////////////////////////////////////////////////
 //
 //
 //
 //   //game loop
 //   while (window.isOpen()) {
 //
 //       //handle input
 //       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
 //           window.close();
 //       }
 //
 //       //handle events
 //        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && state == State::PLAYING) {
 //            state = State::PAUSED;
 //        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && state == State::PAUSED) {
 //            state = State::PLAYING;
 //            clock.restart();
 //        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && state == State::GAMEOVER) {
 //            state = State::LEVELING_UP;
 //        }
 //        if (state == State::PLAYING){
 //            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
 //                player.moveUp();
 //            }else {
 //                player.stopUp();
 //            }
 //            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
 //                player.moveLeft();
 //            }else {
 //                player.stopLeft();
 //            }
 //            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
 //                player.moveDown();
 //            }else {
 //                player.stopDown();
 //            }
 //            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
 //                player.moveRight();
 //            }else {
 //                player.stopRight();
 //            }
 //        }
 //      
 //
 //       if (state == State::LEVELING_UP) {
 //           //handle player leveling up
 //           while (const std::optional event = window.pollEvent()) {
 //               if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
 //                   state = State::PLAYING;
 //               }
 //               if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
 //                   state = State::PLAYING;
 //               }
 //               if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
 //                   state = State::PLAYING;
 //               }
 //               if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
 //                   state = State::PLAYING;
 //               }
 //               if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
 //                   state = State::PLAYING;
 //               }
 //               if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
 //                   state = State::PLAYING;
 //               }
 //               if (state == State::PLAYING) {
 //                   //prepare the level
 //                   arena.position.x = 1000;
 //                   arena.position.y = 500;
 //                   int tileSize = createBackground(background, arena);
 //                   //int tileSize = 50; change later
 //
 //                   //spawn the player
 //                   player.spawn(arena, resolution, tileSize);
 //
 //                   //reset clock
 //                   clock.reset();
 //               }
 //           }
 //
 //           //update frame
 //           if (state == State::PLAYING) {
 //               //update time
 //               sf::Time dt = clock.restart();
 //               //update game time total
 //               totalGameTime += dt;
 //               float dtasSecconds = dt.asSeconds();
 //               mouseScreenPosition = sf::Mouse::getPosition();
 //               mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);
 //               sf::Vector2f playerPosition(player.getCenter());
 //               //make the view center around the player
 //               //mainView.setCenter(player.getCenter());
 //           }
 //       }
 //
 //
 //       //draw the scene
 //
 //       if (state == State::PLAYING) {
 //           window.clear();
 //           window.setView(mainView);
 //           window.draw(background, &texBackground);
 //           window.draw(player.getSprite());
 //          
 //       }
 //       if (state == State::LEVELING_UP) {
 //           
 //           
 //
 //       }
 //       if (state == State::PAUSED) {
 //           
 //          
 //
 //       }
 //       if (state == State::GAMEOVER) {
 //          
 //           
 //
 //       }
 //     
 //       window.display();
 //       
 //   }//end game loop

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Zombie_arena.h"
#include "Player.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int main() {
    std::srand(std::time(0)); // Seed random number generator once

    enum class State {
        PAUSED, LEVELING_UP, GAMEOVER, PLAYING
    };
    State state = State::GAMEOVER;

    sf::Vector2f resolution(1920/2, 1080/2);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("./graphics/player.png")) {
        std::cerr << "Error loading player texture!" << std::endl;
        return -1;
    }
    Player player(playerTexture);

    sf::VideoMode vm({ 1920,1080 });
    sf::RenderWindow window(vm, "zombies");

    sf::View mainView;
    sf::View hudView;
    //mainView.rotate(sf::degrees(45));
    sf::VertexArray background;


    sf::Texture texBackground;
    if (!texBackground.loadFromFile("./graphics/background_sheet.png")) {
        std::cerr << "Error loading background texture!" << std::endl;
        return -1;
    }

    sf::Clock clock;
    sf::Time totalGameTime;
    sf::Vector2f mouseWorldPosition;
    sf::Vector2i mouseScreenPosition;
    sf::IntRect arena;

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            if (state == State::PLAYING) {
                state = State::PAUSED;
            }
            else if (state == State::PAUSED) {
                state = State::PLAYING;
                clock.restart();
            }
            else if (state == State::GAMEOVER) {
                state = State::LEVELING_UP;
            }
        }

        if (state == State::PLAYING) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.moveUp(); else player.stopUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.moveLeft(); else player.stopLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.moveDown(); else player.stopDown();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.moveRight(); else player.stopRight();
        }

        if (state == State::LEVELING_UP) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::KeyPressed>()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
                        state = State::PLAYING;
                        //arena.left = 0;
                        //arena.top = 0;
                        arena.position.x = 1000;
                        arena.position.y = 1000;
                        createBackground(background, arena);
                        player.spawn(arena, resolution, 50);
                        clock.restart();
                    }
                }
            }
        }

        if (state == State::PLAYING) {
            sf::Time dt = clock.restart();
            totalGameTime += dt;
            mouseScreenPosition = sf::Mouse::getPosition(window);
            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
            player.update(dt.asSeconds(), mouseScreenPosition);
            mainView.setCenter(player.getPosition().getCenter());
        }

        window.clear();
        if (state == State::PLAYING) {
            window.setView(mainView);
            window.draw(background, &texBackground);
            window.draw(player.getSprite());
        }
        if (state == State::LEVELING_UP) {
            // Draw leveling up screen
        }
        if (state == State::PAUSED) {
            // Draw paused screen
        }
        if (state == State::GAMEOVER) {
            // Draw game over screen
        }
        window.display();
    }
    return 0;
}

