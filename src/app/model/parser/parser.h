#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <sstream>
#include <vector>

#include "../data.h"

namespace s21 {
class Parser {
 public:
  Parser(Data &data);
  ~Parser() = default;
  void ClearData();
  int Counter(const std::string &filename);
  void ParseFile(const std::string &filename);

 private:
  Data &data_;
  std::string line_;
  void ParseVertex();
  void ParsePolygon(int correctVertex);
};
}  // namespace s21
#endif  // PARSER_H
