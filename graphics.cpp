#include "headers.h"

using namespace std;

int round(float d){
     return floor(d + 0.5);
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
}

void drawPoint(Attribute A, Point p) {
    //draw a point
    int firstIndex = getIndex(p.get_x(), p.get_y(), A);
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
        drawPoint(A, p);
    }
}
