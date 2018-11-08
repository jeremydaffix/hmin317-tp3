/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"


#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(int _fps, QWidget *parent) :
    QOpenGLWidget(parent),
    //geometries(0),
    texture(0),
    angularSpeed(0)
{

    fps = _fps;


}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    //delete heightmap;
    delete geometries;
    //delete cube;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        //cameraRotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * cameraRotation; ////

        // Request an update
        update();
    }

    // pour faire tourner la caméra sur elle même
   // cameraRotation = QQuaternion::fromEulerAngles(0, rotationSpeed, 0) * cameraRotation; // tourner à vitesse constante
    //qDebug() << cameraRotation.toEulerAngles();

    update();

    // déplacement géré ici
    // position pas changée dans l'event clavier
    // on estime que timerEvent est lancée à un fps fixe

    bool needUpdate = true;

    switch(movementDirection)
    {
        case DIRECTION::UP:
            //if(cameraPosition.z() > -4.0) cameraPosition.setZ(cameraPosition.z() - 0.2);
            if(cameraMoveLeftRight.y() > -6) cameraMoveLeftRight.setY(cameraMoveLeftRight.y() - 0.2);
        break;

        case DIRECTION::DOWN:
            //if(cameraPosition.z() < -2) cameraPosition.setZ(cameraPosition.z() + 0.2);
            if(cameraMoveLeftRight.y() < 6) cameraMoveLeftRight.setY(cameraMoveLeftRight.y() + 0.2);
        break;

        case DIRECTION::LEFT:
            if(cameraMoveLeftRight.x() < 6) cameraMoveLeftRight.setX(cameraMoveLeftRight.x() + 0.2);
        break;

        case DIRECTION::RIGHT:
            if(cameraMoveLeftRight.x() > -6) cameraMoveLeftRight.setX(cameraMoveLeftRight.x() - 0.2);
        break;

        default:
            needUpdate = false;
        break;

    }

    if(needUpdate) update();
}
//! [1]



void MainWidget::keyPressEvent(QKeyEvent* e)
{

    switch(e->key())
    {
        case Qt::Key_Z:
            movementDirection = DIRECTION::UP;
        break;

        case Qt::Key_S:
            movementDirection = DIRECTION::DOWN;
        break;

        case Qt::Key_Q:
            movementDirection = DIRECTION::LEFT;
        break;

        case Qt::Key_D:
            movementDirection = DIRECTION::RIGHT;
        break;

        default:
            movementDirection = DIRECTION::NO;
        break;
    }


    switch(e->key())
    {
        case Qt::Key_Up:
            if(rotationSpeed < 10.0) rotationSpeed += 0.1;
        break;

        case Qt::Key_Down:
            if(rotationSpeed > 0.2) rotationSpeed -= 0.1;
        break;

        default:
        break;
    }

}

void MainWidget::keyReleaseEvent(QKeyEvent* e)
{
    movementDirection = DIRECTION::NO;
}



void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(1000 / fps, this);





    Cube *cube = new Cube(QVector3D(-0.5, 0.2, -5.), QQuaternion::fromEulerAngles(0, 20, 0), QVector3D(1.5, 2.0, 1.0));
    Cube *cube2 = new Cube(QVector3D(0.5, 0.2, -5));

    GameScene::getInstance()->addChild(cube);
    GameScene::getInstance()->addChild(cube2);


    //Plane *plane = new Plane(16, QVector3D(0, -5, -5), QQuaternion::fromEulerAngles(95, 0, 0), QVector3D(1, 1, 1));
    //GameScene::getInstance()->addChild(plane);

    Terrain *terrain = new Terrain(":/island_heightmap.png", 64, QVector3D(0, -3, 0), QQuaternion::fromEulerAngles(-90, 0, 0), QVector3D(1, 1, 1));
    terrain->setShader(&shaderTerrain);
    GameScene::getInstance()->addChild(terrain);


    GameScene::getInstance()->createGeometry();


    GameScene::getInstance()->setLocalPosition(QVector3D(0, 0, 10));
    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(0, 0, 0));
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!shaderDice.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!shaderDice.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();


    // Link shader pipeline
    if (!shaderDice.link())
        close();

    // Bind shader pipeline for use
    if (!shaderDice.bind())
        close();




    // Compile vertex shader
    if (!shaderTerrain.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader_color.glsl"))
        close();

    // Compile fragment shader
    if (!shaderTerrain.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader_color.glsl"))
        close();


    // Link shader pipeline
    if (!shaderTerrain.link())
        close();

    // Bind shader pipeline for use
    /*-if (!shaderTerrain.bind())
        close();*/



    GameScene::getInstance()->setDefaultShader(&shaderDice);
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    //heightmap = new QImage(QImage(":/island_heightmap.png"));

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    ////const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    const qreal zNear = 1.0, zFar = 100.0, fov = 45.0;


    // Reset projection
    QMatrix4x4 proj;
    proj.setToIdentity();

    // Set perspective projection
    proj.perspective(fov, aspect, zNear, zFar);

    GameScene::getInstance()->setProjection(proj);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
    //QMatrix4x4 matrix;

    // position fixe caméra (tp1)
    //matrix.translate(0.0, 0.0, -55.0);

    // position au dessus du terrain, modifiable par ZQSD (tp1)
    //matrix.translate(cameraPosition);
    //matrix.rotate(cameraRotation);

     //matrix.lookAt(cameraPosition, QVector3D(0, 0, 0), QVector3D(0.0, 1.0, 0.0));

    // on inverse R et T si on veut faire tourner la camera sur elle même (tp2)
    // (sinon elle tourne autour de l'origine)
    //matrix.rotate(cameraRotation);
    //matrix.translate(cameraPosition);
    //matrix.translate(cameraMoveLeftRight);


    /*QVector3D mlr =  QQuaternion::fromEulerAngles(0, cameraRotation.toEulerAngles().y(), 0) * cameraMoveLeftRight;
    //mlr.setZ(0);
    qDebug() << cameraMoveLeftRight << mlr;
    matrix.translate(mlr);*/


    // Set modelview-projection matrix
    //program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    //program.setUniformValue("texture", 0);

    // Draw cube geometry
    //geometries->drawCubeGeometry(&program);
    //geometries->drawPlaneGeometry(&program, geometries->sizeTerrain);

    GameScene::getInstance()->draw();
}
