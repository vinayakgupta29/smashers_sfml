#include "include/IntroScreen.hpp"
#include "include/RoundedRectangle.h"
#include "include/models.h"
#include "include/utils.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

IntroScreen::IntroScreen(float windowWidth, float windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {}

void IntroScreen::draw(sf::RenderWindow &window, sf::Font &font) {

  sf::Text playText(font);
  sf::Text instructions(font);
  sf::Text title(font);
  playButton = RoundedRectangle();
  // Play button setup
  sf::Vector2f buttonSize(150.f, 50.f);
  float padding = 30.f;
  float currentY = 80.f; // start Y position

  // Title setup
  title.setFont(font);
  title.setString("Smashers");
  title.setCharacterSize(60);
  title.setFillColor(sf::Color::Yellow);
  title.setStyle(sf::Text::Bold);
  sf::FloatRect titleBounds = title.getLocalBounds();
  title.setOrigin({titleBounds.size.x / 2.f, titleBounds.size.y / 2.f});
  title.setPosition({windowWidth / 2.f, currentY + titleBounds.size.y / 2.f});
  currentY += titleBounds.size.y + padding;

  // Instructions setup
  instructions.setFont(font);
  instructions.setString("Click the skull enemies before it moves!\n"
                         "Lose a life if you miss.\n"
                         "Score increases with each hit.\n"
                         "Game speeds up every 100 points.\t Esc to exit...");
  instructions.setCharacterSize(22);
  instructions.setFillColor(sf::Color::White);
  sf::FloatRect instrBounds = instructions.getLocalBounds();
  instructions.setOrigin({instrBounds.size.x / 2.f, 0.f});
  instructions.setPosition({windowWidth / 2.f, currentY});
  currentY += instrBounds.size.y + padding * 2;

  // Play button setup
  playButton.setSize(buttonSize);
  playButton.setRadius(5.0f);
  playButton.setFillColor(colorFromHex("#FFB400"));
  playButton.setOutlineColor(sf::Color::Black);
  playButton.setOutlineThickness(3.f);
  playButton.setPosition({windowWidth / 2.f - buttonSize.x / 2.f, currentY});

  // Play text setup
  playText.setFont(font);
  playText.setString("PLAY");
  playText.setCharacterSize(36);
  playText.setFillColor(sf::Color::Black);
  sf::FloatRect playTextBounds = playText.getLocalBounds();
  playText.setOrigin(
      {playTextBounds.size.x / 2.f, playTextBounds.size.y / 2.f});
  playText.setPosition({playButton.getPosition().x + buttonSize.x / 2.f,
                        playButton.getPosition().y + buttonSize.y / 2.f - 5.f});

  // Draw all
  window.draw(title);
  window.draw(instructions);

  window.draw(playButton);
  window.draw(playText);
}

void IntroScreen::handleEvent(const sf::Event &event, sf::RenderWindow &window,
                              GameState &gameState) {
  // If using std::variant for event, check for MouseButtonPressed
  if (const auto *mouseButtonPressed =
          event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
      sf::Vector2f click_pos =
          window.mapPixelToCoords(mouseButtonPressed->position);
      if (playButton.getGlobalBounds().contains(click_pos)) {
        gameState = GameState::PLAYING;
      }
    }
  }
  if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::Escape) {
      window.close();
    }
  }
}
