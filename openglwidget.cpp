#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}
void OpenGLWidget::initializeGL()
{

    initializeOpenGLFunctions();
    qDebug ("OpenGL version : %s", glGetString(GL_VERSION));
    qDebug ("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    glEnable (GL_DEPTH_TEST);


}

void OpenGLWidget::resizeGL( int w , int h )
{
    glViewport(0 ,0 ,w , h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void OpenGLWidget::createModels()
{
    target = std::make_shared<Target>();
}


