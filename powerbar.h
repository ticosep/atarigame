#ifndef POWERBAR_H
#define POWERBAR_H

#include <model.h>
#include <QOpenGLWidget>


class PowerBar : public QOpenGLWidget
{
public:
    PowerBar();
    int power;
    void createPowerBar();
    void createCircles();
    void drawModel();
    void animate();
    void populateColors();

private:
    std::shared_ptr<Model> circleX = nullptr;
    std::shared_ptr<Model> circleY = nullptr;
    std::vector<QVector4D> targetC;

};

#endif // POWERBAR_H
