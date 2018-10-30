#include "target.h"

Target::Target()
{
    populateColors();
}

void Target::createTarget()
{
    for(unsigned int i =0; i < numCircles; ++i) {
                double divisor = i ? i + 0.4 : 1;
                std::shared_ptr<Model> circle (new Model());

                circle->color = colorsCircle[i];
                circle->readOFFFile("circle.off");
                circle->invDiag = circle->invDiag  / divisor;

                float z = circle->midPoint.z();
                circle->midPoint.setZ(z + i*0.01);
                circles.push_back(circle);
      }

}

void Target::drawModel()
{
    for(unsigned int i =0; i < numCircles; ++i) {
               circles[i]->drawModel();
      }
}


void Target::populateColors()
{
    QVector4D blue = QVector4D(0, 0, 1, 1);
    QVector4D yellow = QVector4D(1, 1, 0, 1);
    QVector4D red = QVector4D(1, 0, 0, 1);

    colorsCircle.push_back(blue);
    colorsCircle.push_back(yellow);
    colorsCircle.push_back(red);



}
