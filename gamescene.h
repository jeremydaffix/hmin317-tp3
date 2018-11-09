#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <gameobject.h>


class GameScene : public GameObject
{
public:
    static GameScene* getInstance();

    void createGeometry();
    void draw();

    QOpenGLShaderProgram *getDefaultShader();
    void setDefaultShader(QOpenGLShaderProgram *value);

    QMatrix4x4 getProjection() const;
    void setProjection(const QMatrix4x4 &value);

    QMatrix4x4 getLocalTransform() const;

    // POUR LE TP3 ON EST OBLIGES D'AVOIR 4 INSTANCES INDEPENDANTES DANS UN TABLEAU
    // astuce : on utilise un indice static currentNumInstance, ce qui rend l'utilisation transparente
    static int getCurrentNumInstance();
    static void setCurrentNumInstance(int value);

private:
    GameScene(); // SINGLETON


protected:

    QOpenGLShaderProgram* defaultShader;
    //static GameScene* instance;

    static GameScene *instances[4]; // POUR LE TP3 ON EST OBLIGES D'AVOIR 4 INSTANCES INDEPENDANTES DANS UN TABLEAU
    static int currentNumInstance;

    QMatrix4x4 projection;

};

#endif // GAMESCENE_H
