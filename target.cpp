#include "target.h"

Target::Target()
{

}

void Target::createTarget()
{
    for(unsigned int i =0; i < 3; ++i) {
                std::shared_ptr<Model> circle (new Model());
                circle->readOFFFile("circle.off");
                circles.push_back(circle);
      }

}
