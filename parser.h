/*
 * Author: Ryan - David Reyes
 */
#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
/*
 * Parser class
 * the parser class takes an input, and seperates it into a list of tokens
 * found in tokens_.
 */
class Parser {
  public:
    Parser ();
    Parser (const char delimiter);
    ~Parser();

    void SetDelimiter(const char delimiter);
    void Parse       (const std::string input);
    void CopyTokens  (std::vector<std::string> &destination);
    void ClearTokens ();
    void DumpTokens  ();

    const std::vector<std::string> &GetTokens() const;

  private:
    std::vector<std::string> tokens_;
    char delimiter_;
};
#endif
