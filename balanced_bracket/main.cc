#include <iostream>
#include <string>

using namespace std;

bool solve(string expression) {

}

void test() {
  string one = "{[()]}";
  string two = "{[(])}";
  string three = "{{[[(())]]}}";
  cout << "Test case 1: " << one << endl;
  cout << boolalpha << solve(one) << endl;
  cout << "Expected: YES" << endl;
  cout << "Test case 2: " << two << endl;
  cout << boolalpha << solve(two) << endl;
  cout << "Expected: NO" << endl;
  cout << "Test case 3: " << three << endl;
  cout << boolalpha << solve(three) << endl;
  cout << "Expected: YES" << endl;
}

int main(void) {
  test();
}
