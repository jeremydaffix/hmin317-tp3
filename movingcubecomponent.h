#ifndef MOVINGCUBECOMPONENT_H
#define MOVINGCUBECOMPONENT_H

#include <gameobject.h>


class MovingCubeComponent : public Component
{
public:
    MovingCubeComponent();

    void update();
    void fixedUpdate();
};

#endif // MOVINGCUBECOMPONENT_H
