
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Zombie_arena.h"
#include "Player.h"
#include "Bullet.h"
#include "TextureHolder.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int main() {
    //std::srand(std::time(0)); // Seed random number generator once

    TextureHolder textureHolder;

    enum class State {
        PAUSED, LEVELING_UP, GAMEOVER, PLAYING
    };
    State state = State::GAMEOVER;

    sf::Vector2f resolution(1920 / 2, 1080 / 2);

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
    int numZombies=0;
    int numZombiesAlive=0;
    Zombie* zombies = nullptr;

    Bullet* bullets = new Bullet[10];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;
    //when was the last fire button pressed;
    sf::Time lastPressed;


    ////////////////////////////////////////////////////////////////////////////////////////////////


    sf::Clock clock;
    sf::Time totalGameTime;
    sf::Vector2f mouseWorldPosition;
    sf::Vector2i mouseScreenPosition;
    sf::IntRect arena;


    //maint loop


    while (window.isOpen()) {// window is not opening

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            std::cout << "closed";
            window.close();
        }
        std::cout << "escape was not pressed\n";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            if (state == State::PLAYING) {
                state = State::PAUSED;
                std::cout << "playing";
            }
            else if (state == State::PAUSED) {
                state = State::PLAYING;
                clock.restart();
                std::cout << "paused";
            }
            else if (state == State::GAMEOVER) {
                state = State::LEVELING_UP;
                std::cout << "gameover";
            }
            else if (state == State::LEVELING_UP) {
                state = State::PLAYING;
                clock.restart();
                std::cout << "leveling up";
            }
        }else {      
            std::cerr << "error: " << errno<< "\n";
        }
        std::cout << "key is not pressed\n";
        if (state == State::PLAYING) {
            std::cout << "playing";
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.moveUp(); else player.stopUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.moveLeft(); else player.stopLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.moveDown(); else player.stopDown();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.moveRight(); else player.stopRight();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                if (bulletsSpare >= clipSize) {
                    bulletsInClip = clipSize;
                    bulletsSpare -= clipSize;
                }
                else if (bulletsSpare > 0) {
                    bulletsInClip = clipSize;
                    bulletsSpare -= clipSize;
                }
                else {
                    //more to come...
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if (totalGameTime.asSeconds() - lastPressed.asSeconds() > 1000 / fireRate && bulletsInClip > 0) {
                    // pass the center of the player and the center
                    // of the cross-hair to the shoot function
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                    currentBullet++;
                    if (currentBullet > 99) {
                        currentBullet = 0;
                    }
                    lastPressed = totalGameTime;
            
                    bulletsInClip--;
                }
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


                            numZombies = 10;


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
                        std::cout << "updating zombie";
                    }
                }
                //update bullets in flight
                for (int i = 0; i < 10; i++) {
                    if (bullets[i].isInFlight()) {
                        bullets[i].update(dt.asSeconds());
                    }
                }
            }

            window.clear();

            //draw the scene
            if (state == State::PLAYING) {
                window.setView(mainView);
                window.draw(background, &texBackground);
                for (int i = 0; i < numZombies; i++) {
                    std::cout << i;
                    window.draw(zombies[i].getSprite());
                }
                for (int i = 0; i < 100; i++) {
                    if (bullets[i].isInFlight()) {
                        window.draw(bullets[i].getShape());
                    }
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
				window.draw(player.getSprite());
            }
            window.display();
        }
        std::cout << "end of the line\n";
        delete[] zombies;
        delete[] bullets;
        std::cout << "everything is deleted\n";
        return 0;
    }
}

