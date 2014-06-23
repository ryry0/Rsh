#include <builtin.h>

namespace builtin
{
Manager::~Manager() {
}

bool Manager:: Execute(const std::vector<std::string> &tokens) {
  token_list_ = tokens;
  DataType function;

  if (builtin_command_table_.Retrieve(token_list_[0], function) == false) {
    return false;
  }

  else {
    return_value_ = (this->*function)();
    return true;
  }
} //end execute
}
