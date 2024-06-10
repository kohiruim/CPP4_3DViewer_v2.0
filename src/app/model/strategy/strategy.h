#ifndef STRATEGY_H
#define STRATEGY_H

#include "../affine/affine.h"

namespace s21 {

class Strategy {
 public:
  virtual ~Strategy() = default;
  virtual void ChangeVertex(double value, const Axis &axis) = 0;
};

class ScaleStrategy : public Strategy {  // Стратегии масштабирования по осям
 public:
  ScaleStrategy(Affine &affine);
  void ChangeVertex(double value, const Axis &axis);

 private:
  Affine &affine_;
};

class MoveStrategy : public Strategy {  // Стратегии перемещения по осям
 public:
  MoveStrategy(Affine &affine);
  void ChangeVertex(double value, const Axis &axis);

 private:
  Affine &affine_;
};

class RotateStrategy : public Strategy {  // Стратегии вращения по осям
 public:
  RotateStrategy(Affine &affine);
  void ChangeVertex(double value, const Axis &axis);

 private:
  Affine &affine_;
};
}  // namespace s21

#endif  // STRATEGY_H
