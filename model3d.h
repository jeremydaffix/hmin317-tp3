#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include <gamescene.h>
//#include <gameobject.h>

//class GameScene;


class Model3D : public GameObject, protected QOpenGLFunctions
{
public:

    Model3D(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL);
    virtual ~Model3D();


    //virtual void CreateGeometry();
    //virtual void Draw();


    QOpenGLShaderProgram *getShader() const;
    void setShader(QOpenGLShaderProgram *value);

protected:

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLShaderProgram *shader = NULL;

};

#endif // DISPLAYABLEOBJECT_H
