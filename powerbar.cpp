#include "powerbar.h"

PowerBar::PowerBar()
{
    createSquare();
}

void PowerBar::createSquare()
{
    squareX = std::make_shared<Model>();
    squareX->color = QVector4D(0, 1, 0, 1);
    squareX->readOFFFile("square.off");
    squareX->invDiag = squareX->invDiag  / 6;
    squareX->midPoint.setY(8);


}

void PowerBar::drawModel()
{
    squareX->drawModel();
}
