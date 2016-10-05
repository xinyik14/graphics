#include "headers.h"

Attribute::Attribute(int _width, int _height) {
    //Attribute class constructor
    width = _width;
    height = _height;
    pixelBuffer = new float[width*height*3];
}

Attribute::~Attribute() {
    delete[] pixelBuffer;
}

Point::Point(float _x, float _y) {
    //Point class constructor
    x = _x;
    y = _y;
}

Polygon::Polygon(int _nPoint, string _id) {
    //Polygon class constructor
    nPoint = _nPoint;
    id = _id;
    points = new Point*[nPoint];
}

Polygon::~Polygon() {
    //Polygon class deconstructor
    for (int i = 0; i < nPoint; i++) {
        delete points[i];
    }
    delete[] points;
}

void Polygon::setPoint(int index, float x, float y) {
    points[index] = new Point(x, y);
}

void Polygon::findMaxAndMinY(int &max, int &min){
    max = 0, min = 0;
    for (int i = 0; i < nPoint; i++){
        Point* p = points[i];
        int y = p -> get_y();
        if (y > max){
            max = y;
        }
        if (y < min){
            min = y;
        }
    }
}

