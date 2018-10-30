#ifndef TARGET_H
#define TARGET_H

#include <model.h>

class Target : public Model
{
public:
    Target();

    std::vector<std::shared_ptr<Model>> circles;
    std::vector<QVector4D> colorsCircle;

    void createTarget();
    void drawModel();
    void populateColors();

    unsigned int numCircles = 3;
};

#endif // TARGET_H
