#pragma once

// Enum for different game screens
#include "entity.h"
enum class GameState {
  WAITING,
  PLAYING,
  GAME_OVER,
  TESTING,
};

// Utility functions
float randomNum(float min, float max);
bool isClickedOn(const Entity& entity, sf::Vector2f &click_pos);
