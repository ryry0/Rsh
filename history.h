#ifndef HISTORY_H_
#define HISTORY_H_
#include <deque>
/*
 * History class
 * This class can be used to keep a history of string data.
 */
class History {
  public:
    History();
    History(size_t size);
    ~History();

    void SetHistorySize (size_t size) {history_max_size_ = size;}
    void AddToHistory   (const std::string input);
    //write/reads the history from a file
    bool WriteHistoryToFile(const std::string file_name);
    bool LoadHistory    (const std::string file_name);

    //functions for asking for previous history entries
    void ResetHistoryPosition();
    std::string GetPrevious();
    std::string GetNext    ();
    void Dump              ();

  private:
    size_t history_max_size_;
    std::deque<std::string> history_;
    std::deque<std::string>::reverse_iterator history_position_;
    //this variable holds what command in history will be returned by GetPrev,
    //getNext
};
#endif
