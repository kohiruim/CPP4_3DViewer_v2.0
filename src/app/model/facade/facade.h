#ifndef FACADE_H
#define FACADE_H
#include <memory>

#include "../parser/parser.h"
#include "../strategy/strategy.h"

namespace s21 {
class Facade {
 public:
  Facade(Data &data);
  ~Facade() { delete instance_; };
  Facade(const Facade &other) = delete;
  Facade &operator=(const Facade &other) = delete;
  static Facade &GetInstance(Data &data);
  int Parse(const std::string &filename);
  void Move(double value, const Axis &axis);
  void Rotate(double value, const Axis &axis);
  void Scale(double value, const Axis &axis);

 private:
  std::unique_ptr<Affine> affine_;
  std::unique_ptr<Parser> parser_;
  std::unique_ptr<Strategy> move_;
  std::unique_ptr<Strategy> rotate_;
  std::unique_ptr<Strategy> scale_;
  static Facade *instance_;
};
}  // namespace s21

#endif  // FACADE_H
