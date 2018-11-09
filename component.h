#ifndef COMPONENT_H
#define COMPONENT_H

//#include<gameobject.h>
#include <iostream>

class GameObject;

class Component
{
public:
    Component();

    virtual void update() = 0;
    virtual void fixedUpdate() = 0;


    GameObject *getContainer() const;
    void setContainer(GameObject *value);

protected:

    GameObject* container = NULL;
};

#endif // COMPONENT_H
