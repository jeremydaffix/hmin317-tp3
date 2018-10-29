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

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

#include <string>
#include <iostream>


struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    heightmap = new QImage(QImage(":/island_heightmap.png"));

    // Initializes cube geometry and transfers it to VBOs
    //initCubeGeometry();

     // si on change le nombre de sommets, ne pas oublier d'adapter l'affichage en conséquences !!!
     //initPlaneGeometry(); // plan 16x16
     //initTerrainGeometry(); // terrain avec relief 16x16
     //initTerrainGeometry(sizeTerrain, 16. / sizeTerrain);
     //initTerrainGeometry(sizeTerrain, 16. / sizeTerrain, heightmap);
     //initTerrainGeometry(sizeTerrain, 32. / sizeTerrain, heightmap); // + grand !

}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();

    delete heightmap;
}
//! [0]

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
//! [1]
}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}
//! [2]




void GeometryEngine::initPlaneGeometry(int nbrSommets, float size)
{
    int nbrFaces = nbrSommets - 1;
    //int nbrIndices = (nbrFaces * nbrFaces * 6) + ((nbrFaces - 1) * 4);
    int nbrIndices = (nbrFaces * nbrFaces * 6) + (nbrFaces * 4);

    VertexData vertices[nbrSommets * nbrSommets]; // tableau des sommets

    // pour tous les sommets
    for(int i = 0 ; i < nbrSommets ; ++i) { // ligne

        for(int j = 0 ; j < nbrSommets ; ++j) { // colonne

            // on remplit ligne par ligne

            int pos = i * nbrSommets + j;

            vertices[pos].position = QVector3D((float)j * size, (float)i * size, 0.0); // plan normal

            vertices[pos].texCoord = QVector2D(1. / nbrFaces * j, 1. / nbrFaces * i);

        }
    }



    GLushort indices[nbrIndices];

    int pos = 0;

    // pour toutes les cases (15 x 15)
    // 2 triangles à afficher
    for(GLushort i = 0 ; i < nbrFaces ; ++i) { // ligne

        for(GLushort j = 0 ; j < nbrFaces ; ++j) { // colonne

            // trangle haut gauche
            GLushort index1 = i * nbrSommets + j; // haut gauche
            GLushort index2 = index1 + 1; // haut droit
            GLushort index3 = index1 + nbrSommets; // bas gauche

            // triangle bas droit
            GLushort index4 = index3; // bas gauche
            GLushort index5 = index3 + 1; // bas droit
            GLushort index6 = index2; // haut droit

            indices[pos++] = index1;
            indices[pos++] = index2;
            indices[pos++] = index3;

            indices[pos++] = index4;
            indices[pos++] = index5;
            indices[pos++] = index6;

            // sur une même ligne, on se retrouve au 1er point de la case suivante en haut à gauche
        }

        // changement de ligne
        /*if(i != (nbrFaces - 1))*/ {

            indices[pos++] = i * nbrSommets + nbrSommets;
            indices[pos++] = i * nbrSommets; // déplacement à gauche
            indices[pos++] = i * nbrSommets;
            indices[pos++] = (i + 1) * nbrSommets; // déplacement d'une ligne
        }
    }

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrSommets * nbrSommets * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));

}



void GeometryEngine::initTerrainGeometry(int nbrSommets, float size, QImage* qi)
{
    int nbrFaces = nbrSommets - 1;
    int nbrIndices = (nbrFaces * nbrFaces * 6) + (nbrFaces * 4);

    VertexData vertices[nbrSommets * nbrSommets]; // tableau des sommets

    // relief généré par heightmap
    float stepHeightmap;
    if(qi != NULL)
    {
        // la heightmap peut être très grande
        // on prendra des échantillons en fonction de la taille de notre terrain
        stepHeightmap =  qi->size().width() / nbrSommets;
    }

    int scaleRelief = nbrSommets / 16;
    qDebug() << scaleRelief;

    // pour tous les sommets
    for(int i = 0 ; i < nbrSommets ; ++i) { // ligne

        for(int j = 0 ; j < nbrSommets ; ++j) { // colonne

            // on remplit ligne par ligne

            int pos = i * nbrSommets + j;


            // relief généré
            if(qi == NULL)
            {
                if(i > 3 * scaleRelief && i < 12 * scaleRelief && j > 3 * scaleRelief && j < 12 * scaleRelief) // partie relief
                {
                    if((i < 7 * scaleRelief || i > 9 * scaleRelief) && (j < 7 * scaleRelief || j > 9 * scaleRelief))
                        vertices[pos].position = QVector3D((float)j * size, (float)i * size, -2.0);
                    else
                        vertices[pos].position = QVector3D((float)j * size, (float)i * size, 2.0);
                }
                else // partie plate
                {
                    vertices[pos].position = QVector3D((float)j * size, (float)i * size, 0.0);
                }
            }

            // relief généré par heightmap
            else
            {
                QColor col = qi->pixel(j * stepHeightmap, i * stepHeightmap);

                //qDebug() << col;

                int r, g, b, a;
                col.getRgb(&r, &g, &b, &a);

                float coef = 2.0;

                float z = (r + g + b + a) / 255. / 4. * coef;

                //qDebug() << z;
                vertices[pos].position = QVector3D((float)j * size, (float)i * size, z);
            }


            vertices[pos].texCoord = QVector2D(1. / nbrFaces * j, 1. / nbrFaces * i);

        }
    }



    GLushort indices[nbrIndices];

    int pos = 0;

    // pour toutes les cases (15 x 15)
    // 2 triangles à afficher
    for(GLushort i = 0 ; i < nbrFaces ; ++i) { // ligne

        for(GLushort j = 0 ; j < nbrFaces ; ++j) { // colonne

            // trangle haut gauche
            GLushort index1 = i * nbrSommets + j; // haut gauche
            GLushort index2 = index1 + 1; // haut droit
            GLushort index3 = index1 + nbrSommets; // bas gauche

            // triangle bas droit
            GLushort index4 = index3; // bas gauche
            GLushort index5 = index3 + 1; // bas droit
            GLushort index6 = index2; // haut droit

            indices[pos++] = index1;
            indices[pos++] = index2;
            indices[pos++] = index3;

            indices[pos++] = index4;
            indices[pos++] = index5;
            indices[pos++] = index6;

            // sur une même ligne, on se retrouve au 1er point de la case suivante en haut à gauche
        }

        // changement de ligne
        /*if(i != (nbrFaces - 1))*/ {

            indices[pos++] = i * nbrSommets + nbrSommets;
            indices[pos++] = i * nbrSommets; // déplacement à gauche
            indices[pos++] = i * nbrSommets;
            indices[pos++] = (i + 1) * nbrSommets; // déplacement d'une ligne
        }
    }


    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrSommets * nbrSommets * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));

}




void GeometryEngine::drawPlaneGeometry(QOpenGLShaderProgram *program, int nbrSommets)
{
    int nbrFaces = nbrSommets - 1;
    //int nbrIndices = (nbrFaces * nbrFaces * 6) + ((nbrFaces - 1) * 4);
    int nbrIndices = (nbrFaces * nbrFaces * 6) + (nbrFaces * 4);

    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw plane geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, nbrIndices, GL_UNSIGNED_SHORT, 0);
}


