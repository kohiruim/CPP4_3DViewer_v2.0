#include "affine.h"

namespace s21 {

Affine::Affine(Data &data) : data_(data) {}

void Affine::ScaleX(double indexScale) {
  if (indexScale > 0) {
    for (std::size_t i = 1; i < data_.vertex.size(); i++) {
      data_.vertex[i][0] *= indexScale;
    }
  }
}

void Affine::ScaleY(double indexScale) {
  if (indexScale > 0) {
    for (std::size_t i = 1; i < data_.vertex.size(); i++) {
      data_.vertex[i][1] *= indexScale;
    }
  }
}

void Affine::ScaleZ(double indexScale) {
  if (indexScale > 0) {
    for (std::size_t i = 1; i < data_.vertex.size(); i++) {
      data_.vertex[i][2] *= indexScale;
    }
  }
}

void Affine::RotateX(double angle) {
  double y, z;
  double cosValue = std::cos(angle * M_PI / 180);
  double sinValue = std::sin(angle * M_PI / 180);
  for (std::size_t i = 1; i < data_.vertex.size(); ++i) {
    y = data_.vertex[i][1];
    z = data_.vertex[i][2];
    data_.vertex[i][2] = sinValue * y + cosValue * z;
    data_.vertex[i][1] = cosValue * y - sinValue * z;
  }
}

void Affine::RotateY(double angle) {
  double x, z;
  double cosValue = std::cos(angle * M_PI / 180);
  double sinValue = std::sin(angle * M_PI / 180);
  for (std::size_t i = 1; i < data_.vertex.size(); ++i) {
    x = data_.vertex[i][0];
    z = data_.vertex[i][2];
    data_.vertex[i][2] = -sinValue * x + cosValue * z;
    data_.vertex[i][0] = cosValue * x + sinValue * z;
  }
}

void Affine::RotateZ(double angle) {
  double y, z;
  double cosValue = std::cos(angle * M_PI / 180);
  double sinValue = std::sin(angle * M_PI / 180);
  for (std::size_t i = 1; i < data_.vertex.size(); ++i) {
    y = data_.vertex[i][0];
    z = data_.vertex[i][1];
    data_.vertex[i][1] = sinValue * y + cosValue * z;
    data_.vertex[i][0] = cosValue * y - sinValue * z;
  }
}

void Affine::MoveX(double s) {
  for (std::size_t i = 1; i < data_.vertex.size(); ++i) {
    data_.vertex[i][0] += s;
  }
}

void Affine::MoveY(double s) {
  for (std::size_t i = 1; i < data_.vertex.size(); ++i) {
    data_.vertex[i][1] += s;
  }
}

void Affine::MoveZ(double s) {
  for (std::size_t i = 1; i < data_.vertex.size(); ++i) {
    data_.vertex[i][2] += s;
  }
}
}  // namespace s21
