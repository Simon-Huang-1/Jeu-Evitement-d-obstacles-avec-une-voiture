#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T15:06:48
#
#-------------------------------------------------

QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = TestWebCamQt
TEMPLATE = app


# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}

SOURCES += main.cpp\
        Car.cpp \
        DataTypes.cpp \
        Ground.cpp \
        entity.cpp \
        myglwidget.cpp

HEADERS  += \
    Car.h \
    DataTypes.h \
    Ground.h \
    entity.h \
    myglwidget.h

FORMS    += \
    widget.ui

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
        -lopencv_core451 \
        -lopencv_highgui451 \
        -lopencv_imgproc451 \
        -lopencv_imgcodecs451 \
        -lopencv_videoio451 \
        -lopencv_features2d451 \
        -lopencv_calib3d451 \
        -lopencv_objdetect451

RESOURCES += \
    textures.qrc
