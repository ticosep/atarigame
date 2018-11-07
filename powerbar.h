#ifndef POWERBAR_H
#define POWERBAR_H

#include <model.h>


class PowerBar : public Model
{
public:
    PowerBar();

    void createPowerBar();
    void createSquare();
    void drawModel();

private:
    std::shared_ptr<Model> squareX = nullptr;

};

#endif // POWERBAR_H
