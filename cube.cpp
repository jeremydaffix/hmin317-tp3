#include "cube.h"


Cube::Cube(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh) : Model3D (pos, rot, sc, sh)
{

}

void Cube::CreateGeometry()
{
    std::cout << "CREATE CUBE\n";


    // UTILISER POSITION ET NON LOCALPOSITION
    /*float posX = localPosition.x();
    float posY = localPosition.y();
    float posZ = localPosition.z();*/

    float sizeX = localScale.x();
    float sizeY = localScale.y();
    float sizeZ = localScale.z();

    float sx = sizeX / 2.;
    float sy = sizeY / 2.;
    float sz = sizeZ / 2.;



    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f * sx, -1.0f * sy,  1.0f * sz), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f * sx, -1.0f * sy,  1.0f * sz), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f * sx,  1.0f * sy,  1.0f * sz), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f * sx,  1.0f * sy,  1.0f * sz), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f * sx, -1.0f * sy,  1.0f * sz), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f * sx, -1.0f * sy, -1.0f * sz), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f * sx,  1.0f * sy,  1.0f * sz), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f * sx,  1.0f * sy, -1.0f * sz), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f * sx, -1.0f * sy, -1.0f * sz), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f * sx, -1.0f * sy, -1.0f * sz), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f * sx,  1.0f * sy, -1.0f * sz), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f * sx,  1.0f * sy, -1.0f * sz), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f * sx, -1.0f * sy, -1.0f * sz), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f * sx, -1.0f * sy,  1.0f * sz), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f * sx,  1.0f * sy, -1.0f * sz), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f * sx,  1.0f * sy,  1.0f * sz), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f * sx, -1.0f * sy, -1.0f * sz), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f * sx, -1.0f * sy, -1.0f * sz), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f * sx, -1.0f * sy,  1.0f * sz), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f * sx, -1.0f * sy,  1.0f * sz), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f * sx,  1.0f * sy,  1.0f * sz), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f * sx,  1.0f * sy,  1.0f * sz), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f * sx,  1.0f * sy, -1.0f * sz), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f * sx,  1.0f * sy, -1.0f * sz), QVector2D(0.66f, 1.0f)}  // v23
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

void Cube::Draw()
{
    //qDebug() << "DRAW CUBE " << localPosition << " " << localRotation;

    if(shader == NULL) shader = GameScene::getInstance()->getDefaultShader();


    // UTILISER POSITION ET NON LOCALPOSITION

    QMatrix4x4 matrix;
    matrix.translate(localPosition);
    matrix.rotate(localRotation);
    shader->setUniformValue("mvp_matrix", GameScene::getInstance()->getProjection() * matrix);


qDebug() << GameScene::getInstance()->getProjection();

    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = shader->attributeLocation("a_position");

    shader->enableAttributeArray(vertexLocation);
    shader->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = shader->attributeLocation("a_texcoord");
    shader->enableAttributeArray(texcoordLocation);
    shader->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}
