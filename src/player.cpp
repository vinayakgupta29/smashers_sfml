#include "include/player.h"
#include <iostream>
#include <sys/types.h>
uint smashers::Player::getScore() const { return score; }

void smashers::Player::setScore(uint s) { score = s; }

uint smashers::Player::getHealth() const { return health; }

void smashers::Player::setHealth(uint h) { health = h; };

void smashers::Player::reset() {
  health = 5;
  score = 0;
}

void smashers::Player::incrementScore() { score++; }

void smashers::Player::decrementHealth() {
  if (health > 0) {
    health--;
  }
}

void smashers::Player::print() const {
  std::cout << "Player [id=" << id << ", health=" << health
            << ", score=" << score << ", address="
            << this // memory address (unique per object instance)
            << "]\n";
}
smashers::Player::Player() : health(5), score(0) {}
