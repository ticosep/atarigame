#include "powerbar.h"

PowerBar::PowerBar()
{
    populateColors();
    createCircles();
}

void PowerBar::createCircles()
{
    circleX = std::make_shared<Model>();
    circleX->color = QVector4D(0, 0, 1, 1);
    circleX->readOFFFile("circle.off");
    circleX->invDiag = circleX->invDiag  / 10;
    circleX->midPoint.setY(13);
    circleX->midPoint.setX(-5);

    circleY = std::make_shared<Model>();
    circleY->color = QVector4D(0, 0, 1, 1);
    circleY->readOFFFile("circle.off");
    circleY->invDiag = circleY->invDiag  / 10;
    circleY->midPoint.setY(13);
    circleY->midPoint.setX(5);


}

void PowerBar::populateColors()
{
    targetC.push_back(QVector4D(1, 0, 0, 1)); // Red
    targetC.push_back(QVector4D(0, 0, 1, 1)); // Bllue
    targetC.push_back(QVector4D(1, 0, 1, 1)); // Yellow
    targetC.push_back(QVector4D(1, 1, 1, 1)); // Black

}

void PowerBar::drawModel()
{
    circleX->drawModel();
    circleY->drawModel();
}

void PowerBar::animate()
{
    int index = QRandomGenerator::global()->bounded(0, 3);
    QVector4D tint = targetC[index];
    circleX->color = tint;
    circleY->color = tint;

}


