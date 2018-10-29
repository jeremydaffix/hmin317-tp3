#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <gameobject.h>


class GameScene : public GameObject
{
public:
    static GameScene* getInstance();

    void CreateGeometry();
    void Draw();

    QOpenGLShaderProgram *getDefaultShader();
    void setDefaultShader(QOpenGLShaderProgram *value);

private:
    GameScene(); // SINGLETON


protected:

    QOpenGLShaderProgram* defaultShader;
    static GameScene* instance;

};

#endif // GAMESCENE_H
