#include "objet3d.h"

Objet3d::Objet3d(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh) : Model3D (pos, rot, sc, sh)
{
    path = (char*)malloc(sizeof(char)*1024);

}

bool Objet3d:: loadobj(vector <QVector3D> & out_vertices, vector <QVector3D> & out_normals){

    vector< unsigned int > vertexIndices, normalIndices;
    vector<QVector3D> temp_vertices;
    vector< QVector3D> temp_normals;

    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return false;
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
    }
    for( unsigned int i=0; i < vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        QVector3D vertex = temp_vertices[ vertexIndex-1 ];
        out_vertices.push_back(vertex);
    }
    for( unsigned int i=0; i < normalIndices.size(); i++ ){
        unsigned int normalIndex = normalIndices[i];
        QVector3D normals = temp_normals[ normalIndex-1 ];
        out_normals.push_back(normals);
    }

    return true;
}

void Objet3d:: createGeometry(){

    vector<QVector3D> sommet;
    vector<QVector3D> normals;
    vector<GLushort> indices;
    vector<int> faces;
    bool res = loadobj(sommet,normals);
    for(int i = 0; i < sommet.size(); i++){
        indices.push_back(i);
    }


    //VBO0
    arrayBuf.bind();
    arrayBuf.allocate(sommet.data(),sommet.size()* sizeof(QVector3D));
    arrayBuf.bind();
    arrayBuf.allocate(sommet.data(), sommet.size() * sizeof(VertexData));

    //VBO1
    taille = indices.size();
    indexBuf.bind();
    indexBuf.allocate(indices.data(), indices.size() * sizeof(GLushort));


}
void Objet3d::draw(){
    GameObject::draw(); // affichage enfants

    //qDebug() << "DRAW CUBE " << localPosition << " " << localRotation;

    if(shader == NULL) shader = GameScene::getInstance()->getDefaultShader();

    if (!shader->bind())
            return;

    QMatrix4x4 matrix = getTransform(); // transform dans le repère monde

    shader->setUniformValue("mvp_matrix", GameScene::getInstance()->getProjection() * matrix);



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
    glDrawElements(GL_TRIANGLES, taille, GL_UNSIGNED_SHORT, 0);
}
