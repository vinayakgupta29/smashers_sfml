#include "include/saveData.h"
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <pwd.h>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

// Private methods
std::string TOMLDataSaver::getCurrentTimestamp() const {
  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%SZ");
  return ss.str();
}

bool TOMLDataSaver::createDirectoriesRecursive(const std::string &path) const {
  try {
    std::filesystem::create_directories(path);
    return true;
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Failed to create directory: " << e.what() << std::endl;
    return false;
  }
}

std::string TOMLDataSaver::getHomeDirectory() const {
  const char *homeDir = std::getenv("HOME");
  if (homeDir) {
    return std::string(homeDir);
  }

  // Fallback to passwd
  struct passwd *pw = getpwuid(getuid());
  if (pw && pw->pw_dir) {
    return std::string(pw->pw_dir);
  }

  return "/tmp"; // Last resort
}

// Public methods
TOMLDataSaver::TOMLDataSaver(const std::string &appName) {
  std::string homeDir = getHomeDirectory();
  saveDir = homeDir + "/.local/share/" + appName;
  saveFile = saveDir + "/highscore.toml";

  // Create directory structure
  if (!createDirectoriesRecursive(saveDir)) {
    std::cerr << "Warning: Could not create save directory" << std::endl;
  }
}

bool TOMLDataSaver::saveHighScore(int score, const std::string &playerName) {
  std::ofstream file(saveFile, std::ios::trunc);
  if (!file.is_open()) {
    std::cerr << "Failed to open save file: " << saveFile << std::endl;
    return false;
  }

  std::string timestamp = getCurrentTimestamp();

  // Write TOML format
  file << "# High Score Data\n"
       << "# Generated on " << timestamp << "\n\n"
       << "[game]\n"
       << "name = \"Smashers\"\n"
       << "version = \"1.0\"\n\n"
       << "[player]\n"
       << "name = \"" << playerName << "\"\n"
       << "high_score = " << score << "\n"
       << "achieved_at = \"" << timestamp << "\"\n\n"
       << "[statistics]\n"
       << "total_games = 1\n"
       << "last_updated = \"" << timestamp << "\"\n";

  file.close();
  return file.good();
}

int TOMLDataSaver::loadHighScore() const {
  std::ifstream file(saveFile);
  if (!file.is_open()) {
    return 0; // Default score if file doesn't exist
  }

  std::string line;
  while (std::getline(file, line)) {
    // Use the new getTOMLValue method
    std::string value = getTOMLValue(line, "high_score");
    if (!value.empty()) {
      try {
        return std::stoi(value);
      } catch (const std::exception &e) {
        std::cerr << "Error parsing high score: " << e.what() << std::endl;
        return 0;
      }
    }
  }
  return 0;
}

bool TOMLDataSaver::updateHighScore(int newScore,
                                    const std::string &playerName) {
  int currentHighScore = loadHighScore();
  if (newScore > currentHighScore) {
    return saveHighScore(newScore, playerName);
  }
  return true; // No update needed, but not an error
}

const std::string &TOMLDataSaver::getSaveFilePath() const { return saveFile; }

// Standalone functions for backward compatibility
std::string getSaveFilePath(const std::string &filename) {
  const char *homeDir = std::getenv("HOME");
  if (!homeDir) {
    struct passwd *pw = getpwuid(getuid());
    if (pw && pw->pw_dir) {
      homeDir = pw->pw_dir;
    } else {
      homeDir = "/tmp";
    }
  }

  std::string dir = std::string(homeDir) + "/.local/share/vins.dev.smashers";

  try {
    std::filesystem::create_directories(dir);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Failed to create directory: " << e.what() << std::endl;
  }

  return dir + "/" + filename;
}

inline std::string TOMLDataSaver::getTOMLValue(const std::string &line,
                                               const std::string &key) const {
  // Look for "key="
  std::string pattern = key + "=";
  auto pos = line.find(pattern);
  if (pos == std::string::npos) {
    // Try with space: "key ="
    pattern = key + " =";
    pos = line.find(pattern);
    if (pos == std::string::npos)
      return "";
  }
  // Find the position after '='
  auto eqPos = line.find('=', pos);
  if (eqPos == std::string::npos)
    return "";
  // Extract the value part and trim whitespace
  std::string value = line.substr(eqPos + 1);
  return trim(value);
}
// Trims whitespace from both ends of a string
std::string trim(const std::string &s) {
  auto start = s.find_first_not_of(" \t\r\n");
  auto end = s.find_last_not_of(" \t\r\n");
  if (start == std::string::npos)
    return "";
  return s.substr(start, end - start + 1);
}
void saveHighScoreTOML(int score) {
  TOMLDataSaver saver;
  if (!saver.saveHighScore(score)) {
    std::exit(10);
  }
}
