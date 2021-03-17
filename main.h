
#include<iostream>
#include<vector>
#include <stdlib.h> // abs
#include <algorithm> // min
#include<cmath>
#include <fstream> 
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<set>
#include<string>

using namespace std;

enum color {
	banned = -2,
	initial = -1,
	red = 0,
	green = 1
};

struct rect {
	int x1;
	int y1;
	int x2;	// larger than x1
	int y2; // larger than y1
};

struct adjacent_vertex {
	int vertex_number = -1;                   //vertex的編號,initial設成-1
	color shape_color = initial;              //vertex的顏色,initial設成-1
	int graph = -1;                           //graph的編號,initial設成-1
	adjacent_vertex* adjacent = NULL;         //Link List的ptr,initial設成NULL
};

struct vertex {
	int vertex_number = -1;                   //vertex的編號,initial設成-1
	rect position;                          //vertex的座標
	color shape_color = initial;              //vertex的顏色,initial設成-1
	int graph = -1;                           //graph的編號,initial設成-1
	adjacent_vertex* adjacent = NULL;         //Link List的ptr,initial設成NULL
};

struct window {
	rect position;
	float red_density;
	float green_density;
};


/********************* Rectangular Size ********************/
int ALPHA;
int BETA;

/******************** Funtion prototype *********************/
vertex AssignVertex(int, int, int, int, int);
int ConstructLinkList(vector<vertex>, vertex, int, int, int, int);
void SetColor(vector<vertex>*, struct vertex*, color);
void SetBanned(vector<vertex>*, struct vertex*);
void SetGraph(vector<vertex>*, struct vertex*, int);
void draw_color(int OMEGA, rect bound, int graph_quantity, vector<vertex>* vertices, int vertex_quantity, int* window_quantity_ptr, vector<window> windows);
/********************* part1_declaration ********************/
rect BoundingBox;
int graph = 0;
vector<vertex> vertice;
vector<vertex>* vertice_ptr;

/********************* part2_declaration ********************/
int OMEGA;
int window_quantity;
vector<window> windows;
int vertex_quantity;
ofstream file;