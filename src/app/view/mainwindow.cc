#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"

namespace s21 {
static const QString pathToApplicationLocation = QDir::homePath();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), timer_(new QTimer(0)), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  controller_ = std::make_unique<s21::Controller>(ui_->widget->get_data());
  settings_ = new QSettings("s21", "settings 3DViewer", this);
  loadSettings();

  connect(ui_->fileButton, SIGNAL(clicked()), this,
          SLOT(onFileButtonClicked()));

  connect(ui_->xPosition, SIGNAL(valueChanged(double)), this,
          SLOT(onXpositionValueChanged(double)));
  connect(ui_->yPosition, SIGNAL(valueChanged(double)), this,
          SLOT(onYpositionValueChanged(double)));
  connect(ui_->zPosition, SIGNAL(valueChanged(double)), this,
          SLOT(onZpositionValueChanged(double)));

  connect(ui_->xAngle, SIGNAL(valueChanged(double)), this,
          SLOT(onXangleValueChanged(double)));
  connect(ui_->yAngle, SIGNAL(valueChanged(double)), this,
          SLOT(onYangleValueChanged(double)));
  connect(ui_->zAngle, SIGNAL(valueChanged(double)), this,
          SLOT(onZangleValueChanged(double)));

  connect(ui_->xScale, SIGNAL(valueChanged(double)), this,
          SLOT(onXscaleValueChanged(double)));
  connect(ui_->yScale, SIGNAL(valueChanged(double)), this,
          SLOT(onYscaleValueChanged(double)));
  connect(ui_->zScale, SIGNAL(valueChanged(double)), this,
          SLOT(onZscaleValueChanged(double)));

  connect(ui_->parallelProjection, SIGNAL(toggled(bool)), this,
          SLOT(onParallelProjectionToggled()));
  connect(ui_->centralProjection, SIGNAL(toggled(bool)), this,
          SLOT(onCentralProjectionToggled()));

  connect(ui_->lineColorWhite, SIGNAL(toggled(bool)), this,
          SLOT(onLineColorWhiteToggled()));
  connect(ui_->lineColorBlack, SIGNAL(toggled(bool)), this,
          SLOT(onLineColorBlackToggled()));
  connect(ui_->lineColorRed, SIGNAL(toggled(bool)), this,
          SLOT(onLineColorRedToggled()));

  connect(ui_->lineSolid, SIGNAL(toggled(bool)), this,
          SLOT(onLineSolidToggled()));
  connect(ui_->lineStripple, SIGNAL(toggled(bool)), this,
          SLOT(onLineStrippleToggled()));

  connect(ui_->lineWidth, SIGNAL(valueChanged(double)), this,
          SLOT(onLineWidthValueChanged(double)));
  connect(ui_->vertexSize, SIGNAL(valueChanged(double)), this,
          SLOT(onVertexSizeValueChanged(double)));

  connect(ui_->pointColorBlack, SIGNAL(toggled(bool)), this,
          SLOT(onPointColorBlackToggled()));
  connect(ui_->pointColorWhite, SIGNAL(toggled(bool)), this,
          SLOT(onPointColorWhiteToggled()));
  connect(ui_->pointColorRed, SIGNAL(toggled(bool)), this,
          SLOT(onPointColorRedToggled()));

  connect(ui_->foneColorBlack, SIGNAL(toggled(bool)), this,
          SLOT(onFoneColorBlackToggled()));
  connect(ui_->foneColorGrey, SIGNAL(toggled(bool)), this,
          SLOT(onFoneColorGreyToggled()));
  connect(ui_->foneColorWhite, SIGNAL(toggled(bool)), this,
          SLOT(onFoneColorWhiteToggled()));

  connect(ui_->pointFormCircle, SIGNAL(toggled(bool)), this,
          SLOT(onPointFormCircleToggled()));
  connect(ui_->pointFormNot, SIGNAL(toggled(bool)), this,
          SLOT(onPointFormNotToggled()));
  connect(ui_->pointFormQuad, SIGNAL(toggled(bool)), this,
          SLOT(onPointFormQuadToggled()));

  connect(ui_->saveImg, SIGNAL(clicked()), this, SLOT(onSaveImgReleased()));
  connect(ui_->gif, SIGNAL(clicked()), this, SLOT(onGifReleased()));
}

MainWindow::~MainWindow() {
  saveSettings();
  if (gif_) {
    delete gif_;
  }
  delete timer_;
  delete ui_;
}

void MainWindow::onFileButtonClicked() {
  QString filename =
      QFileDialog::getOpenFileName(this, "Выберете файл", "", "");
  if (controller_->Parse(filename.toStdString()) != -1) {
    QString countPolygon =
        QString::number(ui_->widget->get_data().countPolygon);
    QString countVetrex = QString::number(ui_->widget->get_data().countVertex);
    ui_->label->setText(filename);
    ui_->widget->fileOpen = 1;
    ui_->widget->update();
    ui_->countVertex->setText("Кол-во вершин: " + countVetrex);
    ui_->countPolygon->setText("Кол-во граней: " + countPolygon);
  } else {
    ui_->label->setText("Файл не открывается");
  }
}

void MainWindow::onXpositionValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Move(arg1, Axis::x);
    ui_->widget->update();
  }
}

void MainWindow::onYpositionValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Move(arg1, Axis::y);
    ui_->widget->update();
  }
}

void MainWindow::onZpositionValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Move(arg1, Axis::z);
    ui_->widget->update();
  }
}

void MainWindow::onXangleValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Rotate(arg1, Axis::x);
    ui_->widget->update();
  }
}

void MainWindow::onYangleValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Rotate(arg1, Axis::y);
    ui_->widget->update();
  }
}

void MainWindow::onZangleValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Rotate(arg1, Axis::z);
    ui_->widget->update();
  }
}

void MainWindow::onXscaleValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Scale(arg1, Axis::x);
    ui_->widget->update();
  }
}

void MainWindow::onYscaleValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Scale(arg1, Axis::y);
    ui_->widget->update();
  }
}

void MainWindow::onZscaleValueChanged(double arg1) {
  if (ui_->widget->fileOpen > 0) {
    controller_->Scale(arg1, Axis::z);
    ui_->widget->update();
  }
}

void MainWindow::onParallelProjectionToggled() {
  if (ui_->parallelProjection->isChecked()) {
    ui_->widget->proectionclicked = false;
    ui_->widget->update();
  }
}

void MainWindow::onCentralProjectionToggled() {
  if (ui_->centralProjection->isChecked()) {
    ui_->widget->proectionclicked = true;
    ui_->widget->update();
  }
}

void MainWindow::onLineColorWhiteToggled() {
  if (ui_->lineColorWhite->isChecked()) {
    ui_->widget->lineColor = Qt::white;
    ui_->widget->update();
  }
}

void MainWindow::onLineColorBlackToggled() {
  if (ui_->lineColorBlack->isChecked()) {
    ui_->widget->lineColor = Qt::black;
    ui_->widget->update();
  }
}

void MainWindow::onLineColorRedToggled() {
  if (ui_->lineColorRed->isChecked()) {
    ui_->widget->lineColor = Qt::red;
    ui_->widget->update();
  }
}

void MainWindow::onLineStrippleToggled() {
  if (ui_->lineStripple->isChecked()) {
    ui_->widget->lineStripple = true;
    ui_->widget->update();
  }
}

void MainWindow::onLineSolidToggled() {
  if (ui_->lineSolid->isChecked()) {
    ui_->widget->lineStripple = false;
    ui_->widget->update();
  }
}

void MainWindow::onLineWidthValueChanged(double arg1) {
  ui_->widget->lineWidth = arg1;
  ui_->widget->update();
}

void MainWindow::onVertexSizeValueChanged(double arg1) {
  ui_->widget->vertexSize = arg1;
  ui_->widget->update();
}

void MainWindow::onPointColorWhiteToggled() {
  if (ui_->pointColorWhite->isChecked()) {
    ui_->widget->pointColor = Qt::white;
    ui_->widget->update();
  }
}

void MainWindow::onPointColorBlackToggled() {
  if (ui_->pointColorBlack->isChecked()) {
    ui_->widget->pointColor = Qt::black;
    ui_->widget->update();
  }
}

void MainWindow::onPointColorRedToggled() {
  if (ui_->pointColorRed->isChecked()) {
    ui_->widget->pointColor = Qt::red;
    ui_->widget->update();
  }
}

void MainWindow::onFoneColorGreyToggled() {
  if (ui_->foneColorGrey->isChecked()) {
    ui_->widget->foneColor = Qt::darkGray;
    ui_->widget->update();
  }
}

void MainWindow::onFoneColorBlackToggled() {
  if (ui_->foneColorBlack->isChecked()) {
    ui_->widget->foneColor = Qt::black;
    ui_->widget->update();
  }
}

void MainWindow::onFoneColorWhiteToggled() {
  if (ui_->foneColorWhite->isChecked()) {
    ui_->widget->foneColor = Qt::white;
    ui_->widget->update();
  }
}

void MainWindow::onPointFormNotToggled() {
  if (ui_->pointFormNot->isChecked()) {
    ui_->widget->dotNot = true;
    ui_->widget->dotQuad = false;
    ui_->widget->dotCircle = false;
    ui_->widget->update();
  }
}

void MainWindow::onPointFormCircleToggled() {
  if (ui_->pointFormCircle->isChecked()) {
    ui_->widget->dotNot = false;
    ui_->widget->dotQuad = false;
    ui_->widget->dotCircle = true;
    ui_->widget->update();
  }
}

void MainWindow::onPointFormQuadToggled() {
  if (ui_->pointFormQuad->isChecked()) {
    ui_->widget->dotNot = false;
    ui_->widget->dotQuad = true;
    ui_->widget->dotCircle = false;
    ui_->widget->update();
  }
}

void MainWindow::saveSettings() {
  settings_->setValue("ortho", ui_->centralProjection->isChecked());
  settings_->setValue("central", ui_->parallelProjection->isChecked());
  // цвет линий сохранить
  settings_->setValue("lineColorWhite", ui_->lineColorWhite->isChecked());
  settings_->setValue("lineColorBlack", ui_->lineColorBlack->isChecked());
  settings_->setValue("lineColorRed", ui_->lineColorRed->isChecked());
  // тип линии
  settings_->setValue("lineStripple", ui_->lineStripple->isChecked());
  settings_->setValue("lineSolid", ui_->lineSolid->isChecked());
  // толщина линий
  settings_->setValue("lineWidth", ui_->lineWidth->value());
  // толщина точки
  settings_->setValue("vertexSize", ui_->vertexSize->value());
  // цвет точки сохранить
  settings_->setValue("pointColorWhite", ui_->pointColorWhite->isChecked());
  settings_->setValue("pointColorBlack", ui_->pointColorBlack->isChecked());
  settings_->setValue("pointColorRed", ui_->pointColorRed->isChecked());
  // цвет фона сохранить
  settings_->setValue("foneColorWhite", ui_->foneColorWhite->isChecked());
  settings_->setValue("foneColorBlack", ui_->foneColorBlack->isChecked());
  settings_->setValue("foneColorGrey", ui_->foneColorGrey->isChecked());
  // тип точек сохранить
  settings_->setValue("pointFormNot", ui_->pointFormNot->isChecked());
  settings_->setValue("pointFormCircle", ui_->pointFormCircle->isChecked());
  settings_->setValue("pointFormQuad", ui_->pointFormQuad->isChecked());
}

void MainWindow::loadSettings() {
  // тип проекции
  ui_->centralProjection->setChecked(
      settings_->value("ortho", "false").toBool());
  ui_->parallelProjection->setChecked(
      settings_->value("central", "false").toBool());
  // цвет линий загрузить
  ui_->lineColorWhite->setChecked(
      settings_->value("lineColorWhite", "false").toBool());
  ui_->lineColorBlack->setChecked(
      settings_->value("lineColorBlack", "false").toBool());
  ui_->lineColorRed->setChecked(
      settings_->value("lineColorRed", "false").toBool());
  // тип линии
  ui_->lineStripple->setChecked(
      settings_->value("lineStripple", "false").toBool());
  ui_->lineSolid->setChecked(settings_->value("lineSolid", "false").toBool());
  // толщина линий
  ui_->lineWidth->setValue(settings_->value("lineWidth", "0").toDouble());
  // толщина точки
  ui_->vertexSize->setValue(settings_->value("vertexSize", "0").toDouble());
  // цвет точек загрузить
  ui_->pointColorWhite->setChecked(
      settings_->value("pointColorWhite", "false").toBool());
  ui_->pointColorBlack->setChecked(
      settings_->value("pointColorBlack", "false").toBool());
  ui_->pointColorRed->setChecked(
      settings_->value("pointColorRed", "false").toBool());
  // цвет фона загрузить
  ui_->foneColorWhite->setChecked(
      settings_->value("foneColorWhite", "false").toBool());
  ui_->foneColorBlack->setChecked(
      settings_->value("foneColorBlack", "false").toBool());
  ui_->foneColorGrey->setChecked(
      settings_->value("foneColorGrey", "false").toBool());
  // тип точек загрузить
  ui_->pointFormNot->setChecked(
      settings_->value("pointFormNot", "false").toBool());
  ui_->pointFormCircle->setChecked(
      settings_->value("pointFormCircle", "false").toBool());
  ui_->pointFormQuad->setChecked(
      settings_->value("pointFormQuad", "false").toBool());
  loadSettingsOpenGL();
}

void MainWindow::loadSettingsOpenGL() {
  ui_->widget->proectionclicked = settings_->value("ortho", "false").toBool();
  ui_->widget->lineStripple =
      settings_->value("lineStripple", "false").toBool();
  ui_->widget->lineWidth = settings_->value("lineWidth", "0").toDouble();
  ui_->widget->vertexSize = settings_->value("vertexSize", "0").toDouble();
  ui_->widget->dotQuad = settings_->value("pointFormQuad", "false").toBool();
  ui_->widget->dotCircle =
      settings_->value("pointFormCircle", "false").toBool();
  ui_->widget->dotNot = settings_->value("pointFormNot", "false").toBool();
  if (settings_->value("lineColorBlack", "false").toBool())
    ui_->widget->lineColor = Qt::black;
  if (settings_->value("lineColorRed", "false").toBool())
    ui_->widget->lineColor = Qt::red;
  if (settings_->value("pointColorWhite", "false").toBool())
    ui_->widget->pointColor = Qt::white;
  if (settings_->value("pointColorBlack", "false").toBool())
    ui_->widget->pointColor = Qt::black;
  if (settings_->value("foneColorWhite", "false").toBool())
    ui_->widget->foneColor = Qt::white;
  if (settings_->value("foneColorGrey", "false").toBool())
    ui_->widget->foneColor = Qt::darkGray;
}

void MainWindow::onSaveImgReleased() {
  QString file = QFileDialog::getSaveFileName(this, "Save as...", "name.bmp",
                                              "BMP (*.bmp);; JPEG (*.jpeg)");
  ui_->widget->grabFramebuffer().save(file, NULL, 100);
}

auto MainWindow::onGifReleased() -> void {
  if (gif_) {
    delete gif_;
  }
  gif_ = new QGifImage;
  gif_->setDefaultDelay(100);
  frame_counter_ = 0;
  connect(timer_, &QTimer::timeout, this, &MainWindow::SaveFrame);
  timer_->start(100);
}

void MainWindow::SaveFrame() {
  if (frame_counter_ < 50) {
    QImage frame = ui_->widget->grabFramebuffer().scaled(
        640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    gif_->addFrame(frame);
    ++frame_counter_;
  } else {
    timer_->stop();
    disconnect(timer_, &QTimer::timeout, this, &MainWindow::SaveFrame);
    SaveGif();
  }
}

auto MainWindow::SaveGif() -> void {
  QString save_path = QFileDialog::getSaveFileName(
      this, NULL, pathToApplicationLocation, "GIF (*.gif)", 0,
      QFileDialog::DontUseNativeDialog);
  if (!save_path.isEmpty()) {
    gif_->save(save_path);
  }
}
}  // namespace s21
