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

Polygon::Polygon(int _nPoint, string _id) {
    //Polygon class constructor
    nPoint = _nPoint;
    id = _id;
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

pair<int, int> Polygon::findMaxAndMinY(){
    int max = 0;
    int min = 0;
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
    return make_pair(max, min);


}

