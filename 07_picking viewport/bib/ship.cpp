#include "ship.h"

Ship::Ship()
{
    model = new Model3DS("../3ds/Ship_free.3DS");
}
void Ship::desenha()
{
    Objeto::desenha();
    glPushMatrix();
        glTranslatef(0,0,0);
        glRotatef(-90,1,0,0);
        glScalef(0.003,0.003,0.003);
        model->draw();
    glPopMatrix();
}
