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
  builtin_command_table_.Insert("pwd", &Manager::pwd);
}

int Manager::cd() {
  int return_value = chdir(token_list_[1].c_str());
  if (return_value == -1)
    std::cout << "cd: no such file or directory: " << token_list_[1] << "\n";
  return return_value;
}

int Manager::echo() {
  for (auto i = token_list_.begin() + 1; i != token_list_.end(); ++i)
      std::cout << *i << " ";
  std::cout << "\n";
  return 0;
}

int Manager::pwd() {
  char dir_string[100];
  getcwd(dir_string, 100);
  std::cout << dir_string << "\n";
  return 0;
}
}
