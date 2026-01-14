QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rvbody.cpp \
    rvbounce.cpp \
    rvcamera.cpp \
    rvcube.cpp \
    rvcurve.cpp \
    rvdice.cpp \
    rvhelix.cpp \
    rvlight.cpp \
    rvplane.cpp \
    rvplanet.cpp \
    rvscene.cpp \
    rvskybox.cpp \
    rvspecularcube.cpp \
    rvspecularsphere.cpp \
    rvspeculartorus.cpp \
    rvsphere.cpp \
    rvsphericalcamera.cpp \
    rvstereocamera.cpp \
    rvsurface.cpp \
    rvtexcube.cpp \
    rvtorus.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h \
    rvbody.h \
    rvbounce.h \
    rvcamera.h \
    rvcube.h \
    rvcurve.h \
    rvdice.h \
    rvhelix.h \
    rvlight.h \
    rvplane.h \
    rvplanet.h \
    rvscene.h \
    rvskybox.h \
    rvspecularcube.h \
    rvspecularsphere.h \
    rvspeculartorus.h \
    rvsphere.h \
    rvsphericalcamera.h \
    rvstereocamera.h \
    rvsurface.h \
    rvtexcube.h \
    rvtorus.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Instruction de compilation complémentaire pour Windows
windows:LIBS += -lopengl32

DISTFILES += \
    FS_simple.fsh \
    VS_cube_texture.vsh \
    VS_simple.vsh

RESOURCES += \
    RVResources.qrc

FORMS += \
    mainwindow.ui
