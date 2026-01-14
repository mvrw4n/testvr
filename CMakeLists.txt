cmake_minimum_required(VERSION 3.16)

project(TP5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets QUIET)
if(Qt6_FOUND)
    set(QT_LIBS Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)
else()
    find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::OpenGL)
endif()

find_package(OpenGL REQUIRED)

add_executable(TP5
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    vrbody.cpp
    vrbounce.cpp
    vrcamera.cpp
    vrcube.cpp
    vrcurve.cpp
    vrdice.cpp
    vrhelix.cpp
    vrlight.cpp
    vrplane.cpp
    vrplanet.cpp
    vrscene.cpp
    vrskybox.cpp
    vrspecularcube.cpp
    vrspecularsphere.cpp
    vrspeculartorus.cpp
    vrsphere.cpp
    vrsphericalcamera.cpp
    vrstereocamera.cpp
    vrsurface.cpp
    vrtexcube.cpp
    vrtorus.cpp
    vrwidget.cpp
    vrbody.h
    vrbounce.h
    vrcamera.h
    vrcube.h
    vrcurve.h
    vrdice.h
    vrhelix.h
    vrlight.h
    vrplane.h
    vrplanet.h
    vrscene.h
    vrskybox.h
    vrspecularcube.h
    vrspecularsphere.h
    vrspeculartorus.h
    vrsphere.h
    vrsphericalcamera.h
    vrstereocamera.h
    vrsurface.h
    vrtexcube.h
    vrtorus.h
    vrwidget.h
    RVResources.qrc
)

target_link_libraries(TP5 PRIVATE ${QT_LIBS} OpenGL::GL)
