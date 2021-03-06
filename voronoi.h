#ifndef VORONOI_H
#define VORONOI_H

#include <vector>
#include <algorithm>

#include "points.h"
#include "vedge.h"
#include "chardraw.h"
#include "quickhull.h"

extern double screenWidth;
extern double screenHeight;
/*
extern double leftX;// = 0;
extern double topY;// = 0;

extern double mulX;// = 0.09;
extern double mulY;// = 0.09;
extern double zoom;// = 0.05;
extern double delta;
*/

#define MAXSITE 20

class Voronoi
{
private:
    static double precision;
    bool isIntersecting(VoronoiEdge,VoronoiEdge);
    double intersectingY(VoronoiEdge,VoronoiEdge);
    void getMinMaxPoints(int,int,int,int&,int&,int&,int&);

public:
    std::vector<Point3> sites;
    std::vector<VoronoiEdge> vedges;
    std::vector<int> vRegions[MAXSITE];
    Voronoi();
    void takeInput();
    void buildVoronoiDiagram();
    std::vector<VoronoiEdge> splitSites(int,int);
    std::vector<VoronoiEdge> mergeSites(int,int,int,std::vector<VoronoiEdge>,std::vector<VoronoiEdge>);
    void getUpperSupport(int,int,int,int&,int&);
    void getLowerSupport(int,int,int,int&,int&);
    void drawSites();
    void drawVoronoiEdges();
    void draw();
};
double Voronoi::precision=0.0000000001;
Voronoi::Voronoi()
{
    takeInput();
    buildVoronoiDiagram();
}
bool Voronoi::isIntersecting(VoronoiEdge a,VoronoiEdge b)
{
    //if(abs(a.slope-b.slope)<Voronoi::precision)
    if((a.slope-b.slope)==0)
    {
        return false;
    }
    double x=(a.yIntercept-b.yIntercept)/(b.slope-a.slope);
    if((a.isLeftInf || x>=(a.left)) && (a.isRightInf || x<=(a.right)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
double Voronoi::intersectingY(VoronoiEdge a,VoronoiEdge b)
{
    return (a.slope*b.yIntercept-a.yIntercept*b.slope)/(a.slope-b.slope);
}
void Voronoi::getLowerSupport(int s,int m,int e,int &left,int &right)
{
    /*
    QuickHull leftHull(std::vector<Point3>(sites.begin()+s,sites.begin()+m+1));
    QuickHull rightHull(std::vector<Point3>(sites.begin()+m+1,sites.begin()+e+1));
    printf("finding hull for lower support %d-%d\n",
           leftHull.resultPoints[0].index,leftHull.resultPoints[leftHull.resultPoints.size()-1].index);
    //std::vector<Point3> hull=QuickHull
    */
    printf("inside getLowerSupport()\n");
    QuickHull leftHull(std::vector<Point3>(sites.begin()+s,sites.begin()+m+1));
    QuickHull rightHull(std::vector<Point3>(sites.begin()+m+1,sites.begin()+e+1));
   // printf("finding hull for lower support %d-%d\n",
        //   rightHull.resultPoints[0].index,rightHull.resultPoints[rightHull.resultPoints.size()-1].index);
    int leftInd=0;
    int rightInd=0;

    ///point with max and min value of x from right and left hull
    double currentX=leftHull.resultPoints[0].x;
    for(int i=1;i<leftHull.resultPoints.size();i++)
    {
        if(currentX<leftHull.resultPoints[i].x)
        {
            currentX=leftHull.resultPoints[i].x;
            //leftInd=leftHull.resultPoints[i].index;
            leftInd=i;
        }
    }
    currentX=rightHull.resultPoints[0].x;
    for(int i=1;i<rightHull.resultPoints.size();i++)
    {
        if(currentX>rightHull.resultPoints[i].x)
        {
            currentX=rightHull.resultPoints[i].x;
            //rightInd=rightHull.resultPoints[i].index;
            rightInd=i;
        }
    }

    Vector3 line(leftHull.resultPoints[leftInd],rightHull.resultPoints[rightInd]);
    int leftSize=leftHull.resultPoints.size();
    int next=(leftInd+1)%leftSize;
    while((line.zcross(Vector3(leftHull.resultPoints[leftInd],leftHull.resultPoints[next])))<0)
    {
        leftInd=next;
        next=(next+1)%leftSize;
        line=Vector3(leftHull.resultPoints[leftInd],rightHull.resultPoints[rightInd]);
    }
    left=leftHull.resultPoints[leftInd].index;
    int rightSize=rightHull.resultPoints.size();
    next=(rightInd+1)%rightSize;
    while((line.zcross(Vector3(leftHull.resultPoints[leftInd],rightHull.resultPoints[next])))<0)
    {
        rightInd=next;
        next=(next+1)%rightSize;
        line=Vector3(leftHull.resultPoints[leftInd],rightHull.resultPoints[rightInd]);
    }
    right=rightHull.resultPoints[rightInd].index;
    printf("left %d , right %d\n",left,right);
}

void Voronoi::getUpperSupport(int s,int m,int e,int &left,int &right)
{
    printf("inside getUpperSupport()\n");
    QuickHull leftHull(std::vector<Point3>(sites.begin()+s,sites.begin()+m+1));
    QuickHull rightHull(std::vector<Point3>(sites.begin()+m+1,sites.begin()+e+1));
    //printf("finding hull for upper support %d-%d\n",
    //       rightHull.resultPoints[0].index,rightHull.resultPoints[rightHull.resultPoints.size()-1].index);
    int leftInd=0;
    int rightInd=0;

    ///point with max and min value of x from right and left hull
    double currentX=leftHull.resultPoints[0].x;
    for(int i=1;i<leftHull.resultPoints.size();i++)
    {
        if(currentX<leftHull.resultPoints[i].x)
        {
            currentX=leftHull.resultPoints[i].x;
            //leftInd=leftHull.resultPoints[i].index;
            leftInd=i;
        }
    }
    currentX=rightHull.resultPoints[0].x;
    for(int i=1;i<rightHull.resultPoints.size();i++)
    {
        if(currentX>rightHull.resultPoints[i].x)
        {
            currentX=rightHull.resultPoints[i].x;
            //rightInd=rightHull.resultPoints[i].index;
            rightInd=i;
        }
    }
    ///finding upper bridge
    Vector3 line(leftHull.resultPoints[leftInd],rightHull.resultPoints[rightInd]);
    int leftSize=leftHull.resultPoints.size();
    int nextLeft=(leftInd+1)%leftSize;
    double leftCross = line.zcross(Vector3(leftHull.resultPoints[leftInd],leftHull.resultPoints[nextLeft]));
    while(leftCross>0)
    {
        leftInd=nextLeft;
        nextLeft=(nextLeft+1)%leftSize;
        leftCross = line.zcross(Vector3(leftHull.resultPoints[leftInd],leftHull.resultPoints[nextLeft]));
    }
    left=leftHull.resultPoints[leftInd].index;
    int rightSize=rightHull.resultPoints.size();
    int nextRight=(rightInd+1)%rightSize;
    double rightCross=line.zcross(Vector3(leftHull.resultPoints[leftInd],rightHull.resultPoints[nextRight]));
    while(rightCross>0)
    {
        rightInd=nextRight;
        nextRight=(nextRight+1)%rightSize;
        rightCross=line.zcross(Vector3(leftHull.resultPoints[leftInd],rightHull.resultPoints[nextRight]));
    }
    right=rightHull.resultPoints[rightInd].index;
    printf("left %d , right %d\n",left,right);
    //std::vector<Point3> hull=QuickHull
}
void Voronoi::getMinMaxPoints(int s,int m,int e,int &minL,int &maxL,int &minR,int &maxR)
{
    minL=maxL=s;
    minR=maxR=m+1;
    for(int i=s+1; i<=m; i++)
    {
        if(sites[i].y<sites[minL].y)
        {
            minL=i;
        }
        if(sites[i].y>sites[maxL].y)
        {
            maxL=i;
        }
    }
    for(int i=m+2; i<=e; i++)
    {
        if(sites[i].y<sites[minR].y)
        {
            minR=i;
        }
        if(sites[i].y>sites[maxR].y)
        {
            maxR=i;
        }
    }
}
void Voronoi::takeInput()
{
    int totalPoint;
    char filePath[]="I:\\Dropbox\\open_gl\\Voronoi\\input.txt";
    char outputFilePath[]="I:\\Dropbox\\open_gl\\Voronoi\\output.txt";
    //freopen(outputFilePath,"w",stdout);
    FILE *ifp;
    ifp=fopen(filePath,"r");
    fscanf(ifp,"%d",&totalPoint);
    Point3 p;
    for(int i=0; i<totalPoint; i++)
    {
        fscanf(ifp,"%lf%lf",&p.x,&p.y);
        this->sites.push_back(p);
    }
    printf("input taken\n");
}

void Voronoi::buildVoronoiDiagram()
{
    std::sort(sites.begin(),sites.end(),pointCompr);
    for(int i=0;i<sites.size();i++)
    {
        sites[i].index=i;
    }
    //splitSites(0,sites.size()-1);
    std::vector<VoronoiEdge> leftEdges;
    std::vector<VoronoiEdge> rightEdges;
    int startIndex=0,endIndex=sites.size()-1;
    int mid=(startIndex+endIndex)/2;
    leftEdges=splitSites(startIndex,mid);
    rightEdges=splitSites(mid+1,endIndex);
    mergeSites(startIndex,mid,endIndex,leftEdges,rightEdges);
}

std::vector<VoronoiEdge> Voronoi::splitSites(int startIndex,int endIndex)
{
    std::vector<VoronoiEdge> vList;
    if((endIndex-startIndex+1)==1)
    {
    }
    else if((endIndex-startIndex+1)==2)
    {
        printf("last level %d-%d\n",startIndex,endIndex);
        VoronoiEdge e;
        e.slope=(sites[startIndex].x-sites[endIndex].x)/(sites[endIndex].y-sites[startIndex].y);
        e.yIntercept=0.5*(sites[startIndex].y+sites[endIndex].y-
                          e.slope*(sites[startIndex].x+sites[endIndex].x));
        if(sites[startIndex].y>sites[endIndex].y)
        {
            e.upSiteIndex=startIndex;
            e.downSiteIndex=endIndex;
        }
        else
        {
            e.upSiteIndex=endIndex;
            e.downSiteIndex=startIndex;
        }
        vList.push_back(e);
        vedges.push_back(e);
        //vRegions[startIndex].push_back(e);
        vRegions[startIndex].push_back(vedges.size()-1);
        //vRegions[endIndex].push_back(e);
        vRegions[endIndex].push_back(vedges.size()-1);
    }
    else
    {
        std::vector<VoronoiEdge> leftEdges;
        std::vector<VoronoiEdge> rightEdges;
        int mid=(startIndex+endIndex)/2;
        leftEdges=splitSites(startIndex,mid);
        rightEdges=splitSites(mid+1,endIndex);
        vList=mergeSites(startIndex,mid,endIndex,leftEdges,rightEdges);
    }
    return vList;
}

std::vector<VoronoiEdge> Voronoi::mergeSites(int s,int m,int e,
        std::vector<VoronoiEdge> leftEdges,
        std::vector<VoronoiEdge> rightEdges)
{
    printf("merging %d-%d\n",s,e);
    std::vector<VoronoiEdge> result;
    int downLeft,downRight,upLeft,upRight;
    getLowerSupport(s,m,e,downLeft,downRight);
    getUpperSupport(s,m,e,upLeft,upRight);
    getMinMaxPoints(s,m,e,downLeft,upLeft,downRight,upRight);
    printf("downL=%d, downR=%d -- upL=%d, upR=%d\n\n",downLeft,downRight,upLeft,upRight);

    //change using convex hull
    int curLeft=upLeft,curRight=upRight;

    int oldLeft,oldRight;
    int limit = (s-e+1)*(s-e+1);
    int iteration = 0;
    std::vector<bool> isEdgeChecked;
    for(int i=0; i<vedges.size(); i++)
    {
        isEdgeChecked.push_back(false);
    }
    bool tmp=false;
    std::vector<VoronoiEdge> chain;
    double lastX;

    while(!(curLeft==downLeft&&curRight==downRight))
    {
        printf("curLeft=%d,curRight=%d\n",curLeft,curRight);
        oldLeft=curLeft;
        oldRight=curRight;
        if(++iteration>limit)
        {
            break;
        }
        VoronoiEdge ed;
        ed.slope=(sites[curLeft].x-sites[curRight].x)/(sites[curRight].y-sites[curLeft].y);
        ed.yIntercept=0.5*(sites[curLeft].y+sites[curRight].y-
                           ed.slope*(sites[curLeft].x+sites[curRight].x));
        if(tmp)
        {
            //tmp=true;
            if(ed.slope>0)
            {
                //printf("setting bool\n");
                ed.isRightInf=false;
                ed.right=lastX;
            }
            else
            {
                ed.isLeftInf=false;
                ed.left=lastX;
            }
        }
        else
        {
            tmp=true;
        }
        if(sites[curLeft].y>sites[curRight].y)
        {
            ed.upSiteIndex=curLeft;
            ed.downSiteIndex=curRight;
        }
        else
        {
            ed.upSiteIndex=curRight;
            ed.downSiteIndex=curLeft;
        }

        int leftIntersection,rightIntersection;
        double y,minLeftY=0,minRightY=0;
        //upLeftY=intersectingY(e,vRegions[curLeft][0]);
        bool isLeftUnset=true;
        //printf("vRegions[curleft].size=%d\n",vRegions[curLeft].size());

        for(int i=0; i<vRegions[curLeft].size(); i++)
        {
            if(isEdgeChecked[vRegions[curLeft][i]])
            {
                continue;
            }
            if(isIntersecting(ed,vedges[vRegions[curLeft][i]]))
            {
                //printf("setting bool<%d> -- size<%d>\n",vRegions[curLeft][i],isEdgeChecked.size());
                //isEdgeChecked[vRegions[curLeft][i]]=true;
                y=intersectingY(ed,vedges[vRegions[curLeft][i]]);
                if(isLeftUnset || (!isLeftUnset&&minLeftY<y))
                {
                    isLeftUnset=false;
                    minLeftY=y;
                    leftIntersection=vRegions[curLeft][i];
                }
            }
        }
        //minLeftY=intersectingY(e,vRegions[curLeft][0]);
        bool isRightUnset=true;

        for(int i=0; i<vRegions[curRight].size(); i++)
        {
            if(isEdgeChecked[vRegions[curRight][i]])
            {
                continue;
            }
            if(isIntersecting(ed,vedges[vRegions[curRight][i]]))
            {
                //isEdgeChecked[vRegions[curRight][i]]=true;
                y=intersectingY(ed,vedges[vRegions[curRight][i]]);
                if(isRightUnset || (!isRightUnset&&minRightY<y))
                {
                    isRightUnset=false;
                    minRightY=y;
                    rightIntersection=vRegions[curRight][i];
                }
            }
        }
        //printf("minleftY=%lf,minRightY=%lf\n",minLeftY,minRightY);
        if(isRightUnset || (!isLeftUnset&&minLeftY>minRightY))
        {
            printf("minlefty > minrighty\nleftI=%d\n",leftIntersection);
            isEdgeChecked[leftIntersection]=true;

            //if(ed.slope<vedges[leftIntersection].slope)
            if(true)
            {
                printf("ed.slope>vedges[leftIntersection].slope\n");
                vedges[leftIntersection].isRightInf=false;
                vedges[leftIntersection].right=
                    (minLeftY-vedges[leftIntersection].yIntercept)/
                    vedges[leftIntersection].slope;
                lastX=vedges[leftIntersection].right;
            }
            else
            {
                printf("else ed.slope<=vedges[leftIntersection].slope\n");
                vedges[leftIntersection].isLeftInf=false;
                vedges[leftIntersection].left=
                    (minLeftY-vedges[leftIntersection].yIntercept)/
                    vedges[leftIntersection].slope;
                lastX=vedges[leftIntersection].left;
            }
            //printf("updated vedge<%d>.right=%lf\n",leftIntersection,
            //     (vedges[leftIntersection].right));

            if(ed.slope>0)
            {
                ed.isLeftInf=false;
                ed.left=vedges[leftIntersection].right;
            }
            else
            {
                ed.isRightInf=false;
                ed.right=vedges[leftIntersection].right;
            }
            if(curLeft==vedges[leftIntersection].downSiteIndex)
            //if(false)
            {
                curLeft=vedges[leftIntersection].upSiteIndex;
            }
            else
            {
                curLeft=vedges[leftIntersection].downSiteIndex;
            }
            vedges.push_back(ed);
            //isEdgeChecked[vedges.size()-1]=true;
            vRegions[oldLeft].push_back(vedges.size()-1);
            printf("voronoi edges around site%d = %d\n",curLeft,vRegions[curLeft].size());
        }
        else
        {
            printf("minlefty < minrighty\nrightInter=%d, size=%d\n",rightIntersection,isEdgeChecked.size());
            isEdgeChecked[rightIntersection]=true;
            //printf("set bool\n");
            vedges[rightIntersection].isLeftInf=false;

            //printf("slope=%lf\n",vedges[rightIntersection].slope);
            vedges[rightIntersection].left=
                (minRightY-vedges[rightIntersection].yIntercept)/
                vedges[rightIntersection].slope;

            lastX=vedges[rightIntersection].left;
            //printf("updated vedge<%d>.left=%lf\n",rightIntersection,
            //     (vedges[rightIntersection].left));
            if(ed.slope>0)
            {
                ed.isLeftInf=false;
                ed.left=vedges[rightIntersection].left;
            }
            else
            {
                ed.isRightInf=false;
                ed.right=vedges[rightIntersection].left;
            }
            if(curRight==vedges[rightIntersection].downSiteIndex)
            //if(false)
            {
                curRight=vedges[rightIntersection].upSiteIndex;
            }
            else
            {
                curRight=vedges[rightIntersection].downSiteIndex;
            }
            vedges.push_back(ed);
            //isEdgeChecked[vedges.size()-1]=true;
            vRegions[oldRight].push_back(vedges.size()-1);
            printf("voronoi edges around site%d = %d\n",curRight,vRegions[curRight].size());
            //curRight=vedges[vRegions[curRight][rightIntersection]].downSiteIndex;
        }
        //vedges[0].right=new double(0);
        //vedges[0].right=9;
        //vedges[0].isRightInf=false;

        //vedges.push_back(ed);
        chain.push_back(ed);
        result.push_back(ed);
        //vRegions[oldLeft].push_back(vedges.size()-1);
        //vRegions[oldLeft].push_back(vedges.size()-1+chain.size()-1);

        //vRegions[curLeft].push_back(vedges.size()-1+chain.size()-1);
        //vRegions[oldRight].push_back(vedges.size()-1);
        //vRegions[oldRight].push_back(vedges.size()-1+chain.size()-1);
        //vRegions[curRight].push_back(vedges.size()-1+chain.size()-1);
        //break;
        //printf("\n");
        printf("updated >> curLeft=%d,curRight=%d\n\n",curLeft,curRight);
    }
    printf("curLeft=%d,curRight=%d\n",curLeft,curRight);
    VoronoiEdge ed;
    ed.slope=(sites[curLeft].x-sites[curRight].x)/(sites[curRight].y-sites[curLeft].y);
    ed.yIntercept=0.5*(sites[curLeft].y+sites[curRight].y-
                       ed.slope*(sites[curLeft].x+sites[curRight].x));
    if(ed.slope>0)
    {
        //printf("setting bool\n");
        ed.isRightInf=false;
        ed.right=lastX;
    }
    else
    {
        ed.isLeftInf=false;
        ed.left=lastX;
    }
    if(sites[curLeft].y>sites[curRight].y)
    {
        ed.upSiteIndex=curLeft;
        ed.downSiteIndex=curRight;
    }
    else
    {
        ed.upSiteIndex=curRight;
        ed.downSiteIndex=curLeft;
    }
    chain.push_back(ed);
    result.push_back(ed);
    vedges.push_back(ed);
    vRegions[curLeft].push_back(vedges.size()-1);
    vRegions[curRight].push_back(vedges.size()-1);
    ///returning final voronoi edges
    for(int i=0; i<chain.size(); i++)
    {
        //vedges.push_back(chain[i]);
    }
    for(int i=0; i<leftEdges.size(); i++)
    {
        //result.push_back(leftEdges[i]);
    }
    for(int i=0; i<rightEdges.size(); i++)
    {
        //result.push_back(rightEdges[i]);
    }
    return result;
}

void Voronoi::drawSites()
{
    glColor3f(0,0,0);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    {
        for(int i=0; i<sites.size(); i++)
        {
            glVertex2f(sites[i].x,sites[i].y);
        }
    }
    glEnd();
    char num[5];
    for(int i=0; i<sites.size(); i++)
    {
        itoa(i,num,10);
        Misc::drawString((int)sites[i].x,(int)sites[i].y,num);
    }
}

void Voronoi::drawVoronoiEdges()
{
    double x1,y1,x2,y2;

    //vedges[0].right=new double(9.0);
    //printf("\n\n");
    for(int i=0; i<vedges.size(); i++)
    {
        //printf("drawing vedge%d\n",i);
        glColor3f(0,0,0);
        if(vedges[i].isLeftInf)
        {
            //printf("left at infinity\n");
            x1=-screenWidth/2;
            y1=vedges[i].slope*x1+vedges[i].yIntercept;
        }
        else
        {
            //printf("leftX=%lf\n",(vedges[i].left));
            x1=(vedges[i].left);
            y1=vedges[i].slope*x1+vedges[i].yIntercept;
        }
        if(vedges[i].isRightInf)
        {
            //printf("right at inf\n");
            x2=screenWidth/2;
            y2=vedges[i].slope*x2+vedges[i].yIntercept;
        }
        else
        {
            //printf("rightX=%lf\n",vedges[i].right);
            x2=(vedges[i].right);
            y2=vedges[i].slope*x2+vedges[i].yIntercept;
        }
        glBegin(GL_LINES);
        {
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
        }
        glEnd();
    }
}

void Voronoi::draw()
{
    drawSites();
    drawVoronoiEdges();
}

#endif // VORONOI_H
