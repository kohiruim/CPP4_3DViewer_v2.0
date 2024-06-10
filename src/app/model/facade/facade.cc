#include "facade.h"

namespace s21 {
Facade *Facade::instance_ = nullptr;

Facade::Facade(Data &data)
    : affine_(std::make_unique<Affine>(data)),
      parser_(std::make_unique<Parser>(data)),
      move_(std::make_unique<MoveStrategy>(*affine_)),
      rotate_(std::make_unique<RotateStrategy>(*affine_)),
      scale_(std::make_unique<ScaleStrategy>(*affine_)) {}

Facade &Facade::GetInstance(Data &data) {
  if (instance_ == nullptr) instance_ = new Facade(data);
  return *instance_;
}

int Facade::Parse(const std::string &filename) {
  int error = parser_->Counter(filename);
  parser_->ParseFile(filename);
  return error;
}

void Facade::Move(double value, const Axis &axis) {
  move_->ChangeVertex(value, axis);
}

void Facade::Rotate(double value, const Axis &axis) {
  rotate_->ChangeVertex(value, axis);
}

void Facade::Scale(double value, const Axis &axis) {
  scale_->ChangeVertex(value, axis);
}

}  // namespace s21
