#include <random>
#include "cpathfinder.h"
#include "cgraph.h"
#include <unistd.h>
#include "Drawer.h"
//модуль Drawer реализован Александром Лактионовым, за что ему огромное спасибо)

const double SIGMA_CENTERS = 100;
const double SIGMA_POINTS = 10;
const size_t CENTERS_AMOUNT = 100;
const size_t POINTS_PER_CENTER = 100;

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

std::vector<std::pair<int, int>> pathToEdges(const std::vector<size_t> &path)
{
    std::vector<std::pair<int, int>> edges;
    for (size_t i = 1; i < path.size(); ++i)
    {
        edges.push_back(std::make_pair(path[i - 1], path[i]));
    }
    edges.push_back(std::make_pair(path[0], path[path.size() - 1]));
    return edges;
}

void demonstrateAllAlgorithms(size_t pointsAmount)
{
    std::vector<CPoint> points = generatePoints(pointsAmount, CPoint(0, 0), 100);
  //конвертируем сгенерированные точки в вид, необходимый для визулизации в Drawer
    std::vector<std::pair<double, double>> pairPoints;
    for (CPoint p : points)
    {
        pairPoints.push_back(std::make_pair(p.x, p.y));
    }
    int size = pairPoints.size();
    CPathFinder solver(points);
  //разделяемся на три потока
    if (fork() == 0)
    {
      //(1) - полный перебор
        if (points.size() < 15)
        {
            std::vector<size_t> path = solver.findPath(bruteForce);
            std::vector<std::pair<int, int>> edges = pathToEdges(path);
            AnswerVisualizer(pairPoints, edges, size);
        }
    }
    else
    {
        if (fork() == 0)
        {
          //(2) - главный алгоритм, основанный на минимальном остовном дереве
            std::vector<size_t> path = solver.findPath(kruskalMST);
            std::vector<std::pair<int, int>> edges = pathToEdges(path);
            AnswerVisualizer(pairPoints, edges, size);
        }
        else
        {
          //(3) - (чисто для сравнения) проходит все вершины в порядке их нумерации
            std::vector<std::pair<int, int> > edges;
            edges.push_back(std::make_pair(0, points.size() - 1));
            for (size_t i = 1; i < points.size(); ++i)
            {
                edges.push_back(std::make_pair(i - 1, i));
            }
            AnswerVisualizer(pairPoints, edges, size);
        }
    }
}

void runSolution()
{
  //генерируем произвольные центры и поизвольные точки вокруг них
    std::vector<CPoint> centers = generatePoints(CENTERS_AMOUNT, CPoint(0, 0), SIGMA_CENTERS);
    std::vector<CPoint> points;
    for (CPoint singleCenter : centers)
    {
      std::vector<CPoint> newPoints = generatePoints(POINTS_PER_CENTER, singleCenter, SIGMA_POINTS);
      points.insert(points.end(), newPoints.begin(), newPoints.end());
    }
    CPathFinder solver(points);
    std::vector<size_t> path = solver.findPath(kruskalMST);
    for (size_t index : path)
    {
        std::cout << index << '\n';
    }
}

int main()
{
    //demonstrateAllAlgorithms(10);
    runSolution();
    return 0;
}
