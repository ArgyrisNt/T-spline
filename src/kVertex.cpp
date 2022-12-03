#include <iostream>
#include <vector>
#include "C:\Users\argir\T-spline\include\kVertex.h"

kVertex::kVertex()
{
    _s = 0.0;
    _t = 0.0;
}

kVertex::kVertex(double s, double t)
{
    _s = s;
    _t = t;
}

kVertex::kVertex(double s, double t, std::pair<std::vector<double>,std::vector<double>>& vec)
{
    _s = s;
    _t = t;
    knotVec = vec;
}

kVertex::kVertex(kVertex& old)
{
    _s = old._s;
    _t = old._t;
    knotVec = old.knotVec;
    cPoint = old.cPoint;
    top_start = old.top_start;
    top_end = old.top_end;
    right_start = old.right_start;
    right_end = old.right_end;
    bottom_start = old.bottom_start;
    bottom_end = old.bottom_end;
    left_start = old.left_start;
    left_end = old.left_end;
}

kVertex& kVertex::operator=(kVertex& old)
{
    _s = old._s;
    _t = old._t;
    knotVec = old.knotVec;
    cPoint = old.cPoint;
    top_start = old.top_start;
    top_end = old.top_end;
    right_start = old.right_start;
    right_end = old.right_end;
    bottom_start = old.bottom_start;
    bottom_end = old.bottom_end;
    left_start = old.left_start;
    left_end = old.left_end;

    return *this;
}

std::pair<double,kVertex*> kVertex::shootLeft(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.left_end)
    {
        curVert = startVert.left_end;
        p = startVert._s - curVert->_s;
        return std::make_pair(p,curVert);
    }
    curVert = &startVert;
    while (!curVert->left_end)
    {
        if (!curVert->bottom_end)
        {
            p = 0.0;
            return std::make_pair(p,curVert);
        }
        curVert = curVert->bottom_end;
    }
    curVert = curVert->left_end;
    while (!curVert->top_end)
    {
        curVert = curVert->left_end;
    }
    p = startVert._s - curVert->_s;
    while (curVert->_t < startVert._t)
    {
        if (!curVert->top_end)
        {
            std::cout << "\nIncosistent T-mesh\n";
            throw std::invalid_argument("Incosistent T-mesh");
        }
        curVert = curVert->top_end;
    }

    return std::make_pair(p,curVert);
}

std::pair<double,kVertex*> kVertex::shootRight(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.right_end)
    {
        curVert = startVert.right_end;
        p = - startVert._s + curVert->_s;
        return std::make_pair(p,curVert);
    }
    curVert = &startVert;
    while (!curVert->right_end)
    {
        if (!curVert->bottom_end)
        {
            p = 0.0;
            return std::make_pair(p,curVert);
        }
        curVert = curVert->bottom_end;
    }
    curVert = curVert->right_end;
    while (!curVert->top_end)
    {
        curVert = curVert->right_end;
    }
    p = - startVert._s + curVert->_s;
    curVert = curVert->top_end;
    while (curVert->_t < startVert._t)
    {
        if (!curVert->top_end)
        {
            std::cout << "\nIncosistent T-mesh\n";
            throw std::invalid_argument("Incosistent T-mesh");
        }
        curVert = curVert->top_end;
    }

    return std::make_pair(p,curVert);
}

std::pair<double,kVertex*> kVertex::shootTop(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.top_end)
    {
        curVert = startVert.top_end;
        p = - startVert._t + curVert->_t;
        return std::make_pair(p,curVert);
    }
    curVert = &startVert;
    while (!curVert->top_end)
    {
        if (!curVert->left_end)
        {
            p = 0.0;
            return std::make_pair(p,curVert);
        }
        curVert = curVert->left_end;
    }
    curVert = curVert->top_end;
    while (!curVert->right_end)
    {
        curVert = curVert->top_end;
    }
    p = - startVert._t + curVert->_t;
    curVert = curVert->right_end;
    while (curVert->_s < startVert._s)
    {
        if (!curVert->right_end)
        {
            std::cout << "\nIncosistent T-mesh\n";
            throw std::invalid_argument("Incosistent T-mesh");
        }
        curVert = curVert->right_end;
    }

    return std::make_pair(p,curVert);
}

std::pair<double,kVertex*> kVertex::shootBottom(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.bottom_end)
    {
        curVert = startVert.bottom_end;
        p = startVert._t - curVert->_t;
        return std::make_pair(p,curVert);
    }
    curVert = &startVert;
    while (!curVert->bottom_end)
    {
        if (!curVert->left_end)
        {
            p = 0.0;
            return std::make_pair(p,curVert);
        }
        curVert = curVert->left_end;
    }
    curVert = curVert->bottom_end;
    while (!curVert->right_end)
    {
        curVert = curVert->bottom_end;
    }
    p = startVert._t - curVert->_t;
    curVert = curVert->right_end;
    while (curVert->_s < startVert._s)
    {
        if (!curVert->right_end)
        {
            std::cout << "\nIncosistent T-mesh\n";
            throw std::invalid_argument("Incosistent T-mesh");
        }
        curVert = curVert->right_end;
    }

    return std::make_pair(p,curVert);
}

std::pair<std::vector<double>,std::vector<double>> kVertex::getKnotVec(int deg)
{
    std::vector<double> knotsS;
    std::vector<double> knotsT;
    int sCount = 0;
    if (deg % 2 == 0)
    {
        sCount = deg / 2 + 1;
    }
    else
    {
        sCount = (deg + 1) / 2;
        knotsS = {_s};
        knotsT = {_t};
    }

    kVertex curVert1(*this);
    double p;
    double s, t;
    std::pair<double,kVertex*> my_pair;
    for (int i = 0; i < sCount; i++)
    {
        s = curVert1._s;
        my_pair = shootLeft(curVert1);
        p = my_pair.first;
        curVert1 = *my_pair.second;
        s = s - p;
        knotsS.insert(knotsS.begin(),s);
    }

    kVertex curVert2(*this);
    for (int i = 0; i < sCount; i++)
    {
        s = curVert2._s;
        my_pair = shootRight(curVert2);
        p = my_pair.first;
        curVert2 = *my_pair.second;
        s = s + p;
        knotsS.push_back(s);
    }

    kVertex curVert3(*this);
    for (int i = 0; i < sCount; i++)
    {
        t = curVert3._t;
        my_pair = shootBottom(curVert3);
        p = my_pair.first;
        curVert3 = *my_pair.second;
        t = t - p;
        knotsT.insert(knotsT.begin(),t);
    }

    kVertex curVert4(*this);
    for (int i = 0; i < sCount; i++)
    {
        t = curVert4._t;
        my_pair = shootTop(curVert4);
        p = my_pair.first;
        curVert4 = *my_pair.second;
        t = t + p;
        knotsT.push_back(t);
    }

    return std::make_pair(knotsS,knotsT);
}

void kVertex::updateKnotVec(int deg)
{
    knotVec = getKnotVec(deg);
}

void kVertex::print_knotVec()
{
    std::cout << "\nknotsS: ";
    for (int i = 0; i < knotVec.first.size(); i++)
    {
        std::cout << knotVec.first[i] << " ";
    }
    std::cout << "\nknotsT: ";
    for (int i = 0; i < knotVec.second.size(); i++)
    {
        std::cout << knotVec.second[i] << " ";
    }
    std::cout << "\n\n";
}

void kVertex::print()
{
    std::cout << "s: " << _s;
    std::cout << "\nt: " << _t;
    if (top_end)
    {
        std::cout << "\ntop_end_s: " << top_end->_s;
        std::cout << "\ntop_end_t: " << top_end->_t;
    }
    if (bottom_end)
    {
        std::cout << "\nbottom_end_s: " << bottom_end->_s;
        std::cout << "\nbottom_end_t: " << bottom_end->_t;
    }
    if (left_end)
    {
        std::cout << "\nleft_end_s: " << left_end->_s;
        std::cout << "\nleft_end_t: " << left_end->_t;
    }
    if (right_end)
    {
        std::cout << "\nright_end_s: " << right_end->_s;
        std::cout << "\nright_end_t: " << right_end->_t;
    }
    print_knotVec();
}