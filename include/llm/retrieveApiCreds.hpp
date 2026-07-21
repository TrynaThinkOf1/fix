#pragma once

#include <cstdlib>
#include <string>

#define API_URL_NAME "FIX_LLM_API_URL"
#define API_KEY_NAME "FIX_LLM_API_KEY"
#define API_MODEL_NAME "FIX_LLM_MODEL"


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

[[nodiscard]] static std::string retrieveApiModel() {
  return retrieveEnv(API_MODEL_NAME);
}
