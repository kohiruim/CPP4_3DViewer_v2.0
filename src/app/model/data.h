#ifndef DATA_H_
#define DATA_H_
#include <vector>

struct Data {
  int countVertex = 0;
  int countPolygon = 0;
  std::vector<std::vector<double>> vertex = {{}};
  std::vector<std::vector<int>> polygon = {};
  std::vector<int> countVertexInGroup = {};
};

enum class Axis { x, y, z };

#endif  // DATA_H_
