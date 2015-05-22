#include "cdisjointset.h"

CDisjointSetUnion::CDisjointSetUnion()
{

}

CDisjointSetUnion::~CDisjointSetUnion()
{

}

void CDisjointSetUnion::makeSet(size_t element)
{
    assert(element < element_count);
    parents[element] = element;
}

void CDisjointSetUnion::makeFullUnion(size_t size)
{
    parents.resize(size);
    element_count = size;
    for (int number = 0; number < size; ++number)
    {
        makeSet(number);
    }
}

size_t CDisjointSetUnion::find(size_t element)
{
    if (parents[element] != element)
    {
        parents[element] = find(parents[element]);
    }
    return parents[element];
}

void CDisjointSetUnion::unite(size_t firstMember, size_t secondMember)
{
    size_t firstRoot = find(firstMember);
    size_t secondRoot = find(secondMember);
    std::uniform_int_distribution<int> randomSubTree(0, 1);
    if (randomSubTree(randomGenerator) == 0)
    {
        std::swap(firstRoot, secondRoot);
    }
    parents[firstRoot] = secondRoot;
}

void CDisjointSetUnion::printUnion()
{
    for (size_t element = 0; element < element_count; ++element)
    {
        std::cout << element << '(' << find(element) << ')' << '\n';
    }
}

