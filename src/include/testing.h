#pragma once
#include "models.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include "enemy.h"
#include <SFML/System/Clock.hpp>

class TestingScreen {
public:
    TestingScreen(std::string path);
    void handleEvent(const sf::Event &, sf::RenderWindow &, GameState &);
    void draw(sf::RenderWindow &window, sf::Font &font);

private:
    Enemy enemy;
    sf::Clock clock;
};
