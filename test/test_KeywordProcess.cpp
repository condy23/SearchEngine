#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "offline/DirectoryScanner.h"
#include "offline/KeywordProcessor.h"

int main() {
  // 1.读取需要读取的文档和停用词?不知道是不是对的,目前想到要读取两个
  std::vector<std::string> enPath = DirectoryScanner::scan("data/corpus/en");
  std::vector<std::string> stopWordsPath =
      DirectoryScanner::scan("data/stop_words");
  // 2.读取文件,过滤停用词使用map存
  // 过滤停用词
  std::ifstream stopFile(stopWordsPath[0]);
  if (!stopFile.is_open()) {
    std::cerr << "找不到文件" << std::endl;
    return 1;
  }
  std::set<std::string> stopWords;
  std::string stopWordsLine;
  while (getline(stopFile, stopWordsLine)) {
    stopWords.insert(stopWordsLine);
  }
  // 使用循环来读取文件
  std::map<std::string, int> wordCount;
  for (size_t i = 0; i < enPath.size(); i++) {
    // 使用getline读取文件
    std::string line;
    std::ifstream file(enPath[i]);
    if (!file.is_open()) {
      std::cerr << "找不到文件" << std::endl;
      return 1;
    }
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
      std::stringstream ss(line);
      std::string word;
      while (ss >> word) {
        // 使用set的计数功能如果set里面没有就进入
        if (stopWords.count(word) == 0) {
          wordCount[word]++;
        }
      }
    }
  }

  // 3.最后将结果写入outfile格式化写入: 单词 频率
  std::ofstream outFile("output.txt");
  if (!outFile.is_open()) {
    std::cerr << "文件写入失败" << std::endl;
    return 1;
  }
  for (const auto& [word, count] : wordCount) {
    outFile << word << " " << count << std::endl;
  }
  stopFile.close();
  outFile.close();
  return 0;
}