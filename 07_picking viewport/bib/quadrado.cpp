#include "quadrado.h"

Quadrado::Quadrado()
{
}



void Quadrado::desenha()
{
    Objeto::desenha();

        glBegin(GL_QUADS);
            glNormal3f(0,0,1);
            glVertex3f(-0.25, 0.25, 0);
            glVertex3f(-0.25, -0.25, 0);
            glVertex3f(0.25, -0.25, 0);
            glVertex3f(0.25, 0.25, 0);
        glEnd();

}
