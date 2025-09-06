#pragma once

#include "effects.h"
#include "enemy.h"
#include "gameStateManager.h"
#include "models.h"
#include "player.h"
#include "saveData.h"
#include "screen.h"
#include "sounds.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <unordered_map>

class GameScreen : public smashers::Widget {
public:
  uint consecutiveMisses;

  sf::Clock clock;
  sf::Time interval;
  bool isDotClicked;
  std::unordered_map<SoundId, sf::Sound> &sounds;

  // Constructor
  GameScreen(uint width, uint height, Enemy &enm, smashers::Effects &explosion,
             std::unordered_map<SoundId, sf::Sound> &sounds,
             TOMLDataSaver &saver);

  // Methods
  void draw(sf::RenderWindow &, sf::Font &);
  void update(smashers::Player &player);
  void draw(sf::RenderWindow &window, sf::Font &font, sf::Texture &heartTexture,
            smashers::Player &player);
  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   smashers::Player &player);

  void reset();

private:
  uint windowWidth, windowHeight;
  Enemy enemy;
  smashers::Effects eff;
  sf::Clock enemyClock;
  TOMLDataSaver scoreSaver;
  void
  handleMouseButtonPressed(const sf::Event::MouseButtonPressed &mouseButton,
                           sf::RenderWindow &window, smashers::Player &player);
  void handleKeyPressed(const sf::Event::KeyPressed &keyPressed,
                        smashers::Player &player);
};
