
#include "include/GameOverScreen.h"
#include "include/GameScreen.h"
#include "include/models.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <sys/types.h>

GameOverScreen::GameOverScreen(uint score) : finalScore(score) {}

void GameOverScreen::handleEvent(const sf::Event &event, GameState &gameState,
                                 GameScreen &gameScreen) {
  if (const auto *mouseButtonPressed =
          event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
      // Reset game and go back to playing
      gameScreen.score = 0;
      gameScreen.lives = 5;
      gameScreen.consecutiveMisses = 0;
      gameScreen.isDotClicked = false;
      gameScreen.interval = sf::milliseconds(2000);
      gameScreen.clock.restart();
      gameState = GameState::PLAYING;
    }
  }

  if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::Space ||
        keyPressed->code == sf::Keyboard::Key::Enter) {
      // Reset game and go back to playing
      gameScreen.score = 0;
      gameScreen.lives = 5;
      gameScreen.consecutiveMisses = 0;
      gameScreen.isDotClicked = false;
      gameScreen.interval = sf::milliseconds(2000);
      gameScreen.clock.restart();
      gameState = GameState::PLAYING;
    }
    if (keyPressed->code == sf::Keyboard::Key::Escape) {
      gameState = GameState::WAITING;
    }
  }
}

void GameOverScreen::draw(sf::RenderWindow &window, sf::Font &font) {
  uint windowWidth = window.getSize().x;
  uint windowHeight = window.getSize().y;

  // Game Over text
  sf::Text gameOverText(font);
  gameOverText.setString("GAME OVER");
  gameOverText.setCharacterSize(60);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setStyle(sf::Text::Bold);

  // Center the game over text
  sf::FloatRect gameOverBounds = gameOverText.getGlobalBounds();
  gameOverText.setPosition({(windowWidth - gameOverBounds.size.x) / 2,
                            (windowHeight - gameOverBounds.size.y) / 2 - 80});

  // Final score text
  sf::Text finalScoreText(font);
  finalScoreText.setString("Final Score: " + std::to_string(finalScore));
  finalScoreText.setCharacterSize(30);
  finalScoreText.setFillColor(sf::Color::White);

  sf::FloatRect scoreBounds = finalScoreText.getGlobalBounds();
  finalScoreText.setPosition({(windowWidth - scoreBounds.size.x) / 2,
                              (windowHeight - scoreBounds.size.y) / 2 - 20});

  // Restart instruction text
  sf::Text restartText(font);
  restartText.setString("Click anywhere or press SPACE to play again");
  restartText.setCharacterSize(20);
  restartText.setFillColor(sf::Color::Yellow);

  sf::FloatRect restartBounds = restartText.getGlobalBounds();
  restartText.setPosition({(windowWidth - restartBounds.size.x) / 2,
                           (windowHeight - restartBounds.size.y) / 2 + 40});

  // Draw everything
  window.draw(gameOverText);
  window.draw(finalScoreText);
  window.draw(restartText);
}
