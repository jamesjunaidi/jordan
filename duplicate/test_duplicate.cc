#include <iostream>
#include "duplicate.cc"

int main(void) {
  vector<int> v = {1,2,3,4,5};
  vector<int> v1 = {1,1};
  vector<int> v2 = {1,2,3,4,5,5};
  vector<int> v3 = {2};

  cout << "Testing" << endl;
  cout << "Test 1: " << endl << "Expected: false: " << endl <<
    "Ans: " << boolalpha << containsDuplicate(v) << endl;
  cout << endl;
  cout << "Test 2: " << endl << "Expected: true: " << endl <<
    "Ans: " << boolalpha << containsDuplicate(v1) << endl;
  cout << endl;
  cout << "Test 3: " << endl << "Expected: true: " << endl <<
    "Ans: " << boolalpha << containsDuplicate(v2) << endl;
  cout << endl;
  cout << "Test 4: " << endl << "Expected: false: " << endl <<
    "Ans: " << boolalpha << containsDuplicate(v3) << endl;




}
