#pragma once

#include <iostream>
#include <vector>

class kVertex
{
public:
    // Constructors
    kVertex();
    kVertex(double, double);
    kVertex(double, double, std::pair<std::vector<double>,std::vector<double>>&);
    kVertex(kVertex&);

    // Destructor
    ~kVertex() {}

    // Overload operators
    kVertex& operator=(kVertex&);

    // Member functions
    std::pair<double,kVertex*> shootLeft(kVertex&);
    std::pair<double,kVertex*> shootRight(kVertex&);
    std::pair<double,kVertex*> shootTop(kVertex&);
    std::pair<double,kVertex*> shootBottom(kVertex&);
    std::pair<std::vector<double>,std::vector<double>> getKnotVec(int);
    void updateKnotVec(int);
    void print_knotVec();
    void print();
    
    // Member variables
    double _s;
    double _t;
    kVertex* top_start = NULL;
    kVertex* top_end = NULL;
    kVertex* right_start = NULL;
    kVertex* right_end = NULL;
    kVertex* bottom_start = NULL;
    kVertex* bottom_end = NULL;
    kVertex* left_start = NULL;
    kVertex* left_end = NULL;
    std::pair<std::vector<double>,std::vector<double>> knotVec;
    std::vector<double> cPoint{0.0,0.0,0.0};
};