#include "objet3d.h"

Objet3d::Objet3d(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh) : Model3D (pos, rot, sc, sh)
{
    path = (char*)malloc(sizeof(char)*1024);

}

void Objet3d:: createGeometry(){

    std::vector< unsigned int > vertexIndices, normalIndices;
    std::vector<QVector3D> temp_vertices;
    std::vector< QVector3D> temp_normals;

    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
    }

    while( 1 ){

        char lineHeader[256];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        if ( strcmp( lineHeader, "v" ) == 0 ){
            QVector3D vertex;
            float x,y,z;
            fscanf(file, "%f %f %f\n", x, y, z );
            vertex.setX(x);
            vertex.setY(y);
            vertex.setZ(z);
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            QVector3D normal;
            float x,y,z;
            fscanf(file, "%f %f %f\n", x, y, z );
            normal.setX(x);
            normal.setY(y);
            normal.setZ(z);
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }

        // else : parse lineHeader

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
}
void Objet3d::draw(){

}
