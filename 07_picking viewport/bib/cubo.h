#ifndef CUBO_H
#define CUBO_H

#include <objeto.h>
#include "quadrado.h"

class Cubo: public Objeto
{
public:

    Quadrado *q = new Quadrado();
    Cubo();
    void desenha();
};



#endif // CUBO_H
