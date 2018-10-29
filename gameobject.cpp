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

void GameObject::CreateGeometry()
{
    std::cout << "CREATE GAMEOBJECT\n";
}

void GameObject::Draw()
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

}

void GameObject::setScale(const QVector3D &value)
{

}

QVector3D GameObject::getLocalPosition() const
{
    return localPosition;
}

void GameObject::setLocalPosition(const QVector3D &value)
{
    localPosition = value;
}

QVector3D GameObject::getPosition() const
{

}

void GameObject::setPosition(const QVector3D &value)
{

}

QQuaternion GameObject::getLocalRotation() const
{
    return localRotation;
}

void GameObject::setLocalRotation(const QQuaternion &value)
{
    localRotation = value;
}

QQuaternion GameObject::getRotation() const
{

}

void GameObject::setRotation(const QQuaternion &value)
{

}


