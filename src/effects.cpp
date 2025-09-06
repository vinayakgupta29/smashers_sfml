#include "include/effects.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>

smashers::Effects::Effects(const std::string &path,
                           const sf::Vector2f &startPos,
                           const sf::Vector2i &frameSize, int totalFramesToLoad)
    : sprite(texture) {
  if (!texture.loadFromFile(path)) {
    std::cerr << "Failed to Effects " << path << std::endl;
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
  // Setup sprite
  sprite.setTexture(texture);
  if (!frameRects.empty())
    sprite.setTextureRect(frameRects[0]);
}
void smashers::Effects::animate() {
  if (!isPlaying)
    return;
  sf::Time deltaTime = animationClock.restart();
  accumulatedTime += deltaTime.asSeconds();
  const float frameDuration = 1.0f / 6.0f; // 6 FPS animation (10x slower)

  while (accumulatedTime >= frameDuration && !frameRects.empty()) {
    accumulatedTime -= frameDuration;
    currentFrameIndex = (currentFrameIndex + 1) % frameRects.size();
    sprite.setTextureRect(frameRects[currentFrameIndex]);
  }

  if (currentFrameIndex >= frameRects.size() - 1) {
    isPlaying = false;
  }
}
void smashers::Effects::resetAnimation() {
  animationClock.restart();
  accumulatedTime = 0.0f;
  currentFrameIndex = 0;
  if (!frameRects.empty()) {
    sprite.setTextureRect(frameRects[0]);
  }
}
void smashers::Effects::play() {
  animationClock.restart();
  accumulatedTime = 0.0f;
  currentFrameIndex = 0;
  isPlaying = true;
  sprite.setTextureRect(frameRects[0]);
}
void smashers::Effects::draw(sf::RenderTarget &target) const {
  if (isPlaying)
    target.draw(sprite);
}

void smashers::Effects::setPosition(float x, float y) {
  sprite.setPosition({x, y});
}

void smashers::Effects::setScale(float factor) {
  sprite.setScale({factor, factor});
}

void smashers::Effects::setScale(float x, float y) { sprite.setScale({x, y}); }

sf::Sprite smashers::Effects::getSprite() { return sprite; }

sf::FloatRect smashers::Effects::getGlobalBounds() {
  return sprite.getGlobalBounds();
}
