#pragma once
#include "models.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
class Screen {
public:
  virtual void handleEvent(const sf::Event &, sf::RenderWindow &window,
                           GameState &gameState) = 0;
  virtual void update(GameState &) = 0;
  virtual void draw(sf::RenderWindow &, sf::Font &) = 0;
  virtual ~Screen() = default;
};
