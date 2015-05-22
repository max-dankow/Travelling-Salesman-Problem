#include <random>
#include "cpathfinder.h"
#include "cgraph.h"

std::vector<CPoint> generatePoints(size_t pointsAmount, CPoint centerPoint, double deviation)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::normal_distribution<> x(centerPoint.x, deviation);
    std::normal_distribution<> y(centerPoint.y, deviation);
    std::vector<CPoint> points;
    for (size_t i = 0; i < pointsAmount; ++i)
    {
        points.push_back(CPoint(x(generator), y(generator)));
    }
    return points;
}

int main()
{
    while (1)
    {
    std::vector<CPoint> points = generatePoints(100, CPoint(0, 0), 100);
    for (CPoint singlePoint : points)
    {
        std::cout << singlePoint.x << ' ' << singlePoint.y << '\n';
    }
    CPathFinder solver(points);
    solver.findPath();
    getchar();
    }
}
