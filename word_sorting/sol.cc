#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

string lower(string s) {
  for (char &a : s) {
    a = tolower(a);
  }
  return s;
}

bool compare(string a, string b) {
  return (lower(a) < lower(b));
}

int solution(vector<string> v) {
  string s;
  while (cin >> s) {
    v.push_back(s);
  }
  
  sort(v.begin(), v.end(), compare);

  for (auto a : v) {
    cout << a << endl;
  }

  return 0;
}
