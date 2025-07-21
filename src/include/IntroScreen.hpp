#pragma once
#include "RoundedRectangle.h"
#include "models.h"
#include "screen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class IntroScreen  {
public:
  IntroScreen(float windowWidth, float windowHeight);
  void update(GameState &) ;
  void draw(sf::RenderWindow &) ;
  void draw(sf::RenderWindow &window, sf::Font &font);
  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   GameState &gameState) ;

private:
  RoundedRectangle playButton;
  float windowWidth;
  float windowHeight;
};
