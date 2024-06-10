QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets
CONFIG += c++ 17

include(../QtGifImage-master/src/gifimage/qtgifimage.pri)

#You can make your code fail to compile if it uses deprecated APIs.
#In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE =0x060000 #disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    model/affine/affine.cc \
    model/facade/facade.cc \
    model/parser/parser.cc \
    model/strategy/strategy.cc \
    view/main.cc \
    view/mainwindow.cc \
    view/opengl.cc

HEADERS += \
    controller/controller.h \
    model/affine/affine.h \
    model/data.h \
    model/facade/facade.h \
    model/parser/parser.h \
    model/strategy/strategy.h \
    view/mainwindow.h \
    view/opengl.h

FORMS += view/mainwindow.ui

#LIBS += -framework GLUT
LIBS += -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx:ICON = $${PWD}/4.icns
