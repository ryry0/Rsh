#include <builtin.h>
#include <sstream>

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
  builtin_command_table_.Insert("history", &Manager::history);

  builtin_command_table_.Insert("q", &Manager::exit);
  builtin_command_table_.Insert("exit", &Manager::exit);
  builtin_command_table_.Insert("jobs", &Manager::jobs);
  builtin_command_table_.Insert("kill", &Manager::kill);
  exit_flag_ = false;
  history_flag_ = false;
}

int Manager::cd() {
  int return_value = 0;
  char * home_path;
  if (token_list_.size() > 1) {
    return_value = chdir(token_list_[1].c_str());
    if (return_value == -1)
      std::cout << "cd: no such file or directory: " << token_list_[1] << "\n";
  }
  else {
    home_path = getenv("HOME");
    return_value = chdir(home_path);
  }
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

int Manager::exit() {
  int return_value = 0;
  exit_flag_ = true;
  if (token_list_.size() > 1) {
    std::stringstream buffer(token_list_[1]);
    buffer >> return_value; //extract the return value from token_list[1]
  }
  return return_value;
}

int Manager::history() {
  history_flag_ = true;
  return 0;
}

int Manager::jobs() {
  jobs_flag_ = true;
  return 0;
}

int Manager::kill() {
  kill_flag_ = true;
  return 0;
}
} //end namespace builtin
