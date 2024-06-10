#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/facade/facade.h"

namespace s21 {
class Controller {
 public:
  Controller(Data &data);
  ~Controller() = default;
  int Parse(const std::string &filename);
  void Scale(double value, const Axis &axis);
  void Move(double value, const Axis &axis);
  void Rotate(double value, const Axis &axis);

 private:
  Facade &facade_;
};
}  // namespace s21
#endif  // CONTROLLER_H_
