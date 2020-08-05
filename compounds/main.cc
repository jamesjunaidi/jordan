#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Compound {
  public:
    string symbol;
    double weight;

    Compound(string a, double b) {
      symbol = a;
      weight = b;
    }

    void printClass() {
      cout << "Symbol: " << symbol << endl << "Weight: " << weight << endl;
    }

    double getWeight() {
      return weight;
    }

    string getSymbol() {
      return symbol;
    }

};

vector<Compound> upload() {
  vector<Compound> v;
  ifstream myfile ("atomic_weights.txt");
  double weight;
  string symbol;
  string name;
  if (myfile.is_open()) {
    myfile >> weight >> symbol >> name;

    while (!myfile.eof()) {
      Compound *a = new Compound(symbol, weight);
      v.push_back(*a);
      myfile >> weight >> symbol >> name;
    }

    myfile.close();
  }

  return v;

}

string seperate(string a) {
  vector<string> elements;
  for (unsigned int i = 0; i < a.size(); i++) {
    string current;
    string counter;
    if (a[i] >= 'A' && a[i] <= 'Z') {
      if (a[i + 1] >= 'a' && a[i] <= 'z') {
        current += a[i];
        current += a[i + 1];

        if (a[i + 2] >= '1' && a[i + 2] <= 'A') {
          counter += a[i + 2];
          istringstream str(counter);
          counter.clear();
          int count;
          str >> count;
          for (int x = 0; x < count; x++) {
            elements.push_back(current);
          }
        }

        else {
          elements.push_back(current);
        }
      }
      else {
        current += a[i];

        if (a[i + 1] >= '1' && a[i + 1] <= 'A') {
          counter += a[i + 1];
          istringstream str(counter);
          counter.clear();
          int count;
          str >> count;
          for (int x = 0; x < count; x++) {
            elements.push_back(current);
          }
        }

        else {
          elements.push_back(current);
        }
      }
    }
  }

  a.clear();

  for (unsigned int i = 0; i < elements.size(); i++) {
    a += elements[i];
    a += " ";
  }

  return a;
}

double solve(string a, vector<Compound> v = upload()) {
  string b = seperate(a);
  istringstream str(b);
  double weight = 0;
  while (str) {
    string buf;
    str >> buf;
    for (Compound &a : v) {
      string symbol = a.getSymbol();
      if (buf == symbol) {
        weight += a.getWeight();
        break;
      }
    }
  }

  cout << endl << "The atomic weight of " << a << " is " << weight << endl << endl;

  return weight; 

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

  string input;

  cout << "Chemical composition?" << endl;
  while (getline(cin, input)) {
    solve(input);
    cout << "Chemical composition?" << endl;
  }

}
