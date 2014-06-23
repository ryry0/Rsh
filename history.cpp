#include <fstream>
#include <iostream>
#include <algorithm>
#include <history.h>

History::History() {
  history_position_ = history_.rend();
}

History::History(size_t size) : history_max_size_(size) {
  history_position_ = history_.rend();
}

History::~History() {
}
/*
 * WriteHistoryToFile
 * writes the history from the deque into a file
 */
bool History::WriteHistoryToFile(const std::string file_name) {
  std::ofstream output_file;
  output_file.open(file_name.c_str());
  if (!output_file)
    return false;

  for (auto i : history_)
    output_file << i << "\n";

  output_file.close();
  return true;
}


/*
 * AddToHistory
 * Pushes back the deque with the new input string.
 * pops the front when it gets too big, so you keep the most recent commands.
 */
void History::AddToHistory(const std::string input) {
   //create a string out of the input with no newlines
  std::string stripped_string(input);
  stripped_string.erase(std::remove(stripped_string.begin(),
        stripped_string.end(), '\n'), stripped_string.end());

  if (history_.size() >= history_max_size_)
    history_.pop_back();

  history_.push_front(input);
  history_position_ = history_.rend();
}

/*
 * LoadHistory
 * loads the history from a file and places it into the deque
 */
bool History::LoadHistory(const std::string file_name) {
  std::string input_string;
  std::ifstream input_file;
  input_file.open(file_name.c_str());
  if (!input_file)
    return false;

  while (getline(input_file,input_string))
    history_.push_back(input_string);

  history_position_ = history_.rend();
  return true;
}

std::string History::GetPrevious() {
  //check position bounds
  if(!history_.empty()) {
    if (history_position_ <= history_.rend() &&
        history_position_ > history_.rbegin()) {
      return *--history_position_;
    }
    else { //reset the position

      return *history_position_;
    }
  }
  return "";
}

std::string History::GetNext() {
  //check position bounds
  if(!history_.empty()) {
    if (history_position_ < history_.rend()-1 &&
        history_position_ >= history_.rbegin()) {
      return *++history_position_;
    }
    else { //reset the position
      history_position_ = history_.rend();
      return "";
    }
  }
  return "";
}

void History::ResetHistoryPosition() {
  history_position_ = history_.rbegin();
}

void History::Dump() {
  int history_counter = 1;
  if (!history_.empty()) {
  for (auto i = history_.rbegin(); i != history_.rend(); ++i)
    std::cout << " " << history_counter++ << "\t" << *i << "\n";
  }
}
