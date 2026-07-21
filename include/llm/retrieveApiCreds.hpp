#pragma once

#include <cstdlib>
#include <string>

#define API_URL_NAME "FIX_LLM_API_URL"
#define API_KEY_NAME "FIX_LLM_API_KEY"


inline std::string retrieveEnv(const char* key) {
  char* var = std::getenv(key);
  return (var == NULL) ? "" : std::string(var);
}

[[nodiscard]] static std::string retrieveApiURL() {
  return retrieveEnv(API_URL_NAME);
}

[[nodiscard]] static std::string retrieveApiKey() {
  return retrieveEnv(API_KEY_NAME);
}
