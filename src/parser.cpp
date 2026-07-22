#include "cli/parser.hpp"


int parse(int argc, char** argv) {
  std::vector<std::string> args(argc);
  for (int i = 0; i < argc; i++) args[i] = std::string(argv[i]);
  
  if (argc <= 1) { // default functionality
    return fix(1, "");
  }
  
  if (std::find(args.begin(), args.end(), "-h") != args.end() || std::find(args.begin(), args.end(), "--help") != args.end()) { // help meny
    std::cout << "Fix - GNU General Purpose License 3.0 - Zevi Berlin\n";
    std::cout << "  Reads your previously entered command(s), passes them through an LLM for\n";
    std::cout << "   which you are responsible for providing the API credentials.\n";
    std::cout << "\nTo Define LLM API Credentials:\n";
    std::cout << "\tAdd `export " << API_URL_NAME << "=<YOUR URL HERE>` - for example, https://opencode.ai/zen/v1/messages\n";
    std::cout << "\tAdd `export " << API_KEY_NAME << "=<YOUR KEY HERE>` - for example, sk-9DcI5ZUGWTbzXi3DGA9WUDd92UIWAFaw82qbQASF\n";
    std::cout << "\tAdd `export " << API_MODEL_NAME << "=<YOUR MODEL NAME HERE>` - for example, big-pickle\n";
    std::cout << "\nUsage:\n";
    std::cout << "\tfix [...OPTIONS]\n";
    std::cout << "\nOptions:\n";
    std::cout << "\t-h, --help       Open this help menu.\n";
    std::cout << "\t-c, --context    Provide additional content to the LLM about the command(s).\n";
    std::cout << "\t-n<#>            Process more than one previous command.\n" << std::endl;
    
    return EXIT_SUCCESS;
  }

  if (std::find(args.begin(), args.end(), "-c") != args.end() || std::find(args.begin(), args.end(), "--context") != args.end()) {
    
  }
}