#include "cpathfinder.h"

CPathFinder::CPathFinder(const std::vector<CPoint> &initialPoints):
    pointsAmount(initialPoints.size()),points(initialPoints)
{
}

double CPathFinder::calculateDistance(const CPoint &first, const CPoint &second) const
{
    return sqrt((first.x - second.x)*(first.x - second.x) +
                (first.y - second.y)*(first.y - second.y));
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

void CPathFinder::bruteForceSearch(std::vector<bool> &visited, std::vector<size_t> &way,
    double &wayLength, std::vector<size_t> &bestWay, double &bestWayLength) const
{
    if (way.size() == pointsAmount)
    {
        way.push_back(way[0]);
        double wayLength = checkPath(way);
        if (wayLength < bestWayLength || bestWayLength < 0)
        {
            bestWay = way;
            bestWayLength = wayLength;
        }
        way.pop_back();
    }
    else
    {
        for (size_t i = 0; i < pointsAmount; ++i)
        {
            if (!visited[i])
            {
                double newLength = 0;
                if (!way.empty())
                {
                    newLength = wayLength + calculateDistance(points[*(way.end() - 1)], points[i]);
                }
                if (newLength >= bestWayLength && bestWayLength >= 0)
                {
                    continue;
                }
                visited[i] = true;
                way.push_back(i);
                bruteForceSearch(visited, way, newLength, bestWay, bestWayLength);
                way.pop_back();
                visited[i] = false;
            }
        }
    }
}

std::vector<size_t> CPathFinder::findPath(CAlgorithm alhorithm) const
{
    std::vector<size_t> path;
    path.reserve(pointsAmount);
    switch (alhorithm)
    {
        case kruskalMST:
        {
            CGraph minimumSpanningTree = kruskalFindMST();
            path = minimumSpanningTree.rebuildWay();
            break;
        }
        case bruteForce:
        {
            std::vector<bool> visited(pointsAmount, false);
            std::vector<size_t> way;
            way.reserve(pointsAmount);
            double bestLength = -1;
            double currentLength = 0;
            bruteForceSearch(visited, way, currentLength, path, bestLength);
            break;
        }
        default:
            assert(false);
    }
    std::cout << "Length is " << checkPath(path) << '\n';
    return path;
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
            sum += calculateDistance(points[path[i]], points[path[i - 1]]);
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
