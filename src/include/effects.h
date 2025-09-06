#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
namespace smashers {
class Effects : public sf::Transformable {

public:
  Effects(const std::string &path, const sf::Vector2f &startPos,
          const sf::Vector2i &frameSize, int totalFramesToLoad);

  void animate();
  void resetAnimation();
  void play();
  void draw(sf::RenderTarget &target) const; // More flexible than RenderWindow
  void setPosition(float x, float y);        // Set position of the enemy
  void setFrame(int frame);
  void setScale(float factor);
  void setScale(float scaleX, float scaleY);
  sf::Sprite getSprite();
  sf::FloatRect getGlobalBounds();

private:
  sf::Texture texture;
  sf::Sprite sprite;
  std::vector<sf::Rect<int>> frameRects;
  sf::Vector2i frameSize;
  size_t currentFrameIndex;
  float accumulatedTime = 0.0f;
  sf::Clock animationClock;
  bool isPlaying;
};
} // namespace smashers
