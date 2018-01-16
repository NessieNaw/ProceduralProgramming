#pragma once
#define VEL 4
#define TIM 60

typedef struct tagList
{
	double road;
	int number; 
	double time; 
	int what;
	tagList* pNext;

}List;
typedef struct tagVertex
{
	int* PathLen; //index wierzcjolków przejscia zapisany w tablicy do najlblizszego sklepu 
	bool type; 
	int Number; 
	double Time; 
	List* pVertexList; //lista wierzcholkow
	double Road;
	bool visited; // dfs
	int Shop;

}Vertex;

//-----------------------------
double Dijkstra( Vertex*, int, int );
void DFS( Vertex*, int, int* );

