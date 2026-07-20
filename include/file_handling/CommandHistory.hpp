#pragma once

#include <string>
// #include <vector>
#include <fstream>
#include <filesystem>

#include "getHomeDirectory.hpp"


/*
 * Factory to automatically handle the resource of ~/.zsh_history or ~/.bash_history
 *
 * Finds and opens the file, closes on destructor, provides functions to read from
 * the file with abstraction and RAII principles.
 */
class CommandHistory {
  private:
    std::ifstream file;

  public:
    explicit CommandHistory(std::string& error);
    CommandHistory(const CommandHistory&& other) = delete; // no-move resource, holds a file
    CommandHistory(const CommandHistory& other) = delete; // no-copy resource, holds a file
    ~CommandHistory(); // explicit destructor to close the file

    // TODO: [[nodiscard]] bool hasNPreviousCommands(int n);
    [[nodiscard]] bool hasPreviousCommand();

    // TODO: [[nodiscard]] std::vector<std::string> getNPreviousCommands(int n);
    [[nodiscard]] std::string getPreviousCommand();
};
