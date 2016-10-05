#include "headers.h"

using namespace std;

class Attribute {
    private:
        int width;
        int height;
        float* pixelBuffer;
    public:
        Attribute(int _width, int _height);
        ~Attribute();
    float* get_buffer() const {return pixelBuffer;}
    int get_width() const {return width;}
    int get_height() const {return height;}
    void set_width(int w){width = w;}
    void set_height(int h){height = h;}
};

class Point {
    private:
        float x, y;
    public:
        Point(float x, float y);
        float get_x() const {return x;}
        float get_y() const {return y;}
//    void draw(Attribute A);
        friend ostream &operator<<( ostream &output, const Point &P ){
            output << "(" << P.get_x() << "," << P.get_y() << ")" << endl;
            return output;
        }
};

class Polygon {
    private:
        string id;
        int nPoint;
        Point **points;
    public:
        Polygon(int nPoint, string _id);
        ~Polygon();
        string get_id() const {return id;}
        int get_n() const {return nPoint;}
        Point** get_array() const {return points;}
        void setPoint(int index, float x, float y);
        void findMaxAndMinY(int &max, int &min);
        friend ostream &operator<<(ostream &output, const Polygon &p ){
            Point** array = p.get_array();
            int n = p.get_n();
            output << p.get_id() << ": "  <<endl;
            for (int i = 0; i < n; i++){
                output << " "<< *array[i];
            }
            output << endl;
            return output;
        }

};
