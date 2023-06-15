#ifndef H_KVERTEX
#define H_KVERTEX

#include "hEdge.h"

class kVertex
{
public:
    kVertex() : s(0.0), t(0.0), top(nullptr), right(nullptr), bottom(nullptr), left(nullptr) {}
    kVertex(double _s, double _t) : s(_s), t(_t), top(nullptr), right(nullptr), bottom(nullptr), left(nullptr) {}
    kVertex(double _s, double _t, std::pair<std::vector<double>, std::vector<double>>& _knotVec) 
        : s(_s), t(_t), top(nullptr), right(nullptr), bottom(nullptr), left(nullptr), knotVec(_knotVec) {}
    kVertex(const kVertex& v)
    { s = v.s; t = v.t; top = v.top; right = v.right; bottom = v.bottom; left = v.left; knotVec = v.knotVec; cPoint = v.cPoint; }

    ~kVertex() {}

    kVertex& operator=(const kVertex& v)
    { s = v.s; t = v.t; top = v.top; right = v.right; bottom = v.bottom; left = v.left; knotVec = v.knotVec; cPoint = v.cPoint; return *this;}

    void cnctTop(kVertex &v) { top = new hEdge(this, &v); }
    void cnctRight(kVertex &v) { right = new hEdge(this, &v); }
    void cnctBottom(kVertex &v) { bottom = new hEdge(this, &v); }
    void cnctLeft(kVertex &v) { left = new hEdge(this, &v); }

    void updateKnotVec(int deg);
    std::pair<std::vector<double>, std::vector<double>> getKnotVec(int deg);
    std::pair<double, kVertex*> shootLeft(kVertex& startVert);
    std::pair<double, kVertex*> shootRight(kVertex& startVert);
    std::pair<double, kVertex*> shootTop(kVertex& startVert);
    std::pair<double, kVertex*> shootBottom(kVertex& startVert);

    void print();
    void print_knotVec();

    double s, t;
    hEdge *top, *right, *bottom, *left;
    std::pair<std::vector<double>, std::vector<double>> knotVec;
    std::vector<double> cPoint;
};

#include "../src/kVertex.cpp"

#endif