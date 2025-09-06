// utils.hpp
#pragma once
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <string>
// Utility functions
float randomNum(float min, float max);
bool isClickedOn(const Entity &entity, sf::Vector2f &click_pos);
sf::Color colorFromHex(const std::string &hexString);
