#include "headers.h"
using namespace std;

//float *PixelBuffer;
void display();
void parameter();
void openDisplay();
int nPolygon = 0;
Polygon **polygons = NULL;
int width = 500;
int height = 500;
Attribute attribute = Attribute(width, height);


// UI related
int UIWindow; 

Polygon** readInput(int &nPolygon) {
    cin >> nPolygon; 
    Polygon **newPolygons = new Polygon*[nPolygon];
    for (int i = 0; i < nPolygon; i++) {
        int nPoint;
        cin >> nPoint;
        stringstream ss;
        ss << i;
        string str;
        ss >> str;
        str = "Polygon " + str;
        newPolygons[i] = new Polygon(nPoint, str);
        for (int j = 0; j < nPoint; j++) {
            float x, y;
            cin >> x >> y;
            newPolygons[i] -> setPoint(j, x, y);
        }
    }
    return newPolygons;
}

void menu(int val){
   if (val == 0){
       glutDestroyWindow(UIWindow);
       exit(0);
   } 
   else{
   
   }
   glutPostRedisplay();
   glutAttachMenu(GLUT_LEFT_BUTTON);
}

int main(int argc, char *argv[])
{
    // read input
    polygons = readInput(nPolygon);

    // initialize window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
   
    glutInitWindowSize(attribute.get_width(), attribute.get_height());
    glutInitWindowPosition(100, 100);
    UIWindow = glutCreateWindow("Input UI");
    int m = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 11);
    glutAddMenuEntry("White", 12);
    glutAddMenuEntry("Yellow", 13);
    glutAddMenuEntry("Green", 14);
    glutAddMenuEntry("Blue", 15);
    glClearColor(0, 0, 0, 0);
    glutDisplayFunc(parameter);

    //glutInitWindowSize(A.get_width(), A.get_height());
    //glutInitWindowPosition(700, 100);
    ////create and set main window title
    //int MainWindow = glutCreateWindow("Hello Graphics!!");
    //glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    ////sets display function
    //glutDisplayFunc(display);

    glutMainLoop();//main display loop, will display until terminate

    for (int i = 0; i < nPolygon; i++) {
        delete polygons[i];
    }
    delete[] polygons;
    
    return 0;
}
void openDisplay(){
    glutInitWindowSize(attribute.get_width(), attribute.get_height());
    glutInitWindowPosition(700, 100);
    //create and set main window title
    int MainWindow = glutCreateWindow("Hello Graphics!!");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    //sets display function
    glutDisplayFunc(display);
}

void parameter(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    int testMenu = glutCreateMenu(menu);

    //draws pixel on screen, width and height must match pixel buffer dimension
   // glDrawPixels(A.get_width(), A.get_height(), GL_RGB, GL_FLOAT, A.get_buffer());
    //window refresh
    openDisplay();
    glFlush();
}

//main display loop, this function will be called again and again by OpenGL
void display() {
    drawAllPolygons(attribute, polygons, nPolygon);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
   //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(attribute.get_width(), attribute.get_height(), GL_RGB, GL_FLOAT, attribute.get_buffer());
    
    //window refresh
    glFlush();
}
