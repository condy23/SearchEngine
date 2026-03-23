#include <iostream>
#include <string>
#include <vector>

#include "offline/DirectoryScanner.h"
using namespace std;
int main() {
  vector<string> result = DirectoryScanner::scan("data/corpus/en");
  for (const string& path : result) {
    cout << "文件路径:" << path << endl;
  }
  return 0;
}