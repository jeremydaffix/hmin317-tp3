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
    model3d.cpp \
    component.cpp \
    movingcubecomponent.cpp \
    gridmainwidget.cpp \
    calendar.cpp

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
    model3d.h \
    component.h \
    movingcubecomponent.h \
    gridmainwidget.h \
    calendar.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES += \
    Skull decimated.obj

CONFIG += resources_big

FORMS +=
