#ifndef TARGET_H
#define TARGET_H

#include <model.h>

class Target : public Model
{
public:
    Target();

    std::vector<std::shared_ptr<Model>> circles;
    void createTarget();

    unsigned int numCircles = 3;
};

#endif // TARGET_H
