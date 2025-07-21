#include "include/enemy.h"
#include "include/testing.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
sf::Vector2f velocity = {5.0f, 5.0f};
// Constructor
TestingScreen::TestingScreen(std::string path)
    : enemy(path, {0, 0}, {22, 27}, 2) // Use your actual frame size and count
{
   // enemy.setScale(100.0f / 314.0f); // Or whatever scale you want
}

void TestingScreen::draw(sf::RenderWindow &window, sf::Font &font) {
    float deltaTime = clock.restart().asSeconds();
    // Example values, replace with your actual ones
int windowWidth = 800;
int windowHeight = 450;
int displayWidth = 30;  // The width after scaling
int displayHeight = 30; // The height after scaling

float centerX = (windowWidth - displayWidth) / 2.0f;
float centerY = (windowHeight - displayHeight) / 2.0f;

enemy.setPosition(centerX, centerY);
    enemy.animate();
    enemy.draw(window);
}

void TestingScreen::handleEvent(const sf::Event &event,
                                sf::RenderWindow &window,
                                GameState &gameState) {};
