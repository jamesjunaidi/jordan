#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool search(std::string item, std::vector<std::string> &words) {
  for (auto a : words) {
    if (a == item)
      return true;
  }
  return false;
}

void run(std::vector<std::string> &words) {
  std::string in;
  std::cin >> in;
  while (std::cin) {
    if (search(in, words))
      std::cout << "Word " << in << " found" << std::endl;
    else
      std::cout << "Word " << in << " not found" << std::endl;
    std::cin >> in;
  }
}

int main(void) {
  std::vector<std::string> items;
  std::ifstream file;
  std::string buf;
  file.open("words.txt");
  if (file.is_open()) {
    while (getline(file, buf)) {
      items.push_back(buf);
    }
  }
  run(items);
  std::ofstream newfile;
  newfile.open("sorted_words.txt");
  std::sort(items.begin(), items.end());
  for (auto &a : items) {
    newfile << a << "\n";
  }
  return 0;
}
