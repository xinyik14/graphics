#include "headers.h"

Attribute::Attribute(int width, int height) {
    //Attribute class constructor
    _width = width;
    _height = height;
    PixelBuffer = new float[_width*_height*3];
}

//Attribute::~Attribute() {delete[] PixelBuffer;}
Point::Point(float _x, float _y) {
    //Point class constructor
    x = _x;
    y = _y;
}

Polygon::Polygon(int nPoint) {
    //Polygon class constructor
    this -> points = new Point*[nPoint];
}

Polygon::~Polygon() {
    //Polygon class deconstructor
    for (int i = 0; i < nPoint; i++) {
        delete points[i];
    }
    delete[] points;
}

void Polygon::setPoint(int index, float x, float y) {
    this -> points[index] = new Point(x, y);
}
