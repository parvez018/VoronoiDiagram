#ifndef CHARDRAW_H
#define CHARDRAW_H

class Misc
{
public:
    static void drawString(int,int,char*);
    static void drawString(int,int,int);
};

void Misc :: drawString(int x, int y, char *str)
{
    float r=1.0;
    float g=0;
    float b=0;
    glColor3f( r, g, b );
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
    }
}
void Misc :: drawString(int x, int y, int val)
{
    float r=0;
    float g=0;
    float b=1;
    glColor3f( r, g, b );
    glRasterPos2f(x, y);
    int len, i;
    char str[10];
    itoa(val,str,10);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    }
}
#endif // CHARDRAW_H
