#ifndef ARROW_H
#define ARROW_H

#include <model.h>

class Arrow
{
public:
    Arrow();

    std::shared_ptr<Model> arrow = nullptr;

    void createArrow();
    void drawModel();
};

#endif // ARROW_H
