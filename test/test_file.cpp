#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream file("data/corpus/en/test1.txt");
  if (!file.is_open()) {
    std::cerr << "找不到文件" << std::endl;
    return 1;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << std::endl;
  }
  file.close();
  return 0;
}