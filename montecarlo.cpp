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
    double minY;
    double maxY;

    /*
     * scale point
     */
    void scale(Point* p)
    {
        p->x = p->x * (maxX - minX) + minX;
        p->y = p->y * (maxY - minY) + minY;
    }
};

// random number generator
// you must call Rand::init() first before you call Rand::next(), 
// otherwise you will get the same result every time.
class Rand
{
public:
    static void init()
    {
		// set rand number seed with time
        srand(time(0));
    }

    // get rand number between 0 and 1
    static double next()
    {
        return rand() / (double)RAND_MAX;
    }

};

// define max random points number
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
	box.minY = 0;
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

// use function pointer to compute any single variable function
double computeIntegration(double func(double), Box box)
{
    Point p;
    int count = 0;
	double result;
    for(int i = 0; i < MAX_POINT_NUM; i++)
    {
        p.x = Rand::next();
        p.y = Rand::next();
		
        box.scale(&p);
		result = func(p.x);
        if (result > 0 && p.y < result)
        {
			// value over axis x
            count++;
        }
		else if (result < 0 && p.y > result)
		{
			// value below axis x
			count--;
		}
    }

    return count * (box.maxX - box.minX) * (box.maxY - box.minY)/ (double)MAX_POINT_NUM;
}

// combination function exp(x) and -x
double expMinus(double x)
{
	return exp(-x);
}

int main()
{
    Rand::init();

	double pi = computePi();
    cout << "PI = " << pi << endl;
    cout << "exp(-10) = " << exp(-10) << endl;
    cout << "Integration exp(-x) from 0 to 10 = " << computeExpIntegration(10) << endl;
    cout << "Integration exp(-x) from 0 to 20 = " << computeExpIntegration(20) << endl;	
	
    Box box;
    box.minX = 0;
    box.maxX = 10;
	box.minY = 0;
    box.maxY = 1;
	
    cout << "Integration exp(-x) from 0 to 10 = " << computeIntegration(expMinus, box) << endl;
	
    box.minX = 0;
    box.maxX = pi;
	box.minY = 0;
    box.maxY = 1;
	
    cout << "Integration sin(x) from 0 to pi = " << computeIntegration(sin, box) << endl;
	
	box.minY = -1;
    box.maxY = 1;
    cout << "Integration cos(x) from 0 to pi = " << computeIntegration(cos, box) << endl;
		
    box.minX = -pi;
    box.maxX = pi;
    cout << "Integration sin(x) from -pi to pi = " << computeIntegration(sin, box) << endl;
    
    return(0);
}
