#include "include/sounds.h"
#include "include/pathResolution.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

std::unordered_map<SoundId, std::string> nameToFile = {
    {SoundId::BACKGROUND, "8-bit-heaven.ogg"},
    {SoundId::HEALTH_LOSS, "8-bit-fireball.ogg"},
    {SoundId::ATTACK, "8-bit-explosion.ogg"},
    {SoundId::GAMELOOSE, "gay.ogg"}};

std::unordered_map<SoundId, sf::SoundBuffer> soundBuffers;
std::unordered_map<SoundId, sf::Sound> sounds;

void loadSound() {
  for (const auto &[id, filename] : nameToFile) {
    std::string path = getAssetPath("sounds/") + filename;
    // "assets/sounds/" + filename;
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path)) {
      soundBuffers[id] = buffer;
      sounds.emplace(id, sf::Sound(soundBuffers[id]));
    } else {
      std::cerr << "Failed to load: " << path << std::endl;
    }
  }
}
