
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Zombie_arena.h"
#include "Player.h"
#include "TextureHolder.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int main() {
   // std::srand(std::time(0)); // Seed random number generator once

    TextureHolder textureHolder;

    enum class State {
        PAUSED, LEVELING_UP, GAMEOVER, PLAYING
    };
    State state = State::GAMEOVER;

    sf::Vector2f resolution(1920/2, 1080/2);

    sf::Texture playerTexture = TextureHolder::getTexture("./graphics/player.png");
    if (!&playerTexture) {
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


    sf::Texture texBackground = TextureHolder::getTexture("./graphics/background_sheet.png");
    if (!&texBackground) {
        std::cerr << "Error loading background texture!" << std::endl;
        return -1;
    }

    //prepare horde of zombies
    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;

    ////////////////////////////////////////////////////////////////////////////////////////////////


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


                        numZombies = 50;

                        
                        zombies = createHorde(numZombies, arena);
                        numZombiesAlive = numZombies;

                        clock.restart();
                    }
                }
            }
        }
        //updating the frame
        if (state == State::PLAYING) {
            sf::Time dt = clock.restart();
            totalGameTime += dt;
            mouseScreenPosition = sf::Mouse::getPosition(window);
            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
            player.update(dt.asSeconds(), mouseScreenPosition);
            sf::Vector2f playerPosition(player.getPosition().getCenter());
            mainView.setCenter(playerPosition);
            //loop through zombie and update them
            for (int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive()) {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }
        }

        window.clear();


        if (state == State::PLAYING) {
            window.setView(mainView);
            window.draw(background, &texBackground);
            for (int i = 0; i < numZombies; i++) {
                std::cout << i;
                window.draw(zombies[i].getSprite());
            }
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

    delete[] zombies;

    return 0;
}

