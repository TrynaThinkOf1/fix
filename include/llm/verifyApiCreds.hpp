#pragma once

#include <string>
#include <regex>

[[nodiscard]] static bool verifyApiURL(const std::string& url) {
  // raw string literal so the compiler doesn't miniterpret \escape characters
  std::regex url_matcher(R"(https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&//=]*))");

  return std::regex_match(url, url_matcher);
}

[[nodiscard]] static bool verifyApiKey(const std::string& key) {
  return !key.empty();
}

[[nodiscard]] static bool verifyApiModel(const std::string& model) {
  return !model.empty();
}