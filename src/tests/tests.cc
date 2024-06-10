#include <gtest/gtest.h>

#include "../app/model/affine/affine.h"
#include "../app/model/parser/parser.h"

namespace s21 {
class Example {
 public:
  std::unique_ptr<Parser> parser_;
  std::unique_ptr<Affine> affine_;
  Example(Data& data)
      : parser_(std::make_unique<Parser>(data)),
        affine_(std::make_unique<Affine>(data)) {}
};
}  // namespace s21

TEST(Test, testParse1) {
  Data data;
  std::string filename = "tests/cube.obj";
  s21::Example test(data);

  int result1 = test.parser_->Counter(filename);
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(data.countVertex, 8);
  EXPECT_EQ(data.countPolygon, 12);
  EXPECT_EQ(data.countVertexInGroup.size(), 1);
  EXPECT_EQ(data.countVertexInGroup[0], 8);
  int result2 = test.parser_->Counter("something.obj");
  EXPECT_EQ(result2, -1);
}

TEST(Test, testParse2) {
  Data data;
  std::string filename = "tests/cube.obj";
  s21::Example test(data);
  std::vector<std::vector<double>> resultVertex = {
      {},          {1, 1, -1},   {1, -1, -1}, {1, 1, 1},  {1, -1, 1},
      {-1, 1, -1}, {-1, -1, -1}, {-1, 1, 1},  {-1, -1, 1}};
  std::vector<std::vector<int>> resultPolygon = {
      {5, 3, 1}, {3, 8, 4}, {7, 6, 8}, {2, 8, 6}, {1, 4, 2}, {5, 2, 6},
      {5, 7, 3}, {3, 7, 8}, {7, 5, 6}, {2, 4, 8}, {1, 3, 4}, {5, 1, 2}};
  test.parser_->Counter(filename);
  test.parser_->ParseFile(filename);
  EXPECT_EQ(data.polygon.size(), resultPolygon.size());
  EXPECT_EQ(data.vertex.size(), resultVertex.size());

  for (size_t i = 0; i < data.polygon.size(); i++) {
    EXPECT_EQ(data.polygon[i].size(), resultPolygon[i].size());
    for (size_t j = 0; j < data.polygon[i].size(); j++) {
      EXPECT_EQ(data.polygon[i][j], resultPolygon[i][j]);
    }
  }

  for (size_t i = 0; i < data.vertex.size(); i++) {
    EXPECT_EQ(data.vertex[i].size(), resultVertex[i].size());
    for (size_t j = 0; j < data.vertex[i].size(); j++) {
      EXPECT_EQ(data.vertex[i][j], resultVertex[i][j]);
    }
  }
}

TEST(Test, testParse3) {
  Data data;
  std::string filename = "tests/skull.obj";
  s21::Example test(data);
  std::vector<int> result = {3441, 864, 1184, 633};
  int result1 = test.parser_->Counter(filename);
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(data.countVertex, 6122);
  EXPECT_EQ(data.countPolygon, 9539);
  EXPECT_EQ(data.countVertexInGroup.size(), 4);
  for (size_t i = 0; i < data.countVertexInGroup.size(); i++) {
    EXPECT_EQ(data.countVertexInGroup[i], result[i]);
  }
}

TEST(Test, testParse4) {
  Data data;
  std::string filename = "tests/skull.obj";
  s21::Example test(data);
  test.parser_->Counter(filename);
  test.parser_->ParseFile(filename);
  EXPECT_EQ(data.countPolygon, data.polygon.size());
  EXPECT_EQ(data.polygon.size(), 9539);
  for (int i = 0; i < data.countPolygon; i++) {
    for (size_t j = 0; j < data.polygon[i].size(); j++) {
      EXPECT_TRUE(data.polygon[i][j] > 0);
    }
  }
}

TEST(Test, testMove) {
  Data data;
  std::string filename = "tests/cube.obj";
  s21::Example test(data);
  std::vector<std::vector<double>> resultVertex = {{},
                                                   {6.3, -0.8, 1.3},
                                                   {6.3, -2.8, 1.3},
                                                   {6.3, -0.8, 3.3},
                                                   {6.3, -2.8, 3.3},
                                                   {4.3, -0.8, 1.3},
                                                   {4.3, -2.8, 1.3},
                                                   {4.3, -0.8, 3.3},
                                                   {4.3, -2.8, 3.3}};
  test.parser_->Counter(filename);
  test.parser_->ParseFile(filename);
  test.affine_->MoveX(5.3);
  test.affine_->MoveY(-1.8);
  test.affine_->MoveZ(0);
  test.affine_->MoveZ(2.3);

  for (size_t i = 0; i < data.vertex.size(); i++) {
    for (size_t j = 0; j < data.vertex[i].size(); j++) {
      EXPECT_NEAR(data.vertex[i][j], resultVertex[i][j], 0.0000001);
    }
  }
}

TEST(Test, testRotate) {
  Data data;
  std::string filename = "tests/cube.obj";
  s21::Example test(data);
  std::vector<std::vector<double>> resultVertex = {
      {},
      {0.977163, 1.0241568, -0.998126},
      {1.00134, -0.975548, -1.02255866},
      {0.998402, 0.99998, 1.001615},
      {1.022578, -0.999724, 0.977182},
      {-1.022578, 0.999724, -0.977182},
      {-0.998402, -0.99998, -1.001615},
      {-1.00134, 0.975548, 1.022559},
      {-0.977163, -1.024157, 0.998126}};
  test.parser_->Counter(filename);
  test.parser_->ParseFile(filename);
  test.affine_->RotateX(0.5);
  test.affine_->RotateX(0.2);
  test.affine_->RotateY(0.3);
  test.affine_->RotateY(0.3);
  test.affine_->RotateZ(0.2);
  test.affine_->RotateZ(0.5);

  for (size_t i = 0; i < data.vertex.size(); i++) {
    for (size_t j = 0; j < data.vertex[i].size(); j++) {
      EXPECT_NEAR(data.vertex[i][j], resultVertex[i][j], 0.000001);
    }
  }
}

TEST(Test, testScale) {
  Data data;
  std::string filename = "tests/cube.obj";
  s21::Example test(data);
  std::vector<std::vector<double>> resultVertex = {{},
                                                   {1.25, 1.25, -1.25},
                                                   {1.25, -1.25, -1.25},
                                                   {1.25, 1.25, 1.25},
                                                   {1.25, -1.25, 1.25},
                                                   {-1.25, 1.25, -1.25},
                                                   {-1.25, -1.25, -1.25},
                                                   {-1.25, 1.25, 1.25},
                                                   {-1.25, -1.25, 1.25}};
  test.parser_->Counter(filename);
  test.parser_->ParseFile(filename);
  test.affine_->ScaleX(0.5);
  test.affine_->ScaleY(0.5);
  test.affine_->ScaleZ(0.5);
  test.affine_->ScaleX(-0.5);
  test.affine_->ScaleY(-0.5);
  test.affine_->ScaleZ(-0.5);
  test.affine_->ScaleX(2.5);
  test.affine_->ScaleY(2.5);
  test.affine_->ScaleZ(2.5);

  for (size_t i = 0; i < data.vertex.size(); i++) {
    for (size_t j = 0; j < data.vertex[i].size(); j++) {
      EXPECT_NEAR(data.vertex[i][j], resultVertex[i][j], 0.000001);
    }
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}