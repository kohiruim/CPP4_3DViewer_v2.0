#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <GL/gl.h>
#include <GL/glu.h>

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "../controller/controller.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QGifImage *gif_ = nullptr;
  QTimer *timer_ = nullptr;
  unsigned int frame_counter_ = 0;

 public slots:
  auto SaveFrame() -> void;
  auto SaveGif() -> void;
  auto onGifReleased() -> void;

 private slots:
  void onFileButtonClicked();
  void onXpositionValueChanged(double arg1);
  void onYpositionValueChanged(double arg1);
  void onZpositionValueChanged(double arg1);
  void onXangleValueChanged(double arg1);
  void onYangleValueChanged(double arg1);
  void onZangleValueChanged(double arg1);
  void onXscaleValueChanged(double arg1);
  void onYscaleValueChanged(double arg1);
  void onZscaleValueChanged(double arg1);
  void onParallelProjectionToggled();
  void onCentralProjectionToggled();
  void onLineColorWhiteToggled();
  void onLineColorBlackToggled();
  void onLineColorRedToggled();
  void onLineStrippleToggled();
  void onLineSolidToggled();
  void onLineWidthValueChanged(double arg1);
  void onVertexSizeValueChanged(double arg1);
  void onPointColorWhiteToggled();
  void onPointColorBlackToggled();
  void onPointColorRedToggled();
  void onFoneColorGreyToggled();
  void onFoneColorBlackToggled();
  void onFoneColorWhiteToggled();

  void saveSettings();
  void loadSettings();
  void loadSettingsOpenGL();

  void onPointFormNotToggled();
  void onPointFormCircleToggled();
  void onPointFormQuadToggled();
  void onSaveImgReleased();

 private:
  Ui::MainWindow *ui_;
  QSettings *settings_;
  std::unique_ptr<s21::Controller> controller_;
};
}  // namespace s21
#endif  // MAINWINDOW_H
