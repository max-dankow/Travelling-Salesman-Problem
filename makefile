all:tsp

tsp:main.cpp cpathfinder.cpp  cgraph.cpp cdisjointset.cpp Drawer.cpp
	g++ main.cpp cpathfinder.cpp  cgraph.cpp cdisjointset.cpp Drawer.cpp -lGL -lGLU -lglut -std=c++11 -o tsp

main.cpp:
cpathfinder.cpp:
cgraph.cpp:
cdisjointset.cpp:
Drawer.cpp: