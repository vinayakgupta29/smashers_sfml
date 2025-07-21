#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <cstdint>   // For fixed-width integers (uint32_t)
#include <stdexcept> // For runtime_error
#include <string>
#include <SFML/System/Clock.hpp>

class Enemy : public Entity, public sf::Transformable {
public:
  Enemy(const std::string &spriteSheetPath, const sf::Vector2f &startPos,
        const sf::Vector2i &frameSize, int totalFramesToLoad);

  void animate();
  void draw(sf::RenderTarget &target) const; // More flexible than RenderWindow
  void setPosition(float x, float y);        // Set position of the enemy
  void setFrame(int frame);
  void setScale(float factor);
  void setScale(float scaleX, float scaleY);
  sf::Sprite getSprite();
  sf::FloatRect getGlobalBounds() const override;

private:
  uint32_t health = 1; // Prefer fixed-width integers
  uint32_t attack = 1;

  sf::Texture texture;
  sf::Sprite sprite;
  std::vector<sf::Rect<int>> frameRects;
  sf::Vector2i frameSize;
  size_t currentFrameIndex;
  float accumulatedTime = 0.0f;
  sf::Clock animationClock; // Add this for animation timing
};
