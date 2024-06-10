#ifndef AFFINE_H
#define AFFINE_H
#include <cmath>

#include "../data.h"

namespace s21 {
class Affine {
 public:
  Affine(Data &data);
  ~Affine() = default;
  void ScaleX(double indexScale);
  void ScaleY(double indexScale);
  void ScaleZ(double indexScale);
  void RotateX(double angle);
  void RotateY(double angle);
  void RotateZ(double angle);
  void MoveX(double s);
  void MoveY(double s);
  void MoveZ(double s);

 private:
  Data &data_;
};
}  // namespace s21

#endif  // AFFINE_H
