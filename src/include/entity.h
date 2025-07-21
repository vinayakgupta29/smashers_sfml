#pragma once
#include <SFML/Graphics/Rect.hpp>
class Entity {
public:
  virtual ~Entity() = default;
  virtual sf::FloatRect getGlobalBounds() const = 0;
};
