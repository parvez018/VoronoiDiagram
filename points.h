#ifndef POINTS_H
#define POINTS_H
struct Point3
{
    double x;
    double y;
    double z;
    int index;

    Point3() {}
    Point3(double a, double b, double c)
    {
        x=a;
        y=b;
        z=c;
    }
    Point3(double a, double b)
    {
        //2d point in xy-plane
        x=a;
        y=b;
    }
    Point3(int a, int b)
    {
        //2d point in xy-plane
        x=a;
        y=b;
    }

    void set(double a, double b, double c)
    {
        x=a;
        y=b;
        z=c;
    }
    void set(Point3 a)
    {
        x=a.x;
        y=a.y;
        z=a.z;
    }
};
typedef Point3 Point3;
struct pointCompare
{
    bool operator()(const Point3 &t1, const Point3 &t2) const
    {
        return t1.x<t2.x;
    }
}pointCompr;

#endif // POINTS_H
