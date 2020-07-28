#include <iostream>
#include <string>

using namespace std;

int main(void) {
  string s;

  // this while loop takes continous input until EOF
  while (cin >> s) {
    cout << "You entered: " << s << endl;
  }

  cout << "Program end" << endl;

  return 0;
}
