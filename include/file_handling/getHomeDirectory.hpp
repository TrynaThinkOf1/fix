#pragma once

#include <string>
#include <filesystem>
#include <unistd.h>
#include <pwd.h>


/*
 * Get the std::string of the user's home directory
 * 
 * On failure, it returns an empty string
 */
[[nodiscard]] static std::string getHomeDirectory() {
  char* envHomeDir = getenv("HOME"); // usually does the trick
  
  if (envHomeDir != nullptr) {
    return std::string(envHomeDir);
  } 
  
  // otherwise, we'll need the passwd entry for the user

  uid_t user = getuid();
  struct passwd* pwd = getpwuid(user);

  return std::string(pwd->pw_dir);
}