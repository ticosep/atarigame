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
    createModels();

    time =  new QTime();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(300);
    time->start();


}

void OpenGLWidget::resizeGL( int w , int h )
{
    glViewport(0 ,0 ,w , h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!target || !arrow)
        return;
    target->drawModel();
    arrow->drawModel();


}

void OpenGLWidget::createModels()
{
    target = std::make_shared<Target>();
    target->createTarget();

    arrow = std::make_shared<Model>();
    arrow->color = QVector4D(1, 1, 1, 1);
    arrow->readOFFFile("circle.off");
    arrow->invDiag = arrow->invDiag  / 10;
    arrow->midPoint.setZ(-10);


    update();
}

void OpenGLWidget::animate()
{
      power = QRandomGenerator::global()->bounded(0, 4);
      emit updateXpLabel(QString("X POWER: %1").arg(power));
      emit updateYpLabel(QString("Y POWER: %1").arg(power));

      update();

}

// Strong focus is required
void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Space)
    {

            if(power == 3){
                arrow->midPoint.setZ(0);
                arrow->midPoint.setX(0);
                arrow->midPoint.setY(0);

                pts += 10;

            } else if (power == 2){
                arrow->midPoint.setZ(0);
                arrow->midPoint.setX(4);
                arrow->midPoint.setY(4);

                pts += 5;

            } else if (power == 1){
                arrow->midPoint.setZ(0);
                arrow->midPoint.setX(6);
                arrow->midPoint.setY(6);

                pts += 1;

            } else {
                arrow->midPoint.setZ(0);
                arrow->midPoint.setX(10);
                arrow->midPoint.setY(10);
            }

            update();

            emit updatePtsLabel(QString("POINTS: %1").arg(pts));

    }

    if (event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
}




