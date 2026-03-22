#include "offline/DirectoryScanner.h"

#include <dirent.h>
#include <sys/stat.h>  // 用于判断文件类型

#include <cstring>

std::vector<std::string> DirectoryScanner::scan(const std::string& dir) {
  std::vector<std::string> result;

  // 打开目录
  DIR* dp = opendir(dir.c_str());
  if (dp == nullptr) {
    return result;  // 打开失败直接返回空
  }

  struct dirent* entry;

  // 遍历目录
  while ((entry = readdir(dp)) != nullptr) {
    std::string name = entry->d_name;

    // 跳过 . 和 ..
    if (name == "." || name == "..") {
      continue;
    }

    // 拼接完整路径
    std::string fullPath = dir + "/" + name;

    // 判断是否为普通文件
    struct stat st;
    if (stat(fullPath.c_str(), &st) == 0) {
      if (S_ISREG(st.st_mode)) {
        result.push_back(fullPath);
      }
    }
  }

  // 关闭目录
  closedir(dp);

  return result;
}