#include <iostream>
#include <csignal>
#include <parser.h>

void SigIntHandler (int parameter) {
  exit(0);
}

int main() {
  signal (SIGINT, SigIntHandler);
  std::string input;
  std::vector<std::string> tokens;
  Parser *command_parser = new Parser(' ');

  while (1) {
    std::cout << ">";
    getline(std::cin, input);
    command_parser->Parse(input);
    tokens = command_parser->GetTokens();

    for (auto i : tokens)
      std::cout << i << "\n";

    command_parser->ClearTokens();
  }

  delete command_parser;
  return 0;
}
