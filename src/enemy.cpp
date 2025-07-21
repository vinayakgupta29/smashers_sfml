#include "include/enemy.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <ostream>

Enemy::Enemy(const std::string &spriteSheetPath, const sf::Vector2f &startPos,
             const sf::Vector2i &frameSize, int totalFramesToLoad)
    : sprite(texture) {
  if (!texture.loadFromFile(spriteSheetPath)) {
    std::cerr << "Failed to Enemy " << spriteSheetPath << std::endl;
    throw std::runtime_error("Failed to load texture!");
  }

  // Calculate texture dimensions
  const sf::Vector2u texSize = texture.getSize();
  const int framesPerRow = (texSize.x - startPos.x) / frameSize.x;

  // Collect frame coordinates
  sf::Vector2f currentPos = startPos;
  for (int i = 0; i < totalFramesToLoad; ++i) {
    // Add frame rectangle
    sf::Vector2i pos(
        {static_cast<int>(currentPos.x), static_cast<int>(currentPos.y)});
    sf::IntRect rect(pos, frameSize);
    frameRects.emplace_back(pos, frameSize);

    // Move to next frame position
    currentPos.x += frameSize.x;
    if (currentPos.x + frameSize.x > texSize.x) {
      currentPos.x = startPos.x;
      currentPos.y += frameSize.y;
    }
  }
  std::cout << frameRects.size() << std::endl;
  // Setup sprite
  sprite.setTexture(texture);
  if (!frameRects.empty())
    sprite.setTextureRect(frameRects[0]);
}
void Enemy::animate() {
  float deltaTime = animationClock.restart().asSeconds();
  accumulatedTime += deltaTime;
  const float frameDuration = 1.0f / 6.0f; // 6 FPS animation (10x slower)

  while (accumulatedTime >= frameDuration && !frameRects.empty()) {
    accumulatedTime -= frameDuration;
    currentFrameIndex = (currentFrameIndex + 1) % frameRects.size();
    sprite.setTextureRect(frameRects[currentFrameIndex]);
  }
}

void Enemy::draw(sf::RenderTarget &target) const { target.draw(sprite); }

void Enemy::setPosition(float x, float y) { sprite.setPosition({x, y}); }

void Enemy::setScale(float factor) { sprite.setScale({factor, factor}); }

void Enemy::setScale(float x, float y) { sprite.setScale({x, y}); }

sf::Sprite Enemy::getSprite() { return sprite; }

sf::FloatRect Enemy::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
