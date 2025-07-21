#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <cmath>
#include <string>
#include <unordered_map>
enum SoundId {
  ATTACK,
  HEALTH_LOSS,
  BACKGROUND,
  GAMEOVER,
  GAMELOOSE,
};
extern std::unordered_map<SoundId, std::string> nameToFile;
extern std::unordered_map<SoundId, sf::SoundBuffer> soundBuffers;
extern std::unordered_map<SoundId, sf::Sound> sounds;
void loadSound();
