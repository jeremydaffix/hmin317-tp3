#ifndef PLANE_H
#define PLANE_H

#include <model3d.h>


class Plane : public Model3D
{
public:
    Plane(int vert = 16, QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL);

    void createGeometry();
    void draw();

    int getNbrVertices() const;
    void setNbrVertices(int value);

protected:
    int nbrVertices;
};

#endif // PLANE_H
