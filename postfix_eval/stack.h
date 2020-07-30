#ifndef STACK_H_
#define STACK_H_
#include <vector>

template <typename T>
class Stack {
 private:
  std::vector<T> items;

 public:
  unsigned int Size() {
    return items.size();
  }
  // this function returns the top item
  T& Top(void) {
    if (!items.size())
        throw std::underflow_error("Empty Stack!");
    return items.back();
  }
  // this function removes the item at the end
  void Pop() {
    if (!items.size())
        throw std::underflow_error("Empty Stack!");
    items.pop_back();
  }
  // this function pushes an item back
  void Push(const T &item) {
    items.push_back(item);
  }
  // this function empties the stack
  void Empty(void) {
    while (items.size() > 0)
        items.pop_back();
  }
  // returns true if empty, and false if not empty
  bool isEmpty(void) {
    return !items.size();
  }
};


#endif  // STACK_H_


