#include "cli/streamWriteCallback.hpp"


std::string main_buffer = "";

size_t streamWriteCallback(char* buffer, size_t size, size_t n_members, void* userp) {
  main_buffer += std::string(buffer, n_members * size);

  int fidx;
  for (int i = 0; i < main_buffer.size(); i++) {
    if (main_buffer[i] == '{') break;
    fidx++;
  }
  main_buffer = main_buffer.substr(fidx);

  const size_t nidx = main_buffer.find('\n');
  const std::string next = main_buffer.substr(0, (nidx == std::string::npos ? main_buffer.size() : nidx));

  
  if (!json::accept(next)) return n_members;
  json j = json::parse(next);
  if (!j.contains("choices")) return n_members;

  auto choices = j["choices"].get<std::vector<json>>();
  if (choices.size() < 1) return n_members;

  auto delta = choices[0]["delta"].get<json>();
  if (!delta.contains("content")) return n_members;
  done = true;
  
  
  std::cout << delta.value("content", std::string{});

  main_buffer = main_buffer.substr(next.size());
  
  return n_members;
}