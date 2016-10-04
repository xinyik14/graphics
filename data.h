#include "headers.h"

using namespace std;

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
        pair<int, int> findMaxAndMinY();
        friend ostream &operator<<( ostream &output, const Polygon &P ){
            Point** array = P.get_array();
            int Pn = P.get_n();
            output << P.get_id() << ": "  <<endl;
            for (int i = 0; i < P.get_n(); i++){
                output << " "<< *array[i];
            }
            output << endl;
            return output;
        }

};

int getIndex(int x, int y, Attribute A);
