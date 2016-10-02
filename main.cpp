#include "headers.h"
using namespace std;

//float *PixelBuffer;
void display();
void readInput();
int nPolygon;
Polygon **polygons;
int width = 500;
int height = 500;
Attribute A = Attribute(width, height);

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

//main display loop, this function will be called again and again by OpenGL
void display() {
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
    
    //window refresh
    glFlush();
}
