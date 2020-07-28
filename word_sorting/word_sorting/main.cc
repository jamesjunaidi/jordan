#include <iostream>
#include <string>
#include <vector>

// put your solution here:
void solve(std::vector<std::string> words) {

}


void test() {
  std::vector<std::string> v = {"james", "James", "Z", "z", "A", "B", "AA", "ABC", "abc", "bca"};

  std::cout << "Expected Answer:" << std::endl << "A" << std::endl << "AA" << std::endl << 
    "abc" << std::endl << "ABC" << std::endl <<  "B" << std::endl << "bca" << std::endl << "James" <<
    std::endl << "james" << std::endl << "z" << std::endl << "Z" << std::endl;

  std::cout << "Your Answer: " << std::endl;
  solve(v);
}


int main(void) {
  test();

  return 0;
}

