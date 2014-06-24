/*
 * Author: Ryan - David Reyes
 */
//std includes
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//other includes
#include <parser.h>
#include <history.h>
#include <getch.h>
#include <builtin.h>

#include <ansicodes.h>
#include <xstring.cpp>
#include <primes.cpp>
#include <bitvect.cpp>
#include <hashfunctions.cpp>

const char CTRL_C      = 3;
const char ARROW_IND   = 27; //27 precedes arrow keys
const char ARROW_UP    = 'A';
const char ARROW_DOWN  = 'B';
const char ARROW_RIGHT = 'C';
const char ARROW_LEFT  = 'D';

const size_t HISTORY_SIZE = 10;
const std::string HISTORY_FILE = "history.dat";

void PrintPrompt();
int ExecuteExternalCommand(const std::vector<std::string> &command_tokens,
    pid_t &child_pid);

void SigIntHandler (int parameter) {
}

int main() {
  signal(SIGINT, SigIntHandler);

  bool        running = true;
  std::string input_buffer;
  char        input_char;
  size_t      cursor_position = 0;
  int         return_value = 0;
  int         child_pid;
  Parser      command_parser(' ');
  History     command_history(HISTORY_SIZE);

  std::vector<std::string> tokens;
  builtin::Manager builtin_manager;
  command_history.LoadHistory(HISTORY_FILE);

  while (running) {
    PrintPrompt();
    do {
      input_char = term::getch();

      //check for special characters
      switch (input_char) {
        case CTRL_C:
          input_buffer.clear();
          std::cout << "\n";
          break;

        case '\b':
        case 127:
          if (cursor_position > 0) {
            std::cout << "\b \b";
            --cursor_position;
          }
          if (!input_buffer.empty()) {
            input_buffer.pop_back();
          }
          break;

        case '\t': //tab
        case ARROW_IND: //arrow indicator
          break;
        case '\n': //newline character will not be appended.
          std::cout << "\n";
          break;

        case ARROW_UP:
          input_buffer = command_history.GetPrevious();
          //clear the screen to prompt
          for (unsigned int i = 0; i < cursor_position; i++)
            std::cout << "\b \b";
          cursor_position = input_buffer.length();//make sure backspace works.
          std::cout << input_buffer;
          break;

        case ARROW_DOWN:
          input_buffer = command_history.GetNext();
          //clear the screen to prompt
          for (unsigned int i = 0; i < cursor_position; i++)
            std::cout << "\b \b";
          cursor_position = input_buffer.length();//make sure backspace works.
          std::cout << input_buffer;
          break;

        default: //add it to the input string
          std::cout << input_char;
          input_buffer += input_char;
          cursor_position ++;
          break;
      }
    } while (input_char != '\n' && input_char != 3);

    //store the history
    command_history.AddToHistory(input_buffer);

    //parse the string
    command_parser.Parse(input_buffer);
    tokens = command_parser.GetTokens();

    //interpret the command
    if (!tokens.empty()) { //check if its empty before doing anything
      if (builtin_manager.Execute(tokens)) {
        return_value = builtin_manager.GetReturnValue();
        running = !builtin_manager.GetExitFlag();
        if (builtin_manager.ReadHistory())
          command_history.Dump();
      }
      else {
        return_value = ExecuteExternalCommand(tokens, child_pid);
      }
    }

    command_parser.ClearTokens();
    input_buffer.clear();
    cursor_position = 0;
  }

  command_history.WriteHistoryToFile(HISTORY_FILE);

  return return_value;
} //end main

/*
 * PrintPrompt()
 * Grabs the directory and prints it.
 */
void PrintPrompt() {
  char buffer[100];
  char uid_char;
  std::vector<std::string> tokenized_path;
  Parser path_parser('/');

  getcwd(buffer, 100);
  path_parser.Parse(buffer);
  tokenized_path = path_parser.GetTokens();

  if (getuid() != 0)
    uid_char = '%';
  else
    uid_char = '#';

  std::cout << ANSI_COLOR_CYAN << tokenized_path.back();
  std::cout << ANSI_COLOR_BLUE << " " << uid_char << ANSI_COLOR_RESET << ">";
} //end printprompt

int ExecuteExternalCommand(const std::vector<std::string> &command_tokens,
    pid_t &child_pid) {
  int status = -1;
  int exec_return;
  std::vector<char *> c_string_tokens;

  c_string_tokens.reserve(command_tokens.size()+1);
  for (auto i = command_tokens.begin(); i != command_tokens.end(); ++i)
    c_string_tokens.push_back(const_cast<char*>(&(*i)[0]));
        //const_cast<char *>(command_tokens[i].c_str()));
  c_string_tokens.push_back(NULL); //has to end with null pointer

  //for (auto i : c_string_tokens)
    //std::cout << i;

  child_pid = fork(); // a child gets zero back
  if (child_pid == 0) { //child process code
    exec_return = execvp(c_string_tokens[0], &c_string_tokens[0]);
    if (exec_return == -1) {
      std::cout << "rsh: command not found: " << command_tokens[0] << "\n";
      exit(-1);
    }
  }
  else { //parent process code
    //if (isbackgroundjob)
    //  record in background job list
    //else
    waitpid(child_pid, &status, 0);
  }
  return status;
}
