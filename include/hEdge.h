#ifndef H_HEDHE
#define H_HEDHE

#include <iostream>
#include <vector>
#include "kVertex.h"

struct kVertex;

struct hEdge
{
    hEdge() : start(nullptr), end(nullptr) {}
    hEdge(kVertex* _start, kVertex* _end) : start(_start), end(_end) {}
    kVertex *start, *end;
};

#endif