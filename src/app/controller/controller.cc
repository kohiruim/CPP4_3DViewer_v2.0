#include "controller.h"

namespace s21 {
Controller::Controller(Data &data) : facade_(Facade::GetInstance(data)) {}

int Controller::Parse(const std::string &filename) {
  int error = facade_.Parse(filename);
  return error;
}

void Controller::Scale(double value, const Axis &axis) {
  facade_.Scale(value, axis);
}

void Controller::Move(double value, const Axis &axis) {
  facade_.Move(value, axis);
}

void Controller::Rotate(double value, const Axis &axis) {
  facade_.Rotate(value, axis);
}
}  // namespace s21
