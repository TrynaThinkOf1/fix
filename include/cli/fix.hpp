#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "cli/streamWriteCallback.hpp"
#include "cli/loadingBar.hpp"
#include "file_handling/CommandHistory.hpp"
#include "llm/CurlWrapper.hpp"
#include "llm/retrieveApiCreds.hpp"
#include "llm/verifyApiCreds.hpp"

const std::string initial_sysprompt =
"You are an LLM designed only to fix terminal commands. It is unknown which operating system these "
"commands are for, assume unix-based unless specified later.\n"
"Your entire task is this: read in the user's previously entered commands (as well as any user-added context), and "
"generate new commands that will run properly while perserving the intended purpose of the commands.\n"
"You will also generate a 1-3 sentence explanation of the erros and fixes. You will not generate any other content.\n"
"If you believe the commands should run properly, just tell the user that there shouldn't be erros, and maybe they need "
" to add more context about the specific errors.\n"
"This user could potentially be on a strict usage limit, so keep your reasoning and response quick and to-the-point.\n"
"Output the explanation of errors, then two newlines, then each separate fixed command enclosed in backticks.\n"
"Godspeed.\n\n";


int fix(int n, const std::string& context);