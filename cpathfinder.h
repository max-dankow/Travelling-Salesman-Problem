#ifndef CPATHFINDER_H
#define CPATHFINDER_H

#include <math.h>
#include <algorithm>
#include "cdisjointset.h"

struct CPoint
{
    CPoint(double new_x, double new_y):
        x(new_x), y(new_y){}
    double x, y;
};

struct CEdge
{
    CEdge(size_t newFirstVertex, size_t newSecondVertex, double newWeight):
        firstVertex(newFirstVertex),secondVertex(newSecondVertex), weight(newWeight){}
    bool operator <(const CEdge &other) const
    {
        return weight < other.weight;
    }
    size_t firstVertex, secondVertex;
    double weight;
};

class CPathFinder
{
public:
    CPathFinder(std::vector<CPoint> initialPoints);
    ~CPathFinder();
    void findPath();
private:
    size_t pointsCount;
    std::vector<CPoint> points;
    double calculateDistance(CPoint first, CPoint second);
    std::vector<CEdge> getAllEdges();
    void kruskalFindMST();
};

#endif // CPATHFINDER_H
