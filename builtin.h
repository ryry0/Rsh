#ifndef BUILTIN_COMMANDS_H_
#define BUILTIN_COMMANDS_H_

#include <vector>
#include <string>
#include <unistd.h>

#include <xstring.h>
#include <hashclasses.h>
#include <primes.h>
#include <bitvect.h>

#include <hashtbl.h>
#include <compare.h>

/*
#include <xstring.cpp>
#include <primes.cpp>
#include <bitvect.cpp>
#include <hashfunctions.cpp>
*/

namespace builtin
{
class Manager {
  typedef std::string                  KeyType;
  typedef int                        (Manager::*DataType)();
  typedef hashclass::KISS < KeyType >  HashType;

  public: //main member functions
    Manager();
    ~Manager();

    bool Execute(const std::vector<std::string> &tokens);
    int GetReturnValue() const {return return_value_;}
    bool GetExitFlag   () const {return exit_flag_;}
    bool ReadHistory   () {
      if (history_flag_ == true) {
      history_flag_ = false;
      return true;
      } else
        return false;
    }

  private: //builtin functions:
    int cd();
    int echo();
    int pwd();
    int history();
    int exit();

  private:
    fsu::HashTable<KeyType, DataType, HashType> builtin_command_table_;
    std::vector<std::string> token_list_;
    int  return_value_;
    bool exit_flag_; //true if you want to exit
    bool history_flag_; //true if you want to read history
};

}
#endif
