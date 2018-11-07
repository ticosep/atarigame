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

        int pts = 0; // Number of points
        int power;
        std::shared_ptr<Target> target = nullptr;
        std::shared_ptr<Model> arrow = nullptr;

        QTimer *timer;
        QTime *time;
        OpenGLWidget(QWidget * parent = 0);

        void keyPressEvent(QKeyEvent *event);

    protected:
        void initializeGL();
        void resizeGL(int width , int height);
        void paintGL();
        void createModels();



public slots:
    void animate();

signals:
    void updatePtsLabel(QString);
    void updateXpLabel(QString);
    void updateYpLabel(QString);

};

#endif // OPENGLWIDGET_H
