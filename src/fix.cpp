#include "cli/fix.hpp"
#include <cstdlib>


int fix(int n, const std::string& context) {
  std::string err;
  
  CommandHistory History(err);
  if (!err.empty()) {
    std::cerr << "\t[ERROR] " << err << std::endl;
    return EXIT_FAILURE;
  }
  
  const std::vector<std::string> commands = History.getNPreviousCommands(n);

  for (const std::string& cmd : commands) {
    std::cout << "\t" << cmd << "\n";
  }
  std::cout << "Are these your last " << n << " entered commands (y[ES]/n[O]): ";
  char conf;
  std::cin >> conf;
  std::cout << '\n';

  if (conf == 'y') {
    std::thread spin_thread(spinner);
    
    CurlWrapper Curl;

    const std::string api_url = retrieveApiURL();
    if (!verifyApiURL(api_url)) {
      std::cerr << "\t[ERROR] Could not connect to LLM: invalid API URL." << std::endl;
      return EXIT_FAILURE;
    }
    const std::string api_key = retrieveApiKey();
    if (!verifyApiKey(api_key)) {
      std::cerr << "\t[ERROR] Could not connect to LLM: invalid API Key." << std::endl;
      return EXIT_FAILURE;
    }
    const std::string api_model = retrieveApiModel();
    if (!verifyApiModel(api_model)) {
      std::cerr << "\t[ERROR] Could not connect to LLM: invalid API Model." << std::endl;
      return EXIT_FAILURE;
    }

    std::string prompt = initial_sysprompt + "User-added content: " + context + "\n\nCommands:\n";
    for (const std::string& cmd : commands) {
      prompt += "`" + cmd + "`\n";
    }

    std::unordered_map<std::string, std::string> headers = {{"Authorization", "Bearer " + api_key}, {"Content-Type", "application/json"}};

    json messages;
    messages["role"] = "user";
    messages["content"] = prompt;
    
    json body;
    body["model"] = api_model;
    body["stream"] = true;
    body["messages"] = (json[]){messages,};

    // this ends the spinner
    long code = Curl.sendRequest(
      api_url,
      headers,
      body,
      streamWriteCallback,
      err
    );
    if (!err.empty() || code == -1) {
      std::cerr << "\t[ERROR] cURL error: " << err << std::endl;
      return EXIT_FAILURE;
    }
    
    spin_thread.join();

    std::cout << "\n\nExiting..." << std::endl;

    return EXIT_SUCCESS;
  }
  
  std::cout << "Then fetching your previous commands failed.\nExiting..." << std::endl;
  return EXIT_FAILURE;
}