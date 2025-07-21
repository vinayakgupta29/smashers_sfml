#include "include/models.h"
#include "include/entity.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

float randomNum(float min, float max) {
  return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

bool isClickedOn(const Entity &entity, sf::Vector2f &click_pos) {
  return entity.getGlobalBounds().contains(click_pos);
}
