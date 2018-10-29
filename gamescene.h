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

    QMatrix4x4 getProjection() const;
    void setProjection(const QMatrix4x4 &value);

private:
    GameScene(); // SINGLETON


protected:

    QOpenGLShaderProgram* defaultShader;
    static GameScene* instance;

    QMatrix4x4 projection;

};

#endif // GAMESCENE_H
