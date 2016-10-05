#include "headers.h"

using namespace std;

// lineSpecial deal with sepcial cases such as line with m=0, m=1 and m=infinite
std::vector<Point> lineSpecial(const Point &start, const Point &end) {
    int x0 = start.get_x(), xEnd = end.get_x(), y0 = start.get_y(), yEnd = end.get_y();
    int dy = yEnd - y0, dx = xEnd - x0;
    int yStep = abs(dy), xStep = abs(dx);
    std::vector<Point> line;
    if (dy == 0){
		//when it's a horizontal line
        int s = dx/xStep;
        for(int i = 0; i <= xStep; i++){
            //deal with both cases that dx > 0 and dx < 0
            int x = x0 + i*s;
            line.push_back(Point(x, y0));
        }
    }
    else if (dx == 0){
		//when it's a horizontal line
        int s = dy/yStep;
        for(int i = 0; i <= yStep; i++ ){
            //deal with both cases that dy > 0 and dy < 0
            int y = y0 + i*s;
            line.push_back(Point(x0, y));
        }
    }
    else{
		//no need for float because m is either -1 or 1
        int yIncrement = dy/yStep;
		//need to know the direction to go(from left to right or vice verse) as well
        int xIncrement = dx/xStep;
        for(int i = 0; i <= xStep; i++){
            line.push_back(Point(x0 + i*xIncrement, y0 + i*yIncrement));
        }
    }
    return line;
}

std::vector<Point> lineDDA(const Point &start, const Point &end){
    int dy = end.get_y() - start.get_y(), dx = end.get_x() - start.get_x();
    int x0 = start.get_x(), y0 = start.get_y();
    int xStep = fabs(dx);
    int yStep = fabs(dy);
    if ((xStep == yStep) || (dy == 0) || (dx == 0)){
        // special cases: m=1/-1, horizontal line or vertical line
        return lineSpecial(start, end);
    }
    std::vector<Point> line;
    
    int xIncrement = dx/xStep; 
    int yIncrement = dy/yStep;
    if (yStep < xStep){
        //the slop is gentle, so march through xi 
        //0< m < 1 or 0 > m > -1
        if (dx < 0){
            return lineDDA(end, start);
        }
        float m = (float)dy/ (float)dx;
        for(int i = 0; i <= xStep; i++){
            float yExact = (float)y0 + (float)i * m;
            int y = round(yExact);
            line.push_back(Point(x0 + i*xIncrement, y));
        }
        return line;
    }
    else{
        //the only case left here is when m > 1 or m < -1
        //so we march through yi instead
        if (dy < 0){
            return lineDDA(end, start);
        }
        float m = (float)dx/ (float)dy;
        for(int i = 0; i <= yStep; i++){
            float xExact = (float)x0 + (float)i * m;
            int x = round(xExact);
            line.push_back(Point(x, y0 + i*yIncrement));
        }
        return line;
    }
}

std::vector<Point> lineBres(const Point &start, const Point &end){
    int dy = end.get_y() - start.get_y(), dx = end.get_x() - start.get_x();
    int x0 = start.get_x(), y0 = start.get_y();
    int xStep = fabs(dx);
    int yStep = fabs(dy);
    if ((xStep == yStep) || (dy == 0) || (dx == 0)){
        //special cases: m=1/-1, horizontal line or vertical line
        cout << "Go to special cases" << endl;
        return lineSpecial(start, end);
    }
    std::vector<Point> line;
    line.push_back(start);

    float m = (float)dy/(float)dx; 
    if (yStep <  xStep){
        //the slop is gentle, so march through xi 
        //0< m < 1 or 0 > m > -1
        if (x0 > end.get_x()){
          //if the line starts from right to left
          return lineBres(end, start);
        }
        int pi = 2*dy-dx;
		int y = y0;
		//y is y(i+1) and y0 is y(i)
		for (int i = 1; i < xStep; i++){
            if (pi >= 0 && m > 0){
			    y += 1;
				//start from y0 but iterate through yEnd
			}
            else if (pi <= 0 && m < 0){
                y -= 1;
            }
            line.push_back(Point(x0 + i, y));
		    //prepare for the next iteration
		    pi = pi+2*dy-2*dx*(y-y0);
            //pi is now p(i+1)
			y0 = y;
			//y0 is now y(i+1)
		}
	}
	else {
        //the only case left here is when m > 1 or m < -1
        //so we march through yi instead
        if (y0 >  end.get_y()){
			//if the line starts from right to left
            return lineBres(end, start);
        }
        int pi = 2*dx - dy;
		int x = x0;
		//x is x(i+1) and x0 is x(i)
		for (int i = 1; i < yStep; i++){
		    if (pi >= 0 && m > 0){
			    x += 1;
				//start from x0 but iterate through xEnd
			}
            else if (pi <= 0 && m < 0){
                x -= 1;
            }
            line.push_back(Point(x, y0 + i));
		    //prepare for the next iteration
		 	pi = pi + 2*dx - 2*dy*(x - x0);
            //pi is now p(i+1)
            x0 = x;
			//x0 is now x(i+1)
		}
    }
    line.push_back(end);
	return line;				
}

void drawPoint(const Attribute &attribute, const Point &p) {
    //draw a point
    int firstIndex = getIndex(p.get_x(), p.get_y(), attribute);
    if (firstIndex == -1) {
        cout << "Error! Given point index is out of range";
        
    }
    else {
        float* PixelBuffer = attribute.get_buffer();
        //change the values for this point stored in PixelBuffer
        for (int i = 0; i < 3; i++){//one pixel has three values to change
            PixelBuffer[firstIndex + i] = 1;
        }
    }
}

void drawLine(const Attribute &attribute, const Point &start, const Point &end, string method) {
    vector<Point> line;
    if (method == "DDA"){
        line = lineDDA(start, end);
    }
    else if (method == "Bres"){
        line = lineBres(start, end);
    }
    else {
        cout << "Please indicate which method ('DDA' or 'Breshem') you would like to use to draw.";
        return;    
    }
    for (int i = 0; i < line.size(); i++){
        Point p = line[i];
        drawPoint(attribute, p);
    }
}

void drawPolygon(const Attribute &attribute, const Polygon &p) {
    Point** pArray = p.get_array();
    int nPoint = p.get_n();
    int i = 0;
    for (int j = 1; j < nPoint; j++) {
        //cout << i << " " << j << endl;
        Point start = *pArray[i];
        Point end = *pArray[j];
        //cout << start << end;  
        drawLine(attribute, start, end, "DDA");
        i++;
    }
    drawLine(attribute, *pArray[i], *pArray[0], "DDA");
}

void drawAllPolygons(const Attribute &attribute, Polygon** polygonsFile, int nPolygons) {
    for(int i = 0; i < nPolygons; i++) {
        drawPolygon(attribute, *polygonsFile[i]);
    }
}

int getIndex(int x, int y, const Attribute &attribute) {
    //function to calculate the corresbonding place of a point in PixelBuffer
    if ((x<0) || (y<0) || (x>attribute.get_width()) || (y>attribute.get_height())){
        return -1;
    }
    else {
        int h = y*attribute.get_width()*3;
        int w = x*3;
        return h+w;
    }
}
