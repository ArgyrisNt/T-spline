#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include "C:\Users\argir\T-spline\include\kVertex.h"

class tspline
{
public:
    // Constructors
    tspline();
    tspline(int, int);

    // Destructor
    ~tspline() {}

    // Member functions
    void updateKnotVecs();
    std::vector<double> evaluate(double, double);
    void printControlPts(bool);
    void printPreImagePaper(bool);
    void print();
    void calc_faces();
    bool is_bound(kVertex);
    void calc_Tjunctions();
    void generate_extensions();

    kVertex* kVertices;
    kVertex* fVertices;
    int deg;
    std::vector<std::vector<double>> faces;
    std::vector<int> Tjunctions;
    int f_len;

private:
    int len;
};

// i.e.
// std::vector<double> temp{0.0,0.0,0.0,1.0,2.0,3.0,3.0,3.0};
// double N0 = basisRecur(2.0, temp, 2, 0);
// double N1 = basisRecur(2.0, temp, 2, 1);
// double N2 = basisRecur(2.0, temp, 2, 2);
// double N3 = basisRecur(2.0, temp, 2, 3);
// double N4 = basisRecur(2.0, temp, 2, 4);
// std::cout << N0 << "\n" << N1 << "\n" << N2 << "\n" << N3 << "\n" << N4 << std::endl;
double basisRecur(double x, std::vector<double> knots, int deg, int knotspan)
{
    double N;
    if (deg == 0)
    {
        if ((x >= knots[knotspan]) && (x < knots[knotspan + 1]))
        {
            N = 1.0;
        }
        else
        {
            N = 0.0;
        }
    }
    else
    {
        double a = 0.0;
        double b = 0.0;

        double ad = knots[knotspan + deg] - knots[knotspan];
        if (ad > 1e-7)
        {
            a = ((x - knots[knotspan]) / ad) * basisRecur(x,knots,deg-1,knotspan);
        }

        double bd = knots[knotspan + deg + 1] - knots[knotspan + 1];
        if (bd > 1e-7)
        {
            b = ((knots[knotspan+deg+1] - x) / bd) * basisRecur(x, knots, deg-1, knotspan + 1);
        }

        N = a + b;
    }

    return N;
} 

double basisFunTSpl(double x, std::vector<double> knots, int deg, int knotspan)
{
    double N;
    bool eq;
    if (x == knots[0])
    {
        eq = true;
        for (int i = 0; i < deg - 1; i++)
        {
            if (knots[i] != knots[i+1])
            {
                eq = false;
            }
        }
        if (eq)
        {
            N = 1.0;
            return N;
        }
    }

    if (x == knots[knots.size()-1])
    {
        eq = true;
        for (int i = knots.size() - deg + 1; i < knots.size() - 1; i++)
        {
            if (knots[i] != knots[i+1])
            {
                eq = false;
            }
        }
        if (eq)
        {
            N = 1.0;
            return N;
        }
    }

    N = basisRecur(x, knots, deg, knotspan);
    
    return N;
}

void plot(std::string filename)
{
    ShellExecute(GetDesktopWindow(), "open", filename.c_str(), NULL, NULL, SW_SHOWNORMAL);
}