#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "target.h"
#include "arrow.h"
#include "powerbar.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QDir>
#include <QTime>
#include <QTimer>


class OpenGLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT



    public:
        std::shared_ptr<Target> target = nullptr;
        QTimer *timer;
        QTime *time;
        OpenGLWidget(QWidget * parent = 0);
        void openFileOff();


    protected:
        void initializeGL();
        void resizeGL(int width , int height);
        void paintGL();


};

#endif // OPENGLWIDGET_H
