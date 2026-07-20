#include "file_handling/CommandHistory.hpp"

bool CommandHistory::goToEnd() {
  this->file.clear();
  this->file.seekg(0, std::ios::end); // go to the end of the file

  std::streamoff size = this->file.tellg(); // streamoff is usually just an alias for long long
  if (size <= 0) return false; // simple as

  this->is_at_end = true; // we have arrived at the end
  return true;
}


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
      this->file.open(history.string(), std::ios_base::in | std::ios::binary);
      if (this->file.is_open()) return; // otherwise it just passes to ZSH
    }
    // otherwise just pass the control over to check for ZSH
  }

  // if bash doesn't exist or is empty, try ZSH
  history.remove_filename();
  history /= ".zsh_history";
  if (std::filesystem::exists(history)) {
    if (std::filesystem::file_size(history) > 1) {
      this->file.open(history.string(), std::ios_base::in | std::ios::binary);
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


[[nodiscard]] std::string CommandHistory::getPreviousCommand() {
  if (!this->is_at_end) {
    if (!this->goToEnd()) return "";
  }
  
  std::streamoff pos = this->file.tellg() - (std::streamoff)1; // ignore the last \n char

  std::vector<char> buffer(BUFFER_SIZE);
  int found = 0;

  // found < 2 because we want to get the last command BEFORE calling fix
  while (pos > 0 && found < 2) {
    // can we read a full BUFFER_SIZE bytes or only pos bytes
    const int nbytes_to_read = std::min<std::streamoff>(pos, buffer.size());
    pos -= nbytes_to_read; // go back that many bytes so that we can read that many bytes
    
    this->file.seekg(pos);
    this->file.read(buffer.data(), nbytes_to_read);

    for (int i = nbytes_to_read - 1; i >= 0; i--) {
      if (buffer[i] == '\n') {
        pos += i;
        found++;
        break;
      }
    }
  }

  this->file.clear();
  this->file.seekg(pos + 1);

  std::string line;
  std::getline(this->file, line);

  // deformat it
  size_t semidx = line.find(';'); 

  return line.substr(semidx + 1);
}
