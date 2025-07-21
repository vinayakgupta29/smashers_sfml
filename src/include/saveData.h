#pragma once
#include <string>

class TOMLDataSaver {
private:
  std::string saveDir;
  std::string saveFile;

  std::string getCurrentTimestamp() const;
  bool createDirectoriesRecursive(const std::string &path) const;
  std::string getHomeDirectory() const;
  inline std::string getTOMLValue(const std::string &line,
                                  const std::string &key) const;

public:
  TOMLDataSaver(const std::string &appName = "vins.dev.smashers");

  bool saveHighScore(int score, const std::string &playerName = "onii_chan");
  int loadHighScore() const;
  bool updateHighScore(int newScore,
                       const std::string &playerName = "onii_chan");
  const std::string &getSaveFilePath() const;
};

// Standalone functions for backward compatibility
std::string getSaveFilePath(const std::string &filename);
void saveHighScoreTOML(int score);
bool isHighScore(int score);
inline std::string trim(const std::string &s);
