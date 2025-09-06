#pragma once
#include "effects.h"
#include "enemy.h"
#include "screen.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

class TestingScreen : public smashers::Widget {
public:
  TestingScreen(std::string path);
  void handleEvent(const sf::Event &, sf::RenderWindow &);
  void draw(sf::RenderWindow &window, sf::Font &font);
  void update();

private:
  smashers::Effects effect;
  sf::Clock clock;
};
