#include "offline/KeywordProcessor.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "offline/DirectoryScanner.h"
using namespace std;
KeyWordProcessor::KeyWordProcessor() {
  std::vector<std::string> paths = DirectoryScanner::scan("data/stop_words");
  // 循环读取,防止以后不止一个文件
  for (const auto& file : paths) {
    std::ifstream stop_file(file);
    if (!stop_file.is_open()) {
      std::cerr << "无法打开停用词文件" << std::endl;
      continue;
    }
    std::string word;
    while (stop_file >> word) {
      en_stop_words_.insert(word);
    }
  }
}
// 首先用process调用create_endict
void KeyWordProcessor::process(const std::string& ch_dir,
                               const std::string& en_dir) {
  create_en_dict(en_dir, "data/dict/en_dict.txt");
}
// 实现create_en_dict()
void KeyWordProcessor::create_en_dict(const std::string& dir,
                                      const std::string& outfile) {
  map<string, int> wordCount;

  // 1. 获取目录下所有文件
  vector<string> files = DirectoryScanner::scan(dir);

  for (const auto& file : files) {
    ifstream ifs(file);
    if (!ifs.is_open()) {
      cerr << "无法打开文件: " << file << endl;
      continue;
    }

    string line;
    while (getline(ifs, line)) {
      // 2. 预处理：非字母 -> 空格
      for (auto& ch : line) {
        if (!isalpha(ch)) {
          ch = ' ';
        } else {
          ch = tolower(ch);  // 转小写
        }
      }

      // 3. 分词
      stringstream ss(line);
      string word;
      while (ss >> word) {
        // 4. 过滤停用词
        if (en_stop_words_.count(word)) continue;

        // 5. 统计词频
        ++wordCount[word];
      }
    }
  }

  // 6. 输出结果
  ofstream ofs(outfile);
  if (!ofs.is_open()) {
    cerr << "无法打开输出文件!" << endl;
    return;
  }

  for (const auto& [word, count] : wordCount) {
    ofs << word << " " << count << endl;
  }

  cout << "英文词典生成完成: " << outfile << endl;
}