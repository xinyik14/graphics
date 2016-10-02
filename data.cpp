class Attribute {
    private:
        int _width;
        int _height;
        float* PixelBuffer;
    public:
        Attribute(int width, int height);
  //      ~Attribute();
        float* get_buffer(){return PixelBuffer;}
        int get_width(){return _width;}
        int get_height(){return _height;}
        void set_width(int w){_width = w;}
        void set_height(int h){_height = h;}
};

Attribute::Attribute(int width, int height) {
    _width = width;
    _height = height;
    PixelBuffer = new float[_width*_height*3];
}

//Attribute::~Attribute() {delete[] PixelBuffer;}


class Point {
    float x, y;
    public:
        Point(float x, float y);
        float get_x() const {return x;}
        float get_y() const {return y;} 
        void draw(Attribute A);
        friend ostream &operator<<( ostream &output, const Point &P ){
            output << "(" << P.get_x() << "," << P.get_y() << ")" << endl;
            return output;
        }
};

class Polygon {
    private:
        int nPoint;
        Point **points; 
    public:
        Polygon(int nPoint);
        ~Polygon();
        void draw();
        void setPoint(int index, float x, float y);
};

Point::Point(float _x, float _y) {
    x = _x;
    y = _y;
}



int getIndex(int x, int y, Attribute A) {
    //function to calculate the corresbonding place of a point in PixelBuffer
    if ((x<0) || (y<0) || (x>A.get_width()) || (y>A.get_height())){
        return -1;
    }
    else {
        int h = y*A.get_width()*3;
        int w = x*3;
        return h+w;
    }
}

// implement this draw method
void Polygon::draw() {
}

void Polygon::setPoint(int index, float x, float y) {
    this -> points[index] = new Point(x, y);

}

Polygon::Polygon(int nPoint) {
    this -> points = new Point*[nPoint];
}

Polygon::~Polygon() {
    for (int i = 0; i < nPoint; i++) {
        delete points[i];
    }
    delete[] points;
}
