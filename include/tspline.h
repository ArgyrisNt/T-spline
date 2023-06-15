#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include "C:\Users\argir\T-spline\include\kVertex.h"

double basisRecur(double x, const std::vector<double>& knots, int deg, int knotspan);

class tspline
{
public:
    tspline() {}
    tspline(int _deg, std::vector<kVertex> &_kVertices) : len(_kVertices.size()), deg(_deg), kVertices(_kVertices) {}

    ~tspline() {}

    void updateKnotVecs();
    std::vector<double> evaluateInRange(int resolution, bool plot);
    std::vector<double> evaluate(double, double);
    double basisFunTSpl(double x, const std::vector<double>& knots, int knotspan);

    void printControlPts();
    void printPreImagePaper();
    //void calc_faces();
    //bool is_bound(kVertex);
    //void calc_Tjunctions();
    //void generate_extensions();

    int len;
    int deg;
    std::vector<kVertex> kVertices;

    //kVertex* fVertices;
    //std::vector<std::vector<double>> faces;
    //std::vector<int> Tjunctions;
    //int f_len;
};
