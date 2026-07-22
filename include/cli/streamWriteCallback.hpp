#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "cli/loadingBar.hpp"

// extern std::string main_buffer;

size_t streamWriteCallback(char* buffer, size_t size, size_t n_members, void* userp);
