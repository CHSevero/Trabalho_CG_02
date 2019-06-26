#include "cubo.h"

Cubo::Cubo()
{

}

void Cubo::desenha()
{
    Objeto::desenha();
    GUI::setColor(0,0,1);
    glPushMatrix();


        glPushMatrix();
            glTranslatef(0,0,0.25);
            q->desenha();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,-0.25);
            glRotatef(180,0,1,0);
            q->desenha();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.25,0,0);
            glRotatef(90,0,1,0);
            q->desenha();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-0.25,0,0);
            glRotatef(-90,0,1,0);
            q->desenha();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0.25,0);
            glRotatef(-90,1,0,0);
            q->desenha();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,-0.25,0);
            glRotatef(90,1,0,0);
            q->desenha();
        glPopMatrix();

    glPopMatrix();
}
