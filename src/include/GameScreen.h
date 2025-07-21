#pragma once

#include "enemy.h"
#include "models.h"
#include "screen.h"
#include "sounds.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <unordered_map>

class GameScreen {
private:
  uint windowWidth, windowHeight;
  Enemy enemy;
  sf::Clock enemyClock;
  void
  handleMouseButtonPressed(const sf::Event::MouseButtonPressed &mouseButton,
                           sf::RenderWindow &window, GameState &gameState);
  void handleKeyPressed(const sf::Event::KeyPressed &keyPressed,
                        GameState &gameState);

public:
  uint score;
  uint lives;
  uint consecutiveMisses;

  sf::Clock clock;
  sf::Time interval;
  bool isDotClicked;
  std::unordered_map<SoundId, sf::Sound> &sounds;

  // Constructor
  GameScreen(uint width, uint height, Enemy &enm,
             std::unordered_map<SoundId, sf::Sound> &sounds);

  // Methods
  void update(GameState &);
  void draw(sf::RenderWindow &);
  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   GameState &gameState);

  void draw(sf::RenderWindow &window, sf::Font &font,
            sf::Texture &heartTexture);
  void reset();
};
