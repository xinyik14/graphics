#include "headers.h"

//using namespace std;

int round(float d);

std::vector<Point> lineSpecial(Point start, Point end);

std::vector<Point> lineDDA(Point start, Point end);

std::vector<Point> lineBres(Point start,Point end);

void drawPoint(const Attribute &attribute, const Point &p);

void drawLine(const Attribute &attribute, const Point &start, const Point &end, string method);

void drawPolygon(const Attribute &attribute, const Polygon &p);

void drawAllPolygons(const Attribute &attribute, Polygon** PolygonsFile, int nPolygons);
  
int getIndex(int x, int y, const Attribute &attribute);
