#ifndef OBJET3D_H
#define OBJET3D_H

#include <model3d.h>
#include <string>
using namespace std;

//la classe qui charge les objets 3d

class Objet3d : public Model3D
{
public:

    Objet3d(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL);

    // les 2 méthodes à redéfinir et spécifiques à la création / affichage des sommets de l'objet !
    void createGeometry();
    void draw();
    string path;
};


#endif // OBJET3D_H
