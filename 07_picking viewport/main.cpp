#include <iostream>

using namespace std;

#include <gui.h>
#include <vector>
#include  <curva.h>
#include <ship.h>
Ship *ship = new Ship();
Curva *c = new Curva();
CameraJogo *camera = new CameraJogo();

double delta_u=0.01;
double delta_u2=0.01;

int tipoM = 0;
//-------------------picking------------------
vector<Vetor3D> pontosControle;

int pontoSelecionado = 0; //names = [1,n] //n = pontosControle.size()
//bool transPontos = glutGUI::trans_obj; //= true;

void desenhaPontosDeControle()
{
    //desenhando pontos de controle
    for (int i=0; i<pontosControle.size(); i++) {
        //definindo cor da selecao
        if (i == pontoSelecionado-1) {
            GUI::setColor(1,1,1,1,true);
        } else {
            GUI::setColor(0,1,0,1,true);
        }
        //desenhando (definindo nomes para o picking)
        Vetor3D p = pontosControle[i];
        glPushName(i+1); //não se deve definir name = 0!
            GUI::drawSphere(p.x,p.y,p.z,0.2);
        glPopName();
    }

//    //teste triangulo
//    glBegin(GL_TRIANGLES);
//        glNormal3f(0,0,1); //definir a normal permite ver as cores mais vivas ao posicionar a iluminacao adequadamente
//        GUI::setColor(1,1,1);
//        glVertex3f(0,0,1);
//        GUI::setColor(0,0,1,0.0);
//        glVertex3f(2,0,1);
//        GUI::setColor(0,1,0,0.0);
//        glVertex3f(0,2,1);
//    glEnd();
//    //teste triangulo usando glColor (sem iluminacao)
//    glDisable(GL_LIGHTING);
//    glBegin(GL_TRIANGLES);
//        glNormal3f(0,0,1);
//        glColor4f(0,1,0,1);
//        glVertex3f(-1,2,1);
//        glColor4f(0,0,1,1);
//        glVertex3f(-3,0,1);
//        glColor4f(1,1,1,0);
//        glVertex3f(-1,0,1);
//    glEnd();
//    glEnable(GL_LIGHTING);
}

//picking
int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);

//de acordo com a implementacao original da funcao display
    //lembrar de nao inicializar a matriz de projecao, para nao ignorar a gluPickMatrix
    GUI::displayInit();
    //só precisa desenhar o que for selecionavel
    desenhaPontosDeControle();
//fim-de acordo com a implementacao original da funcao display

    //retornando o name do objeto (ponto de controle) mais proximo da camera (z minimo! *[matrizes de normalizacao da projecao])
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}
//-------------------picking------------------

//-------------------viewPorts------------------
bool viewports = false;
bool scissored = false;

void cenario();

//visao de duas cameras (duas viewports), viewport auxiliar sobrepondo a principal
void viewPorts() {
    float width = glutGUI::width;
    float height = glutGUI::height;

    //viewport principal
    glViewport(0, 0, width, height);
        glLoadIdentity();
        gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
            cenario();

    //viewport auxiliar sobrepondo a principal
    if (!scissored) {
        //misturando com a principal
        glViewport(0, 3*height/4, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, 3*height/4, width/4, height/4);
    }
        glLoadIdentity();
//        Vetor3D eye = pontosControle[4];
//        Vetor3D center = pontosControle[2];
        gluLookAt(camera->e.x,camera->e.y,camera->e.z,camera->c.x,camera->c.y,camera->c.z,camera->u.x,camera->u.y,camera->u.z);
            cenario();
}
//-------------------viewPorts------------------

void cenario() {
    //GUI::setLight(1,1,3,5,true,false);
    //GUI::setLight(2,-1.5,0.5,-1,true,false);
    GUI::setLight(3,-5,3,5,true,false);

    GUI::drawOrigin(0.5);

    //GUI::setColor(1,0,0);
    //GUI::drawFloor();
//    GUI::setColor(0,0,0);
//    Desenha::drawGrid( 5, 0, 1, 1 );

    desenhaPontosDeControle();

    c->desenhaCurva(pontosControle, delta_u);
    c->desenhaShip(pontosControle,delta_u2, camera);
}

void desenha() {
    GUI::displayInit();

    if (!viewports) {
        cenario();
    } else {
        viewPorts();
    }

    //transladando ponto selecionado atraves do picking
    //if (pontoSelecionado > 0 and pontoSelecionado <= objetos.size()) {
    if (pontoSelecionado!=0) {
        pontosControle[pontoSelecionado-1].x += glutGUI::dtx;
        pontosControle[pontoSelecionado-1].y += glutGUI::dty;
        pontosControle[pontoSelecionado-1].z += glutGUI::dtz;
    }

    GUI::displayEnd();
}

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        //transPontos = glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'v':
        viewports = !viewports;
        break;
    case 's':
        scissored = !scissored;
        break;
    case 'a':
        tipoM  = (tipoM + 1)%5;
        if(tipoM==0){
            c->Matriz=c->Interpoladora;
        }else if(tipoM==1){
            c->Matriz=c->Bezier;
        }else if(tipoM==2){
            c->Matriz=c->Hermite;
        }else if(tipoM==3){
            c->Matriz=c->CatmullRom;
        }else{
            c->Matriz=c->Bspline;
        }
        break;
    case 'b':
        pontosControle.push_back(Vetor3D(0,0,0));
        break;
    case 'd':

        delta_u -=0.0001;
        if(delta_u <= 0){
            delta_u = 0.0001;
        }
        break;
    case 'D':

        delta_u += 0.0001;
        if(delta_u > 1){
            delta_u = 1;
        }
        break;
    case ',':
        c->u-= 0.2;
        if(c->u<0){
            c->u=0;
            c->ic-=1;
            if(c->ic<0){
                c->ic=pontosControle.size()-1;
            }
        }
        break;
    case '<':
        c->u+= 0.1;
        if(c->u>1){
            c->u=0;
            c->ic+=1;
            if(c->ic>pontosControle.size()-1){
                c->ic=0;
            }
        }
        break;
    case 'p':
        if(pontosControle.size() > 0){
            pontosControle.erase(pontosControle.begin()+pontoSelecionado-1);
        }

        break;
    case '.':

        delta_u2 -=0.0001;
        if(delta_u2 <= 0){
            delta_u2 = 0.0001;
        }
        break;
    case '>':

        delta_u2 += 0.0001;
        if(delta_u2 > 1){
            delta_u2 = 1;
        }
        break;
    default:
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick;
                glutGUI::lbpressed = false;
            }
        }
    }
}

int main()
{
    cout << "Hello World!" << endl;



//    pontosControle.push_back(Vetor3D(2,1,0));
//    pontosControle.push_back(Vetor3D(1,2,0));
//    pontosControle.push_back(Vetor3D(0,2,0));
//    pontosControle.push_back(Vetor3D(-1,2,0));
//    pontosControle.push_back(Vetor3D(-2,1,0));
//    pontosControle.push_back(Vetor3D(-3,0,0));
//    pontosControle.push_back(Vetor3D(-2,-2,0));
//    pontosControle.push_back(Vetor3D(-1,-2,0));
//    pontosControle.push_back(Vetor3D(0,-2,0));
//    pontosControle.push_back(Vetor3D(1,-2,0));
//    pontosControle.push_back(Vetor3D(2,-1,0));
//    pontosControle.push_back(Vetor3D(3,0,0));
    pontosControle.push_back(Vetor3D(2,2,0));
    pontosControle.push_back(Vetor3D(0,3,0));
    pontosControle.push_back(Vetor3D(-2,2,0));
    pontosControle.push_back(Vetor3D(-3,0,0));
    pontosControle.push_back(Vetor3D(-2,-2,0));
    pontosControle.push_back(Vetor3D(0,-3,0));
    pontosControle.push_back(Vetor3D(2,-2,0));
    pontosControle.push_back(Vetor3D(3,0,0));

    GUI gui = GUI(800,600,desenha,teclado,mouse);
}


//while(true) {
//    desenha();
//    interacaoUsuario();
//}
