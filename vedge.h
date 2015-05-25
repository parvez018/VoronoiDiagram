#ifndef VEDGE_H
#define VEDGE_H
class VoronoiEdge
{
private:

public:
    double slope;
    double yIntercept;
    bool isLeftInf;
    bool isRightInf;
    double left;
    double right;
    double *up;
    double *down;
    int upSiteIndex;
    int downSiteIndex;
    VoronoiEdge();
};
VoronoiEdge::VoronoiEdge()
{
    left=NULL;
    right=NULL;
    up=NULL;
    down=NULL;
    isLeftInf=true;
    isRightInf=true;
    upSiteIndex=-1;
    downSiteIndex=-1;
}
#endif // VEDGE_H
