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
    openFileOff();

}

void OpenGLWidget::resizeGL( int w , int h )
{
    glViewport(0 ,0 ,w , h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!target)
            return;
        target->drawTarget();

}

void OpenGLWidget::openFileOff()
{
    QDir tempDir;
    QString fileName;

    tempDir.cd("..");
    tempDir.cd("atarigame");

    fileName =  tempDir.absoluteFilePath("target.off");

    if (!fileName.isEmpty())
    {

       target = std::make_shared<Target>(this);
       target->readOFFFile(fileName);
    }
    update();


}



