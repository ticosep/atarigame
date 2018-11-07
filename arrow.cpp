#include "arrow.h"

Arrow::Arrow()
{

}
void Arrow::createArrow()
{
    arrow = std::make_shared<Model>();
    arrow->color = QVector4D(1,1,1,1);
    arrow->readOFFFile("circle.off");
    arrow->invDiag = arrow->invDiag  / 10;

}

void Arrow::drawModel()
{
    arrow->drawModel();
}
