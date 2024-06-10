#include "parser.h"

namespace s21 {

Parser::Parser(Data &data) : data_(data) {}

void Parser::ClearData() {
  data_.countVertexInGroup.clear();
  data_.vertex.clear();
  data_.polygon.clear();
  data_.countPolygon = data_.countVertex = 0;
}

int Parser::Counter(const std::string &filename) {
  int count = 0;
  ClearData();
  std::ifstream file(filename);
  if (file.is_open()) {
    while (std::getline(file, line_)) {
      if (line_[0] == 'g' && line_[1] == ' ') {
        data_.countVertexInGroup.push_back(0);
      }
      if (line_[0] == 'v' && line_[1] == ' ') {
        if (data_.countVertexInGroup.size() == 0) {
          data_.countVertexInGroup.push_back(0);
        }
        data_.countVertex++;
        data_.countVertexInGroup.back()++;
      }
      if (line_[0] == 'f' && line_[1] == ' ') {
        data_.countPolygon++;
      }
    }
    file.close();
  } else {
    count = -1;
  }
  return count;
}

void Parser::ParseVertex() {
  std::stringstream str(line_);
  std::string token;
  std::vector<double> v;
  if (data_.vertex.size() == 0) data_.vertex.push_back(v);
  while (str >> token) {
    if (token != "v") {
      double num = std::stod(token, NULL);
      v.push_back(num);
    }
  }
  data_.vertex.push_back(v);
  v.clear();
}

void Parser::ParsePolygon(int correctVertex) {
  std::stringstream str(line_);
  std::string token;
  std::vector<int> p;
  while (str >> token) {
    if (token != "f") {
      int num = std::stoi(token);
      if (num < 0) {
        num = correctVertex + num + 1;
      }
      p.push_back(num);
    }
  }
  data_.polygon.push_back(p);
  p.clear();
}

void Parser::ParseFile(const std::string &filename) {
  int correctVertex = 0, index = 0;
  std::ifstream file(filename);
  if (file.is_open()) {
    while (std::getline(file, line_)) {
      if (line_[0] == 'g' && line_[1] == ' ') {
        correctVertex += data_.countVertexInGroup[index];
        index++;
      }
      if (line_[0] == 'v' && line_[1] == ' ') {
        ParseVertex();
      }
      if (line_[0] == 'f' && line_[1] == ' ') {
        if (correctVertex == 0) {
          correctVertex += data_.countVertexInGroup[0];
          index++;
        }
        ParsePolygon(correctVertex);
      }
    }
    file.close();
  }
}
}  // namespace s21
