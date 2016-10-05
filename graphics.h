#include "headers.h"

std::vector<Point> lineSpecial(const Point &start, const Point &end);

std::vector<Point> lineDDA(const Point &start, const Point &end);

std::vector<Point> lineBres(const Point &start, const Point &end);

void drawPoint(const Attribute &attribute, const Point &p);

void drawLine(const Attribute &attribute, const Point &start, const Point &end, string method);

void drawPolygon(const Attribute &attribute, const Polygon &p);

void drawAllPolygons(const Attribute &attribute, Polygon** PolygonsFile, int nPolygons);
  
int getIndex(int x, int y, const Attribute &attribute);
