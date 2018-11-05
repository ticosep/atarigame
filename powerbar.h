#ifndef POWERBAR_H
#define POWERBAR_H

#include <model.h>


class PowerBar : public Model
{
public:
    PowerBar();

    void createPowerBar();
    void createLine();
    void createSquare();

private:
    std::vector<Model> square;

};

#endif // POWERBAR_H
