#ifndef OPENGL_H
#define OPENGL_H
#include <GL/gl.h>
#include <GL/glu.h>

#include <QColor>
#include <QMouseEvent>
#include <QOpenGLWidget>

#include "../model/data.h"

class openGL : public QOpenGLWidget {
 public:
  Data& get_data();
  openGL(QWidget* parent = nullptr);
  int fileOpen = 0;
  float vertexSize = 5, lineWidth = 1;
  bool proectionclicked = false, lineStripple = false;
  QColor lineColor = Qt::white;
  QColor pointColor = Qt::red;
  QColor foneColor = Qt::black;
  bool dotNot = false, dotQuad = false, dotCircle = true;

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  Data data_;
  float xPos = 0, yPos = 0, zPos = 0;
  float xRot = 0, yRot = 0, zRot = 0;
  QPoint mPos;
  void mousePressEvent(QMouseEvent* mo) override;
  void mouseMoveEvent(QMouseEvent* mo) override;
};

#endif  // OPENGL_H
