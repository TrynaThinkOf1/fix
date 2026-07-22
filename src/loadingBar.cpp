#include "cli/loadingBar.hpp"


std::atomic<bool> done = false;

void spinner() {
  const char frames[] = {'|', '/', '-', '\\'};
  int i = 0;

  while (!done) {
    std::cout << "\rLoading... " << frames[i++ % 4] << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  // Erase the line
  std::cout << "\r                     \r" << std::flush;
}