all: transform
transform:transform.o shader.o
	g++ transform.o shader.o  -o transform -rdynamic -lGLU -lGL /usr/local/lib/libglfw3.a /usr/local/lib/libGLEW.a -lGLU -lGL -lGLU -lXrandr -lXext -lX11 -lrt -ldl -lrt -lm -lX11 -lpthread -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -ldl -lrt -lm -lX11 -lpthread -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL
transform.o: transform.cpp
	g++ -c transform.cpp
shader.o: shader.cpp
	g++ -c shader.cpp
clean:
	rm -rf *.o transform

