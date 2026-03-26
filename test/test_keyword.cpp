#include <iostream>

#include "offline/KeywordProcessor.h"

int main() {
  KeyWordProcessor kwp;
  kwp.process("data/corpus/ch", "data/corpus/en");
  return 0;
}