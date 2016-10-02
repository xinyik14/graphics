project1 : HelloGraphics.cpp
	g++ -std=c++11 -o $@ $< -lGL -lGLU -lglut

clean:
	rm project1 
	rm *.o 
