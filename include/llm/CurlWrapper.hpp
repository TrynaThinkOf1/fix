#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>

#include <curl/curl.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

extern bool CURL_INITED;

/*
 * Just provides a modern C++ level abstraction over basic cURL
 */
class CurlWrapper {
  public:
    CurlWrapper();
    // allow default copy/move constructors, this isn't a volatile resource
    ~CurlWrapper();

    long sendRequest(
      const std::string& url,
      const std::unordered_map<std::string, std::string>& headers,
      const json& body,
      size_t (*write_data)(char* buffer, size_t size, size_t nmemb, void* userp),
      std::string& error
    );
};