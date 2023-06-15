#include <iostream>
#include <vector>
#include "..\include\kVertex.h"

std::pair<double, kVertex*> kVertex::shootLeft(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.left)
    {
        curVert = startVert.left->end;
        p = startVert.s - curVert->s;
        return std::make_pair(p,curVert);
    }

    curVert = &startVert;
    while (!curVert->left)
    {
        if (!curVert->bottom) return std::make_pair(0.0,curVert);
        curVert = curVert->bottom->end;
    }

    curVert = curVert->left->end;
    while (!curVert->top)
        curVert = curVert->left->end;

    p = startVert.s - curVert->s;
    while (curVert->t < startVert.t)
    {
        if (!curVert->top) throw std::invalid_argument("Incosistent T-mesh");
        curVert = curVert->top->end;
    }

    return std::make_pair(p,curVert);
}

std::pair<double,kVertex*> kVertex::shootRight(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.right)
    {
        curVert = startVert.right->end;
        p = - startVert.s + curVert->s;
        return std::make_pair(p,curVert);
    }

    curVert = &startVert;
    while (!curVert->right)
    {
        if (!curVert->bottom) return std::make_pair(0.0,curVert);
        curVert = curVert->bottom->end;
    }

    curVert = curVert->right->end;
    while (!curVert->top)
        curVert = curVert->right->end;

    p = - startVert.s + curVert->s;
    curVert = curVert->top->end;
    while (curVert->t < startVert.t)
    {
        if (!curVert->top) throw std::invalid_argument("Incosistent T-mesh");
        curVert = curVert->top->end;
    }

    return std::make_pair(p,curVert);
}

std::pair<double,kVertex*> kVertex::shootTop(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.top)
    {
        curVert = startVert.top->end;
        p = - startVert.t + curVert->t;
        return std::make_pair(p,curVert);
    }

    curVert = &startVert;
    while (!curVert->top)
    {
        if (!curVert->left) return std::make_pair(0.0,curVert);
        curVert = curVert->left->end;
    }

    curVert = curVert->top->end;
    while (!curVert->right)
        curVert = curVert->top->end;

    p = - startVert.t + curVert->t;
    curVert = curVert->right->end;
    while (curVert->s < startVert.s)
    {
        if (!curVert->right) throw std::invalid_argument("Incosistent T-mesh");
        curVert = curVert->right->end;
    }

    return std::make_pair(p,curVert);
}

std::pair<double,kVertex*> kVertex::shootBottom(kVertex& startVert)
{
    kVertex* curVert;
    double p;
    if (startVert.bottom)
    {
        curVert = startVert.bottom->end;
        p = startVert.t - curVert->t;
        return std::make_pair(p,curVert);
    }

    curVert = &startVert;
    while (!curVert->bottom)
    {
        if (!curVert->left) return std::make_pair(0.0,curVert);
        curVert = curVert->left->end;
    }

    curVert = curVert->bottom->end;
    while (!curVert->right)
        curVert = curVert->bottom->end;

    p = startVert.t - curVert->t;
    curVert = curVert->right->end;
    while (curVert->s < startVert.s)
    {
        if (!curVert->right) throw std::invalid_argument("Incosistent T-mesh");
        curVert = curVert->right->end;
    }

    return std::make_pair(p,curVert);
}




std::pair<std::vector<double>,std::vector<double>> kVertex::getKnotVec(int deg)
{
    std::vector<double> knotsS, knotsT;
    int sCount = 0;

    if (deg % 2 == 0) sCount = deg / 2 + 1;
    else sCount = (deg + 1) / 2; knotsS = {s}; knotsT = {t};

    kVertex curVert(*this);
    double p, _s, _t;
    std::pair<double,kVertex*> my_pair;
    for (int i = 0; i < sCount; i++)
    {
        _s = curVert.s;
        my_pair = shootLeft(curVert);
        p = my_pair.first;
        curVert = *my_pair.second;
        _s = _s - p;
        knotsS.insert(knotsS.begin(), _s);
    }

    curVert = *this;
    for (int i = 0; i < sCount; i++)
    {
        _s = curVert.s;
        my_pair = shootRight(curVert);
        p = my_pair.first;
        curVert = *my_pair.second;
        _s = _s + p;
        knotsS.push_back(_s);
    }

    curVert = *this;
    for (int i = 0; i < sCount; i++)
    {
        _t = curVert.t;
        my_pair = shootBottom(curVert);
        p = my_pair.first;
        curVert = *my_pair.second;
        _t = _t - p;
        knotsT.insert(knotsT.begin(), _t);
    }

    curVert = *this;
    for (int i = 0; i < sCount; i++)
    {
        _t = curVert.t;
        my_pair = shootTop(curVert);
        p = my_pair.first;
        curVert = *my_pair.second;
        _t = _t + p;
        knotsT.push_back(_t);
    }

    return std::make_pair(knotsS,knotsT);
}

void kVertex::updateKnotVec(int deg)
{
    knotVec = getKnotVec(deg);
}




void kVertex::print_knotVec()
{
    std::cout << "knotsS: ";
    for (int i = 0; i < knotVec.first.size(); i++) std::cout << knotVec.first[i] << " ";

    std::cout << "\nknotsT: ";
    for (int i = 0; i < knotVec.second.size(); i++) std::cout << knotVec.second[i] << " ";
    std::cout << "\n\n";
}

void kVertex::print()
{
    std::cout << "(" << s << ", " << t << ")\n";
    if (top) std::cout << "top: (" << top->end->s << ", " << top->end->t << ")\n";
    if (bottom) std::cout << "bottom: (" << bottom->end->s << ", " << bottom->end->t << ")\n";
    if (left) std::cout << "left: (" << left->end->s << ", " << left->end->t << ")\n";
    if (right) std::cout << "right: (" << right->end->s << ", " << right->end->t << ")\n";

    print_knotVec();
}