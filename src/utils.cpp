#include "include/utils.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

sf::Color colorFromHex(const std::string &hexString) {
  std::string hex = hexString;

  // Remove leading '#' if present
  if (hex[0] == '#') {
    hex = hex.substr(1);
  } else if (hex.substr(0, 2) == "0x") {
    hex = hex.substr(0, 2);
  }

  // Default to white if string length is invalid
  if (hex.length() != 6 && hex.length() != 8) {
    return sf::Color::White;
  }

  // Parse the hex string into an unsigned int
  unsigned int value;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> value;

  if (hex.length() == 6) {
    // Format: RRGGBB
    return sf::Color((value >> 16) & 0xFF, // Red
                     (value >> 8) & 0xFF,  // Green
                     value & 0xFF          // Blue
    );
  } else {
    // Format: RRGGBBAA
    return sf::Color((value >> 24) & 0xFF, // Red
                     (value >> 16) & 0xFF, // Green
                     (value >> 8) & 0xFF,  // Blue
                     value & 0xFF          // Alpha
    );
  }
}
