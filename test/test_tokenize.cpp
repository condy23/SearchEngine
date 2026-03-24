#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main() {
  // 1. 读取data/corpus/en/test1.txt
  // 使用ifstream读取文件
  // 使用getline循环读取到每一行
  ifstream file("data/corpus/en/test1.txt");
  if (!file.is_open()) {
    cerr << "找不到文件!" << endl;
    return 1;
  }

  // 将停用词加载到set<string>中,过滤掉停用词再输出
  ifstream stop_words("data/stop_words/en_stop_words.txt");
  if (!stop_words.is_open()) {
    cerr << "找不到文件!" << endl;
    return 1;
  }
  // 循环存入set
  set<string> stopWords;
  string stopWordsLine;
  while (getline(stop_words, stopWordsLine)) {
    stopWords.insert(stopWordsLine);
  }
  // 2. 将读取到的内容去掉标点和数字
  // 对读取到的一行处理,去除标点和数字
  string line;
  while (getline(file, line)) {
    for (char& c : line) {
      // 使用char类型挨个读取line的每一个字符
      if (!isalpha(c)) {  // 如果不是字母
        c = ' ';          // 将c替换成空格
      }
      // 将每一个字母替换成小写
      c = tolower(c);
    }
    // 使用空格分割单词输出单词
    stringstream iss(line);
    string word;
    while (iss >> word) {
      if (stopWords.count(word) == 0) {
        cout << word << endl;
      }
    }
  }
  return 0;
}