#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
/*
 * Parser class
 *
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

    const std::vector<std::string> &GetTokens() const;

  private:
    std::vector<std::string> tokens_;
    char delimiter_;
};
#endif
