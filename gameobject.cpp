#include "gameobject.h"

GameObject::GameObject(QVector3D pos, QQuaternion rot, QVector3D sc)
{
    localPosition = pos;
    localRotation = rot;
    localScale = sc;
}

GameObject::~GameObject()
{

}


GameObject *GameObject::getParent() const
{
    return parent;
}

void GameObject::setParent(GameObject *value)
{
    parent = value;
}



std::list<GameObject *> GameObject::getChildren() const
{
    return children;
}

void GameObject::addChild(GameObject *child)
{
    if(child->getParent() != NULL) {

        child->getParent()->removeChild(child);
    }

    children.push_back(child);
    child->setParent(this);
}

void GameObject::removeChild(GameObject *child)
{
    children.remove(child);
    child->setParent(NULL);
}

void GameObject::createGeometry()
{
    std::cout << "CREATE GAMEOBJECT\n";
}

void GameObject::draw()
{
    std::cout << "DRAW GAMEOBJECT\n";
}

QVector3D GameObject::getLocalScale() const
{
    return localScale;
}

void GameObject::setLocalScale(const QVector3D &value)
{
    localScale = value;
}

QVector3D GameObject::getScale() const
{
    // scale repère world = multiplication des scales de la hiérarchie

    QVector3D worldScale = getLocalScale();

    GameObject *go = parent;

    while(go != NULL) {

        worldScale *= go->getLocalScale();

        go = go->getParent();
    }

    return worldScale;
}

/*void GameObject::setScale(const QVector3D &value)
{

}*/


QMatrix4x4 GameObject::getLocalTransform() const
{
    QMatrix4x4 transf;

    transf.translate(getLocalPosition());
    transf.rotate(getLocalRotation());
    transf.scale(getLocalScale());

    return transf;
}


QMatrix4x4 GameObject::getTransform() const
{
    QMatrix4x4 transf = getLocalTransform();

    GameObject *go = parent;

    while(go != NULL) {

        transf = go->getLocalTransform() * transf;

        go = go->getParent();
    }

    return transf;
}

QVector3D GameObject::getLocalPosition() const
{
    return localPosition;
}

void GameObject::setLocalPosition(const QVector3D &value)
{
    localPosition = value;
}

/*QVector3D GameObject::getPosition() const
{
    // position repère world = addition des positions de la hiérarchie

    QVector3D worldPos = getLocalPosition();

    GameObject *go = parent;

    while(go != NULL) {

        worldPos += go->getLocalPosition(); // FAUX si rotation

        go = go->getParent();
    }

    return worldPos;
}*/

/*void GameObject::setPosition(const QVector3D &value)
{

}*/

QQuaternion GameObject::getLocalRotation() const
{
    return localRotation;
}

void GameObject::setLocalRotation(const QQuaternion &value)
{
    localRotation = value;
}

/*QQuaternion GameObject::getRotation() const
{
    // rotation repère world = multiplication des rotations de la hiérarchie

    QQuaternion worldRot = getLocalRotation();

    GameObject *go = parent;

    while(go != NULL) {

        worldRot = go->getLocalRotation() * worldRot; // à vérifier !!!

        go = go->getParent();
    }

    return worldRot;
}*/

/*void GameObject::setRotation(const QQuaternion &value)
{

}*/


