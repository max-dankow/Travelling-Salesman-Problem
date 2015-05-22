#include "cpathfinder.h"

CPathFinder::CPathFinder(const std::vector<CPoint> &initialPoints):
    pointsAmount(initialPoints.size()),points(initialPoints)
{
}

double CPathFinder::calculateDistance(const CPoint &first, const CPoint &second) const
{
    return sqrt((first.x - second.x)*(first.x - second.x) + (first.y - second.y)*(first.y - second.y));
}

std::vector<CEdge> CPathFinder::getAllEdges() const
{
    std::vector<CEdge> edges;
    for (size_t first = 0; first < pointsAmount; ++first)
    {
        for (size_t second = first + 1; second < pointsAmount; ++second)
        {
            edges.push_back(CEdge(first, second, calculateDistance(points[first], points[second])));
        }
    }
    return edges;
}

CGraph CPathFinder::kruskalFindMST() const
{
    std::vector<CEdge> edges = getAllEdges();
    std::sort(edges.begin(), edges.end());
    CDisjointSetUnion disjointSetUnion;
    disjointSetUnion.makeFullUnion(points.size());
    CGraph minimumSpanningTree(pointsAmount);
    for (CEdge currentEdge : edges)
    {
        if (disjointSetUnion.find(currentEdge.firstVertexIndex) != disjointSetUnion.find(currentEdge.secondVertexIndex))
        {
            minimumSpanningTree.addEdgeUndirected(currentEdge);
            disjointSetUnion.unite(currentEdge.firstVertexIndex, currentEdge.secondVertexIndex);
        }
    }
    return minimumSpanningTree;
}

void CPathFinder::findPath() const
{
    CGraph minimumSpanningTree = kruskalFindMST();
    std::vector<size_t> path = minimumSpanningTree.rebuildWay();
    std::cout << checkPath(path) << '\n';
}

double CPathFinder::checkPath(const std::vector<size_t> &path) const
{
    std::vector<bool> visited(pointsAmount, false);
    size_t visitedCount = 0;
    double sum = 0;
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i > 0)
        {
            //assert(calculateDistance(points[path[i]], points[path[i - 1]]) >= 0);
            sum = calculateDistance(points[path[i]], points[path[i - 1]]);
        }
        if (!visited[path[i]])
        {
            visited[path[i]] = true;
            visitedCount++;
        }
    }
    assert(visitedCount == pointsAmount);
    assert(*(path.begin()) == *(path.end() - 1));
    return sum;
}
