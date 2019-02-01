QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewerPBS
TEMPLATE = app

CONFIG += c++14
CONFIG(release, release|debug):QMAKE_CXXFLAGS += -Wall -O2

CONFIG(release, release|debug):DESTDIR = release/
CONFIG(release, release|debug):OBJECTS_DIR = release/
CONFIG(release, release|debug):MOC_DIR = release/
CONFIG(release, release|debug):UI_DIR = release/

CONFIG(debug, release|debug):DESTDIR = debug/
CONFIG(debug, release|debug):OBJECTS_DIR = debug/
CONFIG(debug, release|debug):MOC_DIR = debug/
CONFIG(debug, release|debug):UI_DIR = debug/

INCLUDEPATH += Eigen GL glm

#LIBS += -lGLEW

win32-msvc2015{
        RC_FILE        += CS472.rc
        LIBS           += -lopengl32
        QMAKE_CXXFLAGS += /MP /Zi
        QMAKE_LFLAGS   += /MACHINE:X64
}

macx{
        QMAKE_SONAME_PREFIX = @executable_path/../Frameworks
        QMAKE_LFLAGS += -Wl,-rpath,@executable_path/../Frameworks
        QMAKE_LFLAGS   -= -mmacosx-version-min=10.8
        QMAKE_LFLAGS   += -mmacosx-version-min=10.9
        QMAKE_CXXFLAGS -= -mmacosx-version-min=10.8
        QMAKE_CXXFLAGS += -mmacosx-version-min=10.9
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
        ICON = CS472.icns
}

unix:!macx{
        CONFIG += C++11
}

mingw{
        LIBS += -lopengl32
}


SOURCES += \
    triangle_mesh.cc \
    mesh_io.cc \
    main.cc \
    main_window.cc \
    glwidget.cc \
    camera.cc \
    render.cpp

HEADERS  += \
    triangle_mesh.h \
    mesh_io.h \
    main_window.h \
    glwidget.h \
    camera.h \
    render.h

FORMS    += \
    main_window.ui

OTHER_FILES +=

DISTFILES += \
    shaders/reflection.frag \
    shaders/reflection.vert \
    shaders/brdf.frag \
    shaders/brdf.vert \
    shaders/prefilter.frag \
    shaders/prefilter.vert \
    shaders/brdf_lut.frag \
    shaders/brdf_lut.vert \
    shaders/sky.frag \
    shaders/sky.vert


