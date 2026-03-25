#pragma once
#include <map>
#include <set>
#include <string>

class KeyWordProcessor {
 public:
  KeyWordProcessor();
  void process(const std::string& ch_dir, const std::string& en_dir);

 private:
  void create_en_dict(const std::string& dir, const std::string& outfile);

 private:
  std::set<std::string> en_stop_words_;
};