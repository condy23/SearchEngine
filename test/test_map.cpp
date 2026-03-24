#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;
int main() {
  string text = "hello world hello cpp hello world";
  map<string, int> wordCount;
  stringstream iss(text);
  string word;
  while (iss >> word) {
    wordCount[word]++;
  }
  for (const auto& [key, value] : wordCount) {
    cout << key << ":" << value << endl;
  }
  return 0;
}