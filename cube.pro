QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    gameobject.cpp \
    cube.cpp \
    plane.cpp \
    terrain.cpp \
    quadtree.cpp \
    gamescene.cpp \
    model3d.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    gameobject.h \
    cube.h \
    plane.h \
    terrain.h \
    quadtree.h \
    gamescene.h \
    model3d.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=
