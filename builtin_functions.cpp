#include <builtin.h>

/*
 * This file contains all the functions that are built in the shell
 */
namespace builtin
{

Manager::Manager() {
  builtin_command_table_.Insert("cd", &Manager::cd);
  builtin_command_table_.Insert("chdir", &Manager::cd);
  builtin_command_table_.Insert("echo", &Manager::echo);
}

int Manager::cd() {
  return chdir(token_list_[1].c_str());
}

int Manager::echo() {
  for (auto i = token_list_.begin() + 1; i != token_list_.end(); ++i)
      std::cout << *i << " ";
  std::cout << "\n";
  return 0;
}

}
