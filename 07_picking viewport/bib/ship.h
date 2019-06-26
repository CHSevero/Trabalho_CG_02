#ifndef SHIP_H
#define SHIP_H
#include <objeto.h>

class Ship: public Objeto
{
public:

    Model3DS * model;
    Ship();
    void desenha();

};

#endif // SHIP_H
