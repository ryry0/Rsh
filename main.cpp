#include <iostream>
#include <csignal>
#include <parser.h>
#include <unistd.h>

void PrintPrompt();
void SigIntHandler (int parameter) {
  exit(0);
}

int main() {
  signal (SIGINT, SigIntHandler);
  std::string input;
  std::vector<std::string> tokens;
  Parser *command_parser = new Parser(' ');

  while (1) {
    PrintPrompt();
    getline(std::cin, input);
    command_parser->Parse(input);
    tokens = command_parser->GetTokens();

    for (auto i : tokens)
      std::cout << i << "\n";

    command_parser->ClearTokens();
  }

  delete command_parser;
  return 0;
} //end main

/*
 * PrintPrompt()
 * Grabs the directory and prints it.
 */
void PrintPrompt() {
  char buffer[100];
  std::vector<std::string> tokenized_path;
  Parser path_parser('/');

  getcwd(buffer, 100);
  path_parser.Parse(buffer);
  tokenized_path = path_parser.GetTokens();

  std::cout << tokenized_path.back() << " >";
} //end printprompt
