
#include "include/GameOverScreen.h"
#include "include/GameScreen.h"
#include "include/IntroScreen.hpp"
#include "include/effects.h"
#include "include/enemy.h"
#include "include/gameStateManager.h"
#include "include/pathResolution.h"
#include "include/player.h"
#include "include/saveData.h"
#include "include/sounds.h"
#include "include/testing.h"
#include <SFML/Audio.hpp> // Ensure all SFML audio features are included
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unordered_map>

// Enum for different game screens
using namespace std;

int main() {
  using namespace std;

  uint windowWidth = 800;
  uint windowHeight = std::round(windowWidth * 9 / 16);
  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}, 60),
                          "SFML Dot Game!");

  // Initialize game state
  Enemy enm(getAssetPath("sprites/skull-sprite.png"), {0, 0}, {22, 27}, 2);

  TestingScreen testingScreen(
      "/home/zoro/Downloads/explosion.png"); // getAssetPath("sprites/skull-sprite.png"));

  // Load resources
  sf::Font font;
  string path = getAssetPath("fonts/Diphylleia-Regular.ttf");
  if (!font.openFromFile(path)) {
    cerr << "Failed to load Font from : " << path << "\n";
    exit(EXIT_FAILURE);
  }

  loadSound();
  smashers::Effects effect(getAssetPath("sprites/8-bit-explosion.png"), {0, 0},
                           {32, 32}, 6);
  // Set background music to loop
  auto bgIt = sounds.find(SoundId::BACKGROUND);
  if (bgIt != sounds.end()) {
    bgIt->second.setLooping(true);
  }
  TOMLDataSaver saver;
  IntroScreen introScreen(windowWidth, windowHeight);
  GameScreen gameScreen(windowWidth, windowHeight, enm, effect, sounds, saver);
  GameOverScreen gameOverScreen(0);
  sf::Texture heartTexture;
  if (!heartTexture.loadFromFile(getAssetPath("sprites/heart.png"))) {
    cout << "Error loading heart.png" << endl;
    exit(EXIT_FAILURE);
  }

  // Game::setGameState(Game::GameState::TESTING);
  cout << windowHeight << "\t" << windowWidth << endl;

  smashers::Player player;
  cout << &player << "\n";
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // Handle events based on current state
      switch (Game::getGameState()) {
      case Game::GameState::WAITING:
        introScreen.handleEvent(*event, window);
        break;
      case Game::GameState::PLAYING:
        gameScreen.handleEvent(*event, window, player);
        break;
      case Game::GameState::GAME_OVER:
        gameOverScreen.handleEvent(*event, player);
        break;

      case Game::GameState::TESTING:
        testingScreen.handleEvent(*event, window);
        break;
      }
    }

    // --- Background music logic ---
    auto bgIt = sounds.find(SoundId::BACKGROUND);
    if (bgIt != sounds.end()) {
      Game::GameState currentState = Game::getGameState();
      if ((currentState == Game::GameState::WAITING ||
           currentState == Game::GameState::PLAYING)) {
        if (bgIt->second.getStatus() != sf::Sound::Status::Playing) {
          bgIt->second.play();
        }
      } else if (currentState == Game::GameState::GAME_OVER) {
        bgIt->second.stop();
        auto it = sounds.find(SoundId::GAMELOOSE);

        if (it != sounds.end() &&
            it->second.getStatus() != sf::Sound::Status::Playing) {
          it->second.play();
        }
      }
    }

    // --- End background music logic ---

    if (Game::isStateUpdated() &&
        Game::getGameState() == Game::GameState::GAME_OVER) {
      saver.updateHighScore(gameOverScreen.finalScore);
    }

    // Update game logic based on current state
    switch (Game::getGameState()) {
    case Game::GameState::WAITING:
      break;
    case Game::GameState::PLAYING:
      gameScreen.update(player);
      break;
    case Game::GameState::GAME_OVER: { // Update game over screen if it just
                                       // changed

      // if (gameOverScreen.finalScore != player.getScore()) {
      //         << " to " << player.getScore() << std::endl;
      // std::endl; gameOverScreen.finalScore = player.getScore();
      //}
      gameOverScreen.update(player);
      break;
    }
    case Game::GameState::TESTING:
      break;
    }

    // Render based on current state
    window.clear();
    switch (Game::getGameState()) {
    case Game::GameState::WAITING:
      introScreen.draw(window, font);
      break;
    case Game::GameState::PLAYING:
      gameScreen.draw(window, font, heartTexture, player);
      break;
    case Game::GameState::GAME_OVER: {
      gameOverScreen.draw(window, font);
      break;
    }
    case Game::GameState::TESTING:
      testingScreen.draw(window, font);
      break;
    }
    window.display();
  }

  return 0;
}
