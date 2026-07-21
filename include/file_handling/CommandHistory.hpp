#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cmath>

#include "getHomeDirectory.hpp"

#define BUFFER_SIZE 4096


/*
 * Factory to automatically handle the resource of ~/.zsh_history or ~/.bash_history
 *
 * Finds and opens the file, closes on destructor, provides functions to read from
 * the file with abstraction and RAII principles.
 */
class CommandHistory {
  private:
    std::fstream file;

    bool is_at_end = false;
    bool goToEnd();

  public:
    explicit CommandHistory(std::string& error);
    CommandHistory(const CommandHistory&& other) = delete; // no-move resource, holds a file
    CommandHistory(const CommandHistory& other) = delete; // no-copy resource, holds a file
    ~CommandHistory(); // explicit destructor to close the file

    [[nodiscard]] std::vector<std::string> getNPreviousCommands(int n);

    [[nodiscard]] inline std::string getPreviousCommand() {
      return this->getNPreviousCommands(1)[0];
    }
};
