
#include "include/GameScreen.h"
#include "include/effects.h"
#include "include/enemy.h"
#include "include/gameStateManager.h"
#include "include/player.h"
#include "include/saveData.h"
#include "include/sounds.h"
#include "include/utils.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

GameScreen::GameScreen(uint width, uint height, Enemy &enm,
                       smashers::Effects &explosion,
                       std::unordered_map<SoundId, sf::Sound> &sound,
                       TOMLDataSaver &saver)
    : consecutiveMisses(0), isDotClicked(false), windowWidth(width),
      windowHeight(height), enemy(enm), eff(explosion), sounds(sound),
      scoreSaver(saver) {
  eff.setPosition(-1000, -1000);
  interval = sf::milliseconds(2000);
}

void GameScreen::handleEvent(const sf::Event &event, sf::RenderWindow &window,
                             smashers::Player &player) {

  if (const auto *mouseButtonPressed =
          event.getIf<sf::Event::MouseButtonPressed>()) {
    handleMouseButtonPressed(*mouseButtonPressed, window, player);
  }
  if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    handleKeyPressed(*keyPressed, player);
  }
}

void GameScreen::handleMouseButtonPressed(
    const sf::Event::MouseButtonPressed &mouseButton, sf::RenderWindow &window,
    smashers::Player &player) {
  if (mouseButton.button == sf::Mouse::Button::Left) {
    sf::Vector2f click_pos = window.mapPixelToCoords(mouseButton.position);
    if (isClickedOn(enemy, click_pos)) {
      player.incrementScore();

      auto it = sounds.find(SoundId::ATTACK);
      if (it != sounds.end())
        it->second.play();
      isDotClicked = true;
      consecutiveMisses = 0;
      // Spawn new dot (avoid title bar area)
      float titleBarHeight = 80.f; // Approximate title bar height
      sf::Vector2f pos(
          {randomNum(0.f,
                     static_cast<float>(windowWidth -
                                        enemy.getGlobalBounds().size.x * 2)),
           randomNum(titleBarHeight,
                     static_cast<float>(windowHeight -
                                        enemy.getGlobalBounds().size.y * 2))});
      enemy.setPosition(pos.x, pos.y);
      eff.setPosition(click_pos.x, click_pos.y);
      eff.play();

      if (player.getScore() % 100 == 0) {
        interval =
            sf::milliseconds(static_cast<int>(interval.asMilliseconds() * 0.9));
      }
      clock.restart(); // Reset the interval clock on click as well
    }
  }
}

void GameScreen::handleKeyPressed(const sf::Event::KeyPressed &keyPressed,
                                  smashers::Player &player) {
  if (keyPressed.code == sf::Keyboard::Key::Escape) {
    Game::setGameState(Game::GameState::WAITING);

    bool h = scoreSaver.updateHighScore(player.getScore());
    if (h) {
      player.reset();
    }
    update(player);
  }
}

void GameScreen::update(smashers::Player &player) {
  // Update phase
  enemy.animate();
  eff.animate();
  if (clock.getElapsedTime() > interval) {
    // Check if dot was missed
    if (!isDotClicked) {
      consecutiveMisses++;
      std::cout << "Consecutive misses: " << consecutiveMisses << "\n";

      // Lose a heart after 2 consecutive misses
      if (consecutiveMisses >= 2 && player.getHealth() > 0) {
        player.decrementHealth();
        auto it = sounds.find(SoundId::HEALTH_LOSS);
        if (it != sounds.end())
          it->second.play();
        std::cout << "Lost a heart! Lives remaining: " << player.getHealth()
                  << "\n";

        // Check for game over
        if (player.getHealth() == 0) {
          Game::setGameState(Game::GameState::GAME_OVER);

          bool h = scoreSaver.updateHighScore(player.getScore());
          return;
        }
      }
    }

    // Reset for next round and spawn new dot
    isDotClicked = false;
    // Spawn new dot (avoid title bar area)
    float titleBarHeight = 80.f; // Approximate title bar height
    sf::Vector2f pos(
        {randomNum(0.f, static_cast<float>(windowWidth -
                                           enemy.getGlobalBounds().size.x * 2)),
         randomNum(titleBarHeight,
                   static_cast<float>(windowHeight -
                                      enemy.getGlobalBounds().size.y * 2))});
    enemy.setPosition(pos.x, pos.y);
    // shape.setPosition(pos);

    clock.restart();
  }
}

void GameScreen::draw(sf::RenderWindow &window, sf::Font &font,
                      sf::Texture &heartTexture, smashers::Player &player) {
  // Score text
  sf::Text text(font);
  text.setString("Score: " + std::to_string(player.getScore()));
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);
  float paddingX = 20.f;
  float paddingY = 10.f;
  text.setPosition({paddingX, paddingY});

  // Draw hearts
  float heartRadius = 15.f;
  float heartSpacing = 10.f;
  sf::FloatRect textBounds = text.getGlobalBounds();
  float heartsStartX = paddingX + textBounds.size.x + 10;
  float heartsY = paddingY + 10.f;

  std::vector<sf::Sprite> hearts;
  for (uint i = 0; i < 5; ++i) {
    sf::Sprite heart(heartTexture);
    heart.setScale({0.2f, 0.2f});
    heart.setPosition(
        {heartsStartX + i * (heartRadius * 2 + heartSpacing), heartsY});

    // Show full hearts for current lives, faded for lost lives
    if (i < player.getHealth()) {
      heart.setColor(sf::Color::Red);
    } else {
      heart.setColor(sf::Color(100, 100, 100, 100));
    }
    hearts.push_back(heart);
  }

  // enemy.draw(window);
  // Draw everything
  window.draw(enemy.getSprite());
  eff.draw(window);
  window.draw(text);
  for (const auto &heart : hearts) {
    window.draw(heart);
  }
}
