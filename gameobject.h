#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <iostream>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QImage>


class GameObject
{
public:
    GameObject(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D());
    virtual ~GameObject();


    QVector3D getLocalPosition() const;
    void setLocalPosition(const QVector3D &value);

    // a calculer en fonction hiérarchie
    QVector3D getPosition() const;
    void setPosition(const QVector3D &value);

    QQuaternion getLocalRotation() const;
    void setLocalRotation(const QQuaternion &value);

    // a calculer en fonction hiérarchie
    QQuaternion getRotation() const;
    void setRotation(const QQuaternion &value);

    QVector3D getLocalScale() const;
    void setLocalScale(const QVector3D &value);

    QVector3D getScale() const;
    void setScale(const QVector3D &value);


    GameObject *getParent() const;
    void setParent(GameObject *value);




    std::list<GameObject *> getChildren() const;
    void addChild(GameObject* child);
    void removeChild(GameObject* child);


    virtual void CreateGeometry();
    virtual void Draw();



protected:
    QVector3D localPosition;
    QQuaternion localRotation;
    QVector3D localScale;

    GameObject* parent = NULL;
    std::list<GameObject*> children; // pattern composite :o
};



struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};


#endif // GAMEOBJECT_H
