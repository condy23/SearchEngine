#pragma once
#include <map>
#include <set>
#include <string>

class KeyWordProcessor {
 public:
  KeyWordProcessor();
  void process(const std::string& chDir, const std::string& enDir);

 private:
  void create_en_dirt(const std::string& dir, const std::string& outfile);

 private:
  std::set<std::string> m_enStopWords;
};