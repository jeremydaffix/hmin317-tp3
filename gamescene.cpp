#include "gamescene.h"


GameScene *GameScene::instance = nullptr;


GameScene *GameScene::getInstance()
{
    if(!instance) {
        instance = new GameScene();
    }

    return instance;
}

void GameScene::createGeometry()
{
    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->createGeometry();
    }
}

void GameScene::draw()
{
    // les position / rotation / scale de l'instance de gamescene
    // sont celles de la "camera"

    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->draw();
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


// on ne bouge pas la caméra mais la scène qui est la racine du graphe de scène
// redéfinition de getLocalTransform() pour "inverser" la transformation,
// afin de simuler le fait de bouger non pas la scène mais une caméra
QMatrix4x4 GameScene::getLocalTransform() const
{
    QMatrix4x4 transf;

    transf.translate(- getLocalPosition());
    transf.rotate(getLocalRotation().inverted());
    transf.scale(getLocalScale());

    return transf;
}



QOpenGLShaderProgram *GameScene::getDefaultShader()
{
    return defaultShader;
}

void GameScene::setDefaultShader(QOpenGLShaderProgram *value)
{
    defaultShader = value;
}
