#include "offline/DirectoryScanner.h"

#include <dirent.h>

#include <string>
#include <vector>
std::vector<std::string> DirectoryScanner::scan(const std::string& dir) {
  std::vector<std::string> result;
  // 打开目录
  DIR* dp = opendir(dir.c_str());
  // 错误判断
  if (dp == nullptr) {
    return result;
  }
  // 定义一个
  //  定义一个结构体对象存储readdir读取到的内容
  struct dirent* entry;
  while ((entry = readdir(dp)) != nullptr) {
    std::string name = entry->d_name;
    // 跳过.和..
    if (name == "." || name == "..") {
      continue;
    }
    // 跳过所有隐藏文件
    if (name[0] == '.') {
      continue;
    }
    if (entry->d_type == DT_REG) {
      std::string fullPath = dir + "/" + name;
      result.push_back(fullPath);
    }
  }
  closedir(dp);
  return result;
}