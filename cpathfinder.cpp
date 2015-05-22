#include "cpathfinder.h"

CPathFinder::CPathFinder(std::vector<CPoint> initialPoints):
    pointsCount(initialPoints.size()),points(initialPoints)
{
}

CPathFinder::~CPathFinder()
{

}

double CPathFinder::calculateDistance(CPoint first, CPoint second)
{
    return sqrt((first.x - second.x)*(first.x - second.x) + (first.y - second.y)*(first.y - second.y));
}

std::vector<CEdge> CPathFinder::getAllEdges()
{
    std::vector<CEdge> edges;
    for (size_t first = 0; first < pointsCount; ++first)
    {
        for (size_t second = first + 1; second < pointsCount; ++second)
        {
            edges.push_back(CEdge(first, second, calculateDistance(points[first], points[second])));
        }
    }
    return edges;
}

void CPathFinder::kruskalFindMST()
{
    std::vector<CEdge> edges = getAllEdges();
    std::sort(edges.begin(), edges.end());
    CDisjointSetUnion disjointSetUnion;
    disjointSetUnion.makeFullUnion(points.size());
    for (CEdge currentEdge : edges)
    {
        disjointSetUnion.printUnion();
        if (disjointSetUnion.find(currentEdge.firstVertex) != disjointSetUnion.find(currentEdge.secondVertex))
        {
            disjointSetUnion.unite(currentEdge.firstVertex, currentEdge.secondVertex);
            std::cout << currentEdge.firstVertex << ' ' << currentEdge.secondVertex << '\n';
        }
    }
}


void CPathFinder::findPath()
{
    kruskalFindMST();
}
