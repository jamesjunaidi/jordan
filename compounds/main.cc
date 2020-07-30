#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Compound {

};


double solve(string &s) {

}


void test() {

  // testing
  string s1 = "C2H5OH";
  string s2 = "H2O";
  string s3 = "HO";
  string s4 = "Ho";
  string s5 = "SN3";
  string s6 = "Sn3";

  cout << "Test case: " << s1 << endl;
  cout << "Expected Ans: " <<
    "The atomic weight of " << s1 << " is 46.08" << endl;
  cout << "Your Answer: " << endl; solve(s1);

  cout << "Test case: " << s2 << endl;
  cout << "Expected Ans: " <<
    "The atomic weight of " << s2 << " is 18.02" << endl;
  cout << "Your Answer: " << endl; solve(s2);

  cout << "Test case: " << s3 << endl;
  cout << "Expected Ans: " <<
    "The atomic weight of " << s3 << " is 17.01" << endl;
  cout << "Your Answer: " << endl; solve(s3);

  cout << "Test case: " << s4 << endl;
  cout << "Expected Ans: " <<
    "The atomic weight of " << s4 << " is 164.93" << endl;
  cout << "Your Answer: " << endl; solve(s4);

  cout << "Test case: " << s5 << endl;
  cout << "Expected Ans: " <<
    "The atomic weight of " << s5 << " is 74.1" << endl;
  cout << "Your Answer: " << endl; solve(s5);

  cout << "Test case: " << s6 << endl;
  cout << "Expected Ans: " <<
    "The atomic weight of " << s6 << " is 356.13" << endl;
  cout << "Your Answer: " << endl; solve(s6);

}


int main(void) {
  // uncomment this to run the test, but I still want a version w/ continous input
   test();
}
