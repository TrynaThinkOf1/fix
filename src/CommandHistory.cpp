#include "file_handling/CommandHistory.hpp"


/*
 * Only constructor for class
 *
 * Finds and opens the file for command history
 * Any errors are returned as error strings - passed in string expected to be empty
 */
CommandHistory::CommandHistory(std::string& error) {
  const std::string home = getHomeDirectory();
  [[unlikely]] if (home.empty()) {
    error = "Failed to fetch command:  could not find user's home directory";
    return;
  }

  // check to see whether the history files exist and are filled

  std::filesystem::path history(home);
  history /= ".bash_history"; // add the file to the path
  if (std::filesystem::exists(history)) {
    if (std::filesystem::file_size(history) > 1) { // there is (likely) a command present
      this->file.open(history.string());
      if (this->file.is_open()) return; // otherwise it just passes to ZSH
    }
    // otherwise just pass the control over to check for ZSH
  }

  // if bash doesn't exist or is empty, try ZSH
  history.remove_filename();
  history /= ".zsh_history";
  if (std::filesystem::exists(history)) {
    if (std::filesystem::file_size(history) > 1) {
      this->file.open(history.string());
      if (!this->file.is_open()) {
        error = "Failed to fetch command:  could not open command history";
        return;
      } else {
        return;
      }
    }
  }

  error = "Failed to fetch command:  could not find command history";
}

CommandHistory::~CommandHistory() {
  if (this->file.is_open()) this->file.close(); // technically unnecessary (I believe)
}


[[nodiscard]] bool CommandHistory::hasPreviousCommand() {

}

[[nodiscard]] std::string CommandHistory::getPreviousCommand() {

}
