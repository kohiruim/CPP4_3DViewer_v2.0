#include "opengl.h"
//#include <gl/glu.h>
#include "mainwindow.h"

openGL::openGL(QWidget* parent) : QOpenGLWidget(parent) {}

void openGL::initializeGL() { glEnable(GL_DEPTH_TEST); }

Data& openGL::get_data() { return data_; }

void openGL::paintGL() {
  if (fileOpen > 0) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int winHeight = 3;
    float fov = 60.0 * M_PI / 180;
    float heapHeight = winHeight / (2 * tan(fov / 2));
    if (proectionclicked) {
      glFrustum(-winHeight, winHeight, -winHeight, winHeight, heapHeight, 100);
      glTranslatef(0, 0, -3 * heapHeight);
    } else {
      glOrtho(-winHeight, winHeight, -winHeight, winHeight, -winHeight,
              winHeight);
    }

    glClearColor(foneColor.redF(), foneColor.greenF(), foneColor.blueF(),
                 foneColor.alphaF());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (dotCircle) {
      glEnable(GL_POINT_SMOOTH);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glPointSize(vertexSize);
    glLineWidth(lineWidth);

    if (lineStripple) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00ff);
    }

    glTranslatef(xPos, yPos, zPos);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(zRot, 0, 0, 1);

    glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());

    for (std::size_t j = 0; j < data_.polygon.size(); j++) {
      glBegin(GL_LINE_LOOP);
      for (std::size_t i = 0; i < data_.polygon[j].size(); i++) {
        int g = data_.polygon[j][i];
        glVertex3d(data_.vertex[g][0], data_.vertex[g][1], data_.vertex[g][2]);
      }
      glEnd();
    }

    glColor3f(pointColor.redF(), pointColor.greenF(), pointColor.blueF());

    if (!dotNot) {
      glBegin(GL_POINTS);
      for (std::size_t i = 1; i < data_.vertex.size(); i++) {
        glVertex3d(data_.vertex[i][0], data_.vertex[i][1], data_.vertex[i][2]);
      }
      glEnd();
    }

    if (dotCircle) {
      glDisable(GL_POINT_SMOOTH);
      glDisable(GL_BLEND);
    }
    if (lineStripple) {
      glDisable(GL_LINE_STIPPLE);
    }
  }
}

void openGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
void openGL::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }
void openGL::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
