#ifndef CUBE_H
#define CUBE_H

#include <model3d.h>


class Cube : public Model3D
{
public:
    Cube(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(), QOpenGLShaderProgram* sh = NULL);

    void CreateGeometry();
    void Draw();
};

#endif // CUBE_H
