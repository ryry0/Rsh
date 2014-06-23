/*
 * Author: Ryan - David Reyes
 */
#include <iostream>
#include <parser.h>

Parser::Parser() {
}

Parser::Parser(const char delimiter) : delimiter_(delimiter) {
}

Parser::~Parser() {
}

void Parser::SetDelimiter(const char delimiter) {
  delimiter_ = delimiter;
}

/*
 * Parse()
 * Creates a stringstream buffer out of the input. Then uses getline
 * to parse the buffer into tokens.
 */
void Parser::Parse(const std::string input) {
  //create a string out of the input with no newlines
  std::string stripped_string(input);
  stripped_string.erase(std::remove(stripped_string.begin(),
        stripped_string.end(), '\n'), stripped_string.end());

  std::istringstream buffer(stripped_string);
  for (std::string token; getline(buffer, token, delimiter_);)
    tokens_.push_back(token);
} //end Parse

void Parser::CopyTokens(std::vector<std::string> &destination) {
  destination = tokens_;
}

const std::vector<std::string> &Parser::GetTokens() const {
  return tokens_;
}

void Parser::ClearTokens() {
  tokens_.clear();
}

void Parser::DumpTokens() {
  for (auto i : tokens_)
    std::cout << i << "\n";
}

