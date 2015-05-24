#ifndef CPATHFINDER_H
#define CPATHFINDER_H

#include <math.h>
#include <algorithm>
#include "cdisjointset.h"
#include "cgraph.h"

enum CAlgorithm
{
    kruskalMST = 0,
    bruteForce = 1
};

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
    std::vector<size_t> findPath(CAlgorithm alhorithm) const;
    double checkPath(const std::vector<size_t> &path) const;
private:
    size_t pointsAmount;
    std::vector<CPoint> points;
    double calculateDistance(const CPoint &first, const CPoint &second) const;
    std::vector<CEdge> getAllEdges() const;
    CGraph kruskalFindMST() const;
    void bruteForceSearch(std::vector<bool> &visited, std::vector<size_t> &way,
        double &wayLength, std::vector<size_t> &bestWay, double &bestWayLength) const;
};

#endif // CPATHFINDER_H
