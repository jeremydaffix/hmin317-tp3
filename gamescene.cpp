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
    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->Draw();
    }
}

GameScene::GameScene()
{

}

QOpenGLShaderProgram *GameScene::getDefaultShader()
{
    return defaultShader;
}

void GameScene::setDefaultShader(QOpenGLShaderProgram *value)
{
    defaultShader = value;
}
