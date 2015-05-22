#ifndef CPATHFINDER_H
#define CPATHFINDER_H

#include <math.h>
#include <algorithm>
#include "cdisjointset.h"
#include "cgraph.h"

struct CPoint
{
    CPoint(double new_x, double new_y):
        x(new_x), y(new_y){}
    double x, y;
};

class CPathFinder
{
public:
    CPathFinder(const std::vector<CPoint> &initialPoints);
    void findPath() const;
    double checkPath(const std::vector<size_t> &path) const;
private:
    size_t pointsAmount;
    std::vector<CPoint> points;
    double calculateDistance(const CPoint &first, const CPoint &second) const;
    std::vector<CEdge> getAllEdges() const;
    CGraph kruskalFindMST() const;
};

#endif // CPATHFINDER_H
