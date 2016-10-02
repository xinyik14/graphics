#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

int round(float d){
     return floor(d + 0.5);
}

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

std::vector<Point> lineSpecial(Point start, Point end){
//deal with sepcial cases such as line with m=0, m=1 and m=infinite
    //int dy = end.get_y() - start.get_y(), dx = end.get_x() - start.get_x();
    int x0= start.get_x(), xEnd = end.get_x(), y0 = start.get_y(), yEnd = end.get_y();
    int dy = yEnd - y0, dx = xEnd - x0;
    int yStep = abs(dy), xStep = abs(dx);
    std::vector<Point> line;
    if (dy == 0){
    //when it's a horizontal line
        int s = dx/xStep;
        for(int i = 0; i <= xStep; i ++){
            //deal with both cases that dx > 0 and dx < 0
            int x = x0 + i*s;
            line.push_back(Point(x, y0));
        }
    }
    else if (dx == 0){
    //when it's a horizontal line
        int s = dy/yStep;
        for(int i = 0; i <= yStep; i ++ ){
            //deal with both cases that dy > 0 and dy < 0
            int y = y0 + i*s;
            line.push_back(Point(x0, y));
        }
    }
    else{
        int m = dy/dx;//no need for float because m is either -1 or 1
        int s = dx/xStep;//need to know the direction to go(from left to right or vice verse) as well
        for(int i = 0; i <= xStep; i ++){
            line.push_back(Point(x0 + i*s, y0 + i*m));
        }
    }
    cout << line.front() << endl;
    cout << line.back() <<endl;
    return line;
}
std::vector<Point> lineDDA(Point start, Point end){
   
    int dy = end.get_y() - start.get_y(), dx = end.get_x() - start.get_x();
    int x0 = start.get_x(), y0 = start.get_y();
    int xStep = abs(dx);
    int yStep = abs(dy);
    if ((xStep == yStep) || (dy == 0) || (dx == 0)){
        //special cases: m=1/-1, horizontal line or vertical line
        cout << "Go to special cases" << endl;
        return lineSpecial(start, end);
    }
    std::vector<Point> line;
   
    if (dy < dx){
        //the slop is gentle, so march through xi 
        //0< m < 1 or 0 > m > -1
        float m = dy/dx;
        
        for(int i = 0; i <= xStep; i++){
            float yExact = x0 + i * m;
            int y = round(yExact);
            line.push_back(Point(x0 + i, y));
        }
        return line;
    }
    else{
        //the only case left here is when m > 1 or m < -1
        //so we march through yi instead
        float m = dx/dy;
        for(int i = 0; i <= yStep; i++){
            float xExact = y0 + i*m;
            int x = round(xExact);
            line.push_back(Point(x, y0 + i));
        }
        return line;
    }
}

std::vector<Point> lineBres(Point start,Point end){
    int x0 = start.get_x(), y0 = start.get_y(), xEnd = end.get_x(), yEnd = end.get_y();
    int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
    float m = dy/dx;

    // int p = 2 * dy - dx;
   // int twoDy = 2 * dy;
   // int twoDyMinusDx = 2 * (dy - dx);
   // int x, y;

   // if (x0 > xEnd) {
     //   x = xEnd;
       // y = yEnd;
       // xEnd = x0;
   // }
   // else {
     //   x = x0;
       // y = y0;
   // }
   //
   //
   std::vector<Point> line;
  // line.push_back(start);

   float n = m - 1;
   for(int i = x0; i < xEnd; i++){
       line.push_back(Point(i,y0));
       if(n >= 0){
           y0 += 1;
           n -= 1.0;
       }
       else{
           i += 1;
           n += m;
       }
   }
      // while (x < xEnd) {
     //   x++;
       // if (p < 0){
         //   p += twoDy;
       // }
       // else {
         //   y++;
          //  p += twoDyMinusDx;
        //}
       // line.push_back(Point(x, y));
   // }

}

void Point::draw(Attribute A) {
    //draw a point
    int firstIndex = getIndex(x, y, A);
    if (firstIndex == -1) {
        cout << "Error! Given point index is out of range";
        
    }
    else {
        float* PixelBuffer = A.get_buffer();
        //change the values for this point stored in PixelBuffer
        for (int i = 0; i < 3; i++){//one pixel has three values to change
            PixelBuffer[firstIndex + i] = 1;
        }

    }
}

void drawLine(Attribute A, Point start, Point end, string method) {
    vector<Point> line;
    if ( method == "DDA"){
        line = lineDDA(start, end);
    }
    else if (method == "Breshem"){
        line = lineBres(start, end);
    }
    else {
        cout << "Please indicate which method ('DDA' or 'Breshem') you would like to use to draw.";
        return;    
    }
    for (int i = 0; i < line.size(); i++){
        Point p = line[i];
        p.draw(A);
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


//float *PixelBuffer;
void display();
void readInput();
int nPolygon;
Polygon **polygons;
int width = 500;
int height = 500;
Attribute A = Attribute(width, height);
int main(int argc, char *argv[])
{
	readInput();
	//allocate new pixel buffer, need initialization!!
	//PixelBuffer = new float[width * height * 3];

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set window size to 200*200
	glutInitWindowSize(A.get_width(), A.get_height());
	//set window position
	glutInitWindowPosition(100, 100);

	//create and set main window title
	int MainWindow = glutCreateWindow("Hello Graphics!!");
	glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
	//sets display function
	glutDisplayFunc(display);

	glutMainLoop();//main display loop, will display until terminate

    for (int i = 0; i < nPolygon; i++) {
        delete polygons[i];
    }
    delete[] polygons;

	return 0;
}

void readInput() { 
    int nPolygon;
    polygons = new Polygon*[nPolygon];
    cin >> nPolygon;
    for (int i = 0; i < nPolygon; i++) {
        int nPoint;
        cin >> nPoint;
        polygons[i] = new Polygon(nPoint);
        for (int j = 0; j < nPoint; j++) {
            float x, y;
            cin >> x >> y;
            polygons[i] -> setPoint(j, x, y);
        }
    }
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
   
    Point p1(0,0);
    Point p2(499,499);
    //p2.draw(A);
    Point p3(0,250), p4(250,250), p5(250, 0);
    drawLine(A, p1, p2, "DDA");
    drawLine(A, p3, p4, "DDA");
    cout<< "print horizonta line" <<endl;
    drawLine(A, p3, p5, "DDA");
    cout << "print m = -1 line" << endl;
    drawLine(A, p5, p4, "DDA");
    cout << "print vertical line" << endl;
    drawLine(A, p4, p5, "DDA");
   
	//draws pixel on screen, width and height must match pixel buffer dimension
	glDrawPixels(A.get_width(), A.get_height(), GL_RGB, GL_FLOAT,A.get_buffer());

	// draw polygons
	for (int i = 0; i < nPolygon; i++) {
		polygons[i] -> draw();
	}

	//window refresh
	glFlush();
}
