#include "strategy.h"

namespace s21 {

ScaleStrategy::ScaleStrategy(Affine &affine)
    : affine_(affine) {}  // масштабирование
void ScaleStrategy::ChangeVertex(double value, const Axis &axis) {
  if (axis == Axis::x) affine_.ScaleX(value);
  if (axis == Axis::y) affine_.ScaleY(value);
  if (axis == Axis::z) affine_.ScaleZ(value);
}

MoveStrategy::MoveStrategy(Affine &affine) : affine_(affine) {}  // движение
void MoveStrategy::ChangeVertex(double value, const Axis &axis) {
  if (axis == Axis::x) affine_.MoveX(value);
  if (axis == Axis::y) affine_.MoveY(value);
  if (axis == Axis::z) affine_.MoveZ(value);
}

RotateStrategy::RotateStrategy(Affine &affine) : affine_(affine) {}  // вращение
void RotateStrategy::ChangeVertex(double value, const Axis &axis) {
  if (axis == Axis::x) affine_.RotateX(value);
  if (axis == Axis::y) affine_.RotateY(value);
  if (axis == Axis::z) affine_.RotateZ(value);
}
}  // namespace s21
