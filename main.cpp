#include "headers.h"
using namespace std;

//float *PixelBuffer;
void display();
//Polygon** readInput();
int nPolygon;
Polygon **polygons;
int width = 500;
int height = 500;
Attribute A = Attribute(width, height);



int main(int argc, char *argv[])
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(A.get_width(), A.get_height());
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
    pair<Polygon**, int> t = readInput();
    Polygon** polyList = t.first;
    int nPoly = t.second;
    
    pair<int, int> y = polyList[0] -> findMaxAndMinY();
    cout << "max is " << y.first << " and min is " << y.second << endl;
    drawAllPolygons(A, polyList, nPoly);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
   //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(A.get_width(), A.get_height(), GL_RGB, GL_FLOAT, A.get_buffer());
    
    //window refresh
    glFlush();
}
