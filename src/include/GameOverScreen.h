#pragma once

#include "GameScreen.h"
#include "models.h"
#include "screen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

class GameOverScreen {
public:
  uint finalScore;

  // Constructor
  GameOverScreen(uint score = 0);

  // Methods

  void update(GameState &);
  void draw(sf::RenderWindow &, sf::Font &);
  void handleEvent(const sf::Event &event, GameState &gameState,
                   GameScreen &gameScreen);
  void setFinalScore(uint score);
};
