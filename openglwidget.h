#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "model.h"
#include "arrow.h"
#include "powerbar.h"
#include "target.h"
#include <memory>

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


    protected:
        void initializeGL();
        void resizeGL(int width , int height);
        void paintGL();
        void createModels();


};

#endif // OPENGLWIDGET_H
