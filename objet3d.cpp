#include "objet3d.h"

Objet3d::Objet3d(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh) : Model3D (pos, rot, sc, sh)
{

}

void Objet3d:: createGeometry(){

    std::vector< unsigned int > vertexIndices, normalIndices;
    std::vector<QVector3D> temp_vertices;
    std::vector< QVector3D> temp_normals;

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
}
void Objet3d::draw(){

}
