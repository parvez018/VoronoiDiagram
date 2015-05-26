#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

#include <cmath>
#include "points.h"
struct Vector3
{
    double x;
    double y;
    double z;

    Vector3() {}
    Vector3(Point3 s,Point3 e)
    {
        x=e.x-s.x;
        y=e.y-s.y;
        z=e.z-s.z;
    }
    Vector3(double a, double b, double c)
    {
        x=a;
        y=b;
        z=c;
    }

    void set(double a, double b, double c)
    {
        x=a;
        y=b;
        z=c;
    }
    void set(Vector3 a)
    {
        x=a.x;
        y=a.y;
        z=a.z;
    }
    Vector3 operator-()
    {
        Vector3 a(-x,-y,-z);
        return a;
    }
    double dot(Vector3 a);//prototype
    Vector3 cross(Vector3 a);//prototype
    double zcross(Vector3 a);//prototype
    void normalize();//prototype
};
typedef Vector3 Vector3;
double Vector3 :: dot(Vector3 a)
{
    return (x*a.x + y*a.y + z*a.z);

}

double Vector3:: zcross(Vector3 a)
{
    return x*a.y-y*a.x;
}
Vector3 Vector3:: cross(Vector3 a)
{
    a.set(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x);
    return a;
}
void Vector3:: normalize()
{
    double d=sqrt(x*x+y*y+z*z);
    this->set(x/d,y/d,z/d);
}

struct Vertex
{
    int index;
    double x;
    double y;
    Vertex() {}
    Vertex(int i,double a, double b)
    {
        index=i;
        x=a;
        y=b;
    }
    Vertex(double a, double b)
    {
        index=-1;
        x=a;
        y=b;
    }
    bool operator()(const Vertex &t1, const Vertex &t2) const
    {
        if(t1.y==t2.y)return t1.x>t2.x;
        return t1.y<t2.y;
    }
    bool operator>(const Vertex &t1)
    {
        if(t1.y==y)return t1.x>x;
        return t1.y<y;
    }
    bool operator<(const Vertex &t1)
    {
        if(t1.y==y)return t1.x<x;
        return t1.y>y;
    }
};
typedef Vertex Vertex;



struct Edges
{
    Vertex a;
    Vertex b;

    Edges() {}
    Edges(Vertex m, Vertex n)
    {
        a=m;
        b=n;
    }
    double getHorzDistnc(double currentY)
    {
        double keyVal;
        if(a.y == b.y)
        {
            keyVal = (a.x<b.x)?a.x:b.x;
        }
        else
        {
            keyVal= (currentY-a.y)*(b.x - a.x)/(b.y - a.y)+ a.x;
        }
        return keyVal;
    }
};
typedef Edges Edges;

#endif // CUSTOMTYPES_H
