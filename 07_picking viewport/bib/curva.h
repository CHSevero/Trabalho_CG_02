#ifndef CURVA_H
#define CURVA_H
#include<bits/stdc++.h>
#include<Vetor3D.h>
#include<gui.h>
#include<cubo.h>
#include<ship.h>
#include<Camera.h>
#include<CameraJogo.h>
using namespace std;

class Curva
{
public:
    int ic =0;
    double u =0;

    Ship *ship = new Ship();
    Cubo *c = new Cubo();
    Curva();
    vector<vector<double>> Interpoladora = {
        {-4.5, 13.5, -13.5, 4.5},
        {9, -22.5, 18, -4.5},
        {-5.5, 9, -4.5, 1},
        {1, 0, 0, 0}
    };

    vector<vector<double>> Hermite = {
        {2, -2, 1, 1},
        {-3, 3, -2, -1},
        {0, 0, 1, 0},
        {1, 0, 0, 0}
    };
    vector<vector<double>> Bezier = {
        {-1, 3, -3, 1},
        {3, -6, 3, 0},
        {-3, 3, 0, 0},
        {1, 0, 0, 0}
    };
    vector<vector<double>> CatmullRom = {
        {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
        {2/2.0, -5/2.0, 4/2.0, -1/2.0},
        {-1/2.0, 0.0, 1/2.0, 0.0},
        {0.0, 2/2.0, 0.0, 0.0}
    };
    vector<vector<double>> Bspline = {
        {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
        {3/6.0, -6/6.0, 3/6.0, 0},
        {-3/6.0, 0, 3/6.0, 0},
        {1/6.0, 4/6.0, 1/6.0, 0}
    };

    vector<vector<double>> Matriz = Interpoladora;
    Vetor3D pt(double u, vector<Vetor3D> pontos, int op);

    void desenhaCurva(vector<Vetor3D> pontos, double delta_u);
    void desenhaShip(vector<Vetor3D> pontos, double delta_u, CameraJogo *camera);
};

#endif // CURVA_H
