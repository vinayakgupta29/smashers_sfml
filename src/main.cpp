
#include "include/sounds.h"
#include "include/GameOverScreen.h"
#include "include/GameScreen.h"
#include "include/IntroScreen.hpp"
#include "include/enemy.h"
#include "include/models.h"
#include "include/testing.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio.hpp> // Ensure all SFML audio features are included
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
  GameState currentState = GameState::WAITING;
  Enemy enm("assets/sprites/skull-sprite.png", {0, 0}, {22, 27}, 2);

  TestingScreen testingScreen("assets/sprites/skull-sprite.png");

  // Load resources
  sf::Font font;
  string path = "assets/fonts/Diphylleia-Regular.ttf";
  if (!font.openFromFile(path)) {
    cerr << "Failed to load Font from : " << path << "\n";
    exit(EXIT_FAILURE);
  }

  loadSound();

  // Set background music to loop
  auto bgIt = sounds.find(SoundId::BACKGROUND);
  if (bgIt != sounds.end()) {
    bgIt->second.setLooping(true);
  }

  IntroScreen introScreen(windowWidth, windowHeight);
  GameScreen gameScreen(windowWidth, windowHeight, enm, sounds);
  GameOverScreen gameOverScreen(0);
  sf::Texture heartTexture;
  if (!heartTexture.loadFromFile("assets/sprites/heart.png")) {
    cout << "Error loading heart.png" << endl;
    exit(EXIT_FAILURE);
  }

  cout << windowHeight << "\t" << windowWidth << endl;


  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // Handle events based on current state
      switch (currentState) {
      case GameState::WAITING:
        introScreen.handleEvent(*event, window, currentState);
        break;
      case GameState::PLAYING:
        gameScreen.handleEvent(*event, window, currentState);
        break;
      case GameState::GAME_OVER:
        gameOverScreen.handleEvent(*event, currentState, gameScreen);
        break;

      case GameState::TESTING:
        testingScreen.handleEvent(*event, window, currentState);
        break;
      }
    }

    // --- Background music logic ---
      auto bgIt = sounds.find(SoundId::BACKGROUND);
      if (bgIt != sounds.end()) {
        if ((currentState == GameState::WAITING || currentState == GameState::PLAYING)) {
          if (bgIt->second.getStatus() != sf::Sound::Status::Playing) {
            bgIt->second.play();
          }
        } else if (currentState == GameState::GAME_OVER) {
          bgIt->second.stop();
          auto it = sounds.find(SoundId::GAMELOOSE);
      
          if (it!=sounds.end() && it->second.getStatus()!=sf::Sound::Status::Playing) {
          it->second.play();
          }

        }
      }

    
    // --- End background music logic ---

    // Update game logic based on current state
    switch (currentState) {
    case GameState::WAITING:
      break;
    case GameState::PLAYING:
      gameScreen.update(currentState);
      break;
    case GameState::GAME_OVER:
    {  // Update game over screen if it just changed
     
      if (gameOverScreen.finalScore != gameScreen.score) {
        gameOverScreen.finalScore = gameScreen.score;
      }
      break;}
    case GameState::TESTING:
      break;
    }

    // Render based on current state
    window.clear();
    switch (currentState) {
    case GameState::WAITING:
      introScreen.draw(window, font);
      break;
    case GameState::PLAYING:
      gameScreen.draw(window, font, heartTexture);
      break;
    case GameState::GAME_OVER:
      gameOverScreen.draw(window, font);
      break;
    case GameState::TESTING:
      testingScreen.draw(window, font);
      break;
    }
    window.display();
  }

  return 0;
}
