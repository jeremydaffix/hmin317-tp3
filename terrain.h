#ifndef TERRAIN_H
#define TERRAIN_H

#include <model3d.h>


class Terrain : public Model3D
{
public:
    Terrain(QString path, int vert = 16, QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL);
    ~Terrain();

    void createGeometry();
    void draw();

    int getNbrVertices() const;
    void setNbrVertices(int value);

protected:
    int nbrVertices;
    QImage *heightmap = NULL;

};

#endif // TERRAIN_H
