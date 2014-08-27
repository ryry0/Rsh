#include <builtin.h>

namespace builtin
{
Manager::~Manager() {
}

bool Manager:: Execute(const std::vector<std::string> &tokens) {
  token_list_ = tokens;
  DataType function;

  //if the command is not found
  if (builtin_command_table_.Retrieve(token_list_[0], function) == false) {
    return false;
  }

  //if the command is a builtin function
  else {
    return_value_ = (this->*function)();
    return true;
  }
} //end execute
}
