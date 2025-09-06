#pragma once

#include "gameStateManager.h"
#include "player.h"
#include "saveData.h"
#include "screen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

class GameOverScreen : public smashers::Widget {
public:
  uint finalScore;

  // Constructor
  GameOverScreen(uint score = 0);

  // Methods

  void update(smashers::Player &player);
  void draw(sf::RenderWindow &, sf::Font &);
  void handleEvent(const sf::Event &event, smashers::Player &player);
  void handleEvent(const sf::Event &event, sf::RenderWindow &window);
  void setFinalScore(uint score);
};
