#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

class Point
{
public:
    double x;
    double y;
};

class Box
{
public:
    double minX;
    double maxX;
    double maxY;

    /*
     * scale point
     */
    void scale(Point* p)
    {
        p->x = p->x * (maxX - minX) + minX;
        p->y = p->y * maxY;
    }
};

class Rand
{
public:
    static void init()
    {
        srand(time(0));
    }

    /*
     * get rand number between 0 and 1
     */
    static double next()
    {
        return rand() / (double)RAND_MAX;
    }

};

#define MAX_POINT_NUM 1000000

double computePi()
{
    int count = 0;
    double x, y;
    for(int i = 0; i < MAX_POINT_NUM; i++)
    {
        x = Rand::next();
        y = Rand::next();
        
        if ((x * x + y * y) < 1)
        {
            count++;
        }

    }
    double pi = 4 * count / (double)MAX_POINT_NUM;

    return pi;
}

// compute exp(-x)
double computeExpIntegration(int maxX)
{
    Box box;
    box.minX = 0;
    box.maxX = maxX;
    box.maxY = 1;

    Point p;
    int count = 0;
    for(int i = 0; i < MAX_POINT_NUM; i++)
    {
        p.x = Rand::next();
        p.y = Rand::next();

        box.scale(&p);
        if (p.y < exp(-p.x))
        {
            count++;
        }
    }

    return count * maxX / (double)MAX_POINT_NUM;
}

int main()
{
    Rand::init();

    cout << "PI = " << computePi() << endl;
    cout << "exp(-10) = " << exp(-10) << endl;
    cout << "Integration exp(-x) from 0 to 10 = " << computeExpIntegration(10) << endl;
    cout << "Integration exp(-x) from 0 to 20 = " << computeExpIntegration(20) << endl;
    
    return(0);
}
