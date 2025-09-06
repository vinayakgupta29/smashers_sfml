#pragma once
#include "RoundedRectangle.h"
#include "gameStateManager.h"
#include "screen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class IntroScreen : smashers::Widget {
public:
  explicit IntroScreen(float windowWidth, float windowHeight);

  void update();
  void draw(sf::RenderWindow &window, sf::Font &font);
  void handleEvent(const sf::Event &event, sf::RenderWindow &window);

private:
  RoundedRectangle playButton;
  float windowWidth;
  float windowHeight;
};
