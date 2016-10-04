#include "headers.h"

//using namespace std;

int round(float d);

std::vector<Point> lineSpecial(Point start, Point end);

std::vector<Point> lineDDA(Point start, Point end);

std::vector<Point> lineBres(Point start,Point end);

void drawPoint(Attribute A, Point p);

void drawLine(Attribute A, Point start, Point end, string method);

void drawPolygon(Attribute A, Polygon p);

void drawAllPolygons(Attribute A, Polygon** PolygonsFile, int nPolygons);
  
int getIndex(int x, int y, Attribute A);

pair<Polygon**, int> readInput();    
