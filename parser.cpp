#include <parser.h>

Parser::Parser() {
}

Parser::Parser(const char delimiter) : delimiter_(delimiter) {
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
  std::istringstream buffer(input);
  for (std::string token; getline(buffer, token, delimiter_);)
    tokens_.push_back(token);
} //end Parse

void Parser::CopyTokens(std::vector<std::string> &destination) {
  std::copy(tokens_.begin(), tokens_.end(), destination.begin());
}

const std::vector<std::string> &Parser::GetTokens() const {
  return tokens_;
}

void Parser::ClearTokens() {
  tokens_.clear();
}
