#include "gamescene.h"


GameScene *GameScene::instance = nullptr;


GameScene *GameScene::getInstance()
{
    if(!instance) {
        instance = new GameScene();
    }

    return instance;
}

void GameScene::CreateGeometry()
{
    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->CreateGeometry();
    }
}

void GameScene::Draw()
{
    // les position / rotation / scale de l'instance de gamescene
    // sont celles de la "camera"

    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->Draw();
    }
}

GameScene::GameScene()
{

}

QMatrix4x4 GameScene::getProjection() const
{
    return projection;
}

void GameScene::setProjection(const QMatrix4x4 &value)
{
    projection = value;
}

QOpenGLShaderProgram *GameScene::getDefaultShader()
{
    return defaultShader;
}

void GameScene::setDefaultShader(QOpenGLShaderProgram *value)
{
    defaultShader = value;
}
