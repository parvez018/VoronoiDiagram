#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <cstdlib>
#include <ctime>
#include "pcustomtypes.h"
class QuickHull
{
private:
    //double getMinAreaRect();
    double distBetnPoints(Point3 a, Point3 b);
    bool atRightSideOfNormal(Point3 a, Point3 b, Point3 target);
    bool isOnRightSide(Point3 a, Point3 b, Point3 target);
    static double calcNormalDist(Point3 a, Point3 b, Point3 target);
    std::vector<Point3> quickHullNr(std::vector<Point3> linkedList);
    std::vector<Point3> quickHullRcrsv(Point3 a, Point3 b, std::vector<Point3> linkedList);
    void initPoints();
    void drawPoints();
    void drawEdges();
public:
    int totalPoint;
    std::vector<Point3> points,resultPoints;
    QuickHull();
    QuickHull(std::vector<Point3> iPoints);
    void draw();
};

QuickHull::QuickHull()
{
    totalPoint=500;
    initPoints();
    //getMinAreaRect();
}
QuickHull::QuickHull(std::vector<Point3> iPoints)
{
    int maxRangeX = 860;
    int maxRangeY = 560;
    srand (time(NULL));

    std::vector<Point3> linkedList;
    for (int i = 0; i < iPoints.size(); i++)
    {
        //int m=rand() % maxRangeX-(maxRangeX/2);
        //int n=rand() % maxRangeY-(maxRangeY/2);
        points.push_back(iPoints[i]);
        linkedList.push_back(points[i]);
        //printf("point[%d]>>> x=%lf,y=%lf\n", i, points[i].x, points[i].y);
    }
    linkedList = quickHullNr(linkedList);
    int s = linkedList.size();
    //resultPoints = new Point3[s];
    Point3 tmp;
    for (int i = 0; i < s; i++)
    {
        resultPoints.push_back(tmp);
        resultPoints[i] = linkedList[i];
        //printf("%lf,%lf\n",resultPoints[i].x,resultPoints[i].y);
    }
}

bool QuickHull:: isOnRightSide(Point3 a, Point3 b, Point3 target)
{

    //cross product,negative result indicate position on right side due to clockwise rotation
    double m = b.x - a.x;
    double n = b.y - a.y;
    double u = target.x - a.x;
    double v = target.y - a.y;

    double ans = n * u - m * v;//(m)*(v)-(n)*(u);
    if (ans < 0) return true;
    else return false;
}

double QuickHull:: calcNormalDist(Point3 a, Point3 b, Point3 target)
{
    double m = b.x - a.x;
    double n = b.y - a.y;
    double u = target.x - a.x;
    double v = target.y - a.y;

    double ans = n * u - m * v;
    return abs(ans / sqrt(pow(m, 2) + pow(n, 2)));
}

std::vector<Point3> QuickHull:: quickHullNr(std::vector<Point3> linkedList)
{
    int limit = linkedList.size();
    Point3 rightLow = linkedList[0], leftHigh = linkedList[1];
    Point3 p;
    for (int i = 0; i < limit; i++)
    {
        p = linkedList[i];
        if (p.x < leftHigh.x || (p.x == leftHigh.x && p.y > leftHigh.y))
        {
            leftHigh = p;
        }
        if (p.x > rightLow.x || (p.x == rightLow.x && p.y < leftHigh.y))
        {
            rightLow = p;
        }
    }
    std::vector<Point3> resultSet;// = new std::vector<Point3>();
    std::vector<Point3> tempSet;
    std::vector<Point3> leftSet;// = new std::vector<Point3>();
    std::vector<Point3> rightSet;// = new std::vector<Point3>();
    //std::vector<Point3> resultSet=new std::vector<Point3>();
    for (int i = 0; i < limit; i++)
    {
        if (isOnRightSide(rightLow, leftHigh, linkedList[i]))
        {
            leftSet.push_back(linkedList[i]);
        }
        else if (isOnRightSide(leftHigh, rightLow, linkedList[i]))
        {
            rightSet.push_back(linkedList[i]);
        }
    }

    //System.out.printf("left %d,right %d\n", leftSet.size(), rightSet.size());
    resultSet.push_back(rightLow);
    tempSet = quickHullRcrsv(rightLow, leftHigh, leftSet);
    limit = tempSet.size();
    for (int i = 0; i < limit; i++)
    {
        resultSet.push_back(tempSet[i]);
    }
    resultSet.push_back(leftHigh);
    tempSet = quickHullRcrsv(leftHigh, rightLow, rightSet);
    limit = tempSet.size();
    for (int i = 0; i < limit; i++)
    {
        resultSet.push_back(tempSet[i]);
    }
    return resultSet;
}

std::vector<Point3> QuickHull:: quickHullRcrsv(Point3 a, Point3 b, std::vector<Point3> linkedList)
{
    int limit = linkedList.size();
    if (limit == 0) return linkedList;

    double maxDistance = -1;
    int maxDistPoint3Index = -1;
    double dist;
    for (int i = 0; i < limit; i++)
    {
        dist = calcNormalDist(a, b, linkedList[i]);
        if (dist > maxDistance)
        {
            maxDistance = dist;
            maxDistPoint3Index = i;
        }
    }
    Point3 p = linkedList[maxDistPoint3Index];
    std::vector<Point3> leftSet;// = new std::vector<Point3>();
    std::vector<Point3> rightSet;// = new std::vector<Point3>();
    std::vector<Point3> resultSet;// = new std::vector<Point3>();
    for (int i = 0; i < limit; i++)
    {
        if (isOnRightSide(a, p, linkedList[i]))
        {
            leftSet.push_back(linkedList[i]);
        }
        else if (isOnRightSide(p, b, linkedList[i]))
        {
            rightSet.push_back(linkedList[i]);
        }
    }
    leftSet = quickHullRcrsv(a, p, leftSet);
    rightSet = quickHullRcrsv(p, b, rightSet);

    resultSet = leftSet;
    resultSet.push_back(p);
    limit = rightSet.size();
    for (int i = 0; i < limit; i++)
    {
        resultSet.push_back(rightSet[i]);
    }
    return resultSet;
}
/*
void testing()
{
    double d = calcNormalDist(Point3(1, 2), Point3(5, 6), Point3(3, 3));
    System.out.printf("dist %f\n", d);
}
*/
void QuickHull:: initPoints()
{

    int maxRangeX = 860;
    int maxRangeY = 560;
    srand (time(NULL));
    //points = new Point3[totalPoint3s];
    std::vector<Point3> linkedList;// = new std::vector<Point3>();
    for (int i = 0; i < totalPoint; i++)
    {
        int m=rand() % maxRangeX-(maxRangeX/2);
        int n=rand() % maxRangeY-(maxRangeY/2);
        points.push_back(Point3(m, n));
        linkedList.push_back(points[i]);
        //printf("point[%d]>>> x=%lf,y=%lf\n", i, points[i].x, points[i].y);
    }
    linkedList = quickHullNr(linkedList);
    int s = linkedList.size();
    //resultPoints = new Point3[s];
    Point3 tmp;
    for (int i = 0; i < s; i++)
    {
        resultPoints.push_back(tmp);
        resultPoints[i] = linkedList[i];
        printf("%lf,%lf\n",resultPoints[i].x,resultPoints[i].y);
    }
}
void QuickHull::drawPoints()
{
    glColor3f(1,0,0);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        for(int i=0;i<points.size();i++)
        {
            glVertex2f(points[i].x,points[i].y);
        }
    }
    glEnd();
}
void QuickHull::drawEdges()
{
    int limit=resultPoints.size()-1;
    for(int i=0;i<limit;i++)
    {
        glBegin(GL_LINES);
        {
            glVertex2f(resultPoints[i].x,resultPoints[i].y);
            glVertex2f(resultPoints[i+1].x,resultPoints[i+1].y);
        }
        glEnd();
    }
    glBegin(GL_LINES);
    {
        glVertex2f(resultPoints[0].x,resultPoints[0].y);
        glVertex2f(resultPoints[limit].x,resultPoints[limit].y);
    }
    glEnd();
}
void QuickHull::draw()
{
    drawPoints();
    drawEdges();
}

#endif // QUICKHULL_H
