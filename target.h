#ifndef TARGET_H
#define TARGET_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <limits>
#include <iostream>
#include <memory>

class Target : public QOpenGLExtraFunctions
{
public:
    Target(QOpenGLWidget * _glWidget);
    ~Target();
    std::unique_ptr <QVector4D[]> vertices;
    std::unique_ptr <unsigned int []> indices;

    QOpenGLWidget * glWidget;

    unsigned int numVertices;
    unsigned int numFaces;

    bool shaderOK, vboOK, loaded;

    int xTransform = 0;
    int yTransform = 0;
    int zTransform = 0;

    GLuint vao = 0;
    GLuint vboVertices = 0;
    GLuint vboIndices = 0;
    GLuint shaderProgram = 0;

    QMatrix4x4 targetMatrix;
    QVector3D midPoint;

    QVector4D max;
    QVector4D min;

    double invDiag;

    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void readOFFFile(const QString &fileName);
    void drawTarget();


};

#endif // Target_H
