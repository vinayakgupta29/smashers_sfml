#include <string>
#ifdef DEBUG_ASSET_PATH
// In debug, use project-relative path
#define ASSET_BASE_PATH "assets/"
#else
// In release, use executable-relative path
#include <limits.h>
#include <unistd.h>
inline std::string getExecutableDir() {
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  if (count != -1) {
    std::string exePath(result, count);
    size_t lastSlash = exePath.find_last_of('/');
    if (lastSlash != std::string::npos) {
      return exePath.substr(0, lastSlash + 1); // include trailing slash
    }
  }
  return "./";
}
#define ASSET_BASE_PATH (getExecutableDir() + "assets/")
#endif

std::string getAssetPath(const std::string &subpath) {
#ifdef DEBUG_ASSET_PATH
  return std::string("assets/") + subpath;
#else
  return getExecutableDir() + "assets/" + subpath;
#endif
}
