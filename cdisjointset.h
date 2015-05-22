#ifndef DISJOINTSETDATASTRUCTURE_H
#define DISJOINTSETDATASTRUCTURE_H

#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <random>

static std::default_random_engine randomGenerator;

class CDisjointSetUnion
{
public:
    void makeSet(size_t element);
    void makeFullUnion(size_t size);
    void printUnion();
    size_t find(size_t element);
    void unite(size_t firstMember, size_t secondMember);
private:
    size_t elementsAmount;
    std::vector<size_t> parents;
};

#endif // DISJOINTSETDATASTRUCTURE_H
