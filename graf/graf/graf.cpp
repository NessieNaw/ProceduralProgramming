// graf.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include "vertex.h"
#include "prior.h"
#include <stdlib.h>
#include <malloc.h>

#define _GRAPH_


int Read( Vertex* ,FILE* , int );
Vertex* MemInit( int size );
List* MemInitList( );

void Print( FILE*,Vertex* q, int size );

//--------------------------------------
int main( int argc, char* argv[] )
{
	if( argc =! 3 )
	{
		perror( " program start failure " );
		return 1;
	}

	FILE* fin = NULL; 
	if ( ( fin = fopen( argv[1], "r") ) == NULL )
	{
		perror ( "Main ERROR: FILE NOT FOUND!!! " );
			return 1;
	}
	int Size;
	
	fscanf( fin, "%d", &Size );
#ifdef _GRAPH_
		printf( "%d ", Size );
		printf( " \n\n");
#endif
	Vertex* q = MemInit( Size );
	
	Read( q, fin, Size );
	
	fclose( fin );
	
	//bool* visited = ( bool* )calloc( 1, sizeof( bool ) );
	int* visited = ( int* )calloc( Size, sizeof( int ) );
	if( !visited )
	{
		perror( " memory not allocated \n " );
			return 0;
	}
		
			DFS( q, 0, visited );
		
	for( int i = 0; i < Size; i++ )
	{
		if( q[i].type )
			Dijkstra( q, Size, i );
	}
		 
	FILE* output;
	if ( ( output = fopen( argv[2], "a") ) == NULL )
	{
		perror ( "Main ERROR: FILE NOT FOUND!!! " );
			return 1;
	}

	Print( output, q, Size );

	fclose( output );
	
    return 0;
}
//--------------------------------------------
int Read( Vertex* q, FILE* fin, int size  )
{	char c;
	int i = 0;
	// wsk do q[i]

	List* pq = MemInitList();

	while( ( c = getc( fin ) ) != EOF )
	{	ungetc( c , fin );

		int branch = 0; //number of roads
		
		fscanf( fin, "%d", &branch ); // ilosc krawedzi dochodzacych do danego wierzchokla
			printf( "%d ", branch );
		fscanf( fin, "%d", &pq->what );
		fscanf( fin, "%d", &pq->number );

		for( int j = 0; j < branch; j++ )
		{
		//fscanf( fin, "%d", &q[i].Number );
		List* p = MemInitList();

		fscanf( fin, "%d", &p->what ); //czy dom czy sklep
			
		fscanf( fin, "%d", &p->number ); //sasiedni wierzcholek
			
		fscanf( fin, "%lf ", &p->road ); //dlugosc drogi 
				
		p->pNext = q[i].pVertexList;  
		q[i].pVertexList = p;

#ifdef _GRAPH_
			printf( " %d ", p->what );
			printf( " %d ", p->number );
			printf( "%0.2lf ", p->road );
#endif 
		}
		printf( " \n\n " );
		i++;
	}

	//fclose ( fin ); 
	return 0;
}
//--------------------------------------------
void Print( FILE* output, Vertex* q, int size )
{
	for( int i = 0; i < size; i++ )
	{
		List* p = MemInitList();
		if( p->what )
		{
		fprintf( output, " Wierzcholek %d" , p->number );
		fprintf( output, " Typ %d ", p->what );
		fprintf( output, " Droga %d ", p->road );

		fprintf( output, " \n" );
		}
	}
}
//--------------------------------------------
List* MemInitList( )
{
	List* p  = ( List * )calloc( 1, sizeof( List ) );
	if( !p )
	{
		perror( "MEMInitError: memory was not allocated " );
		return 0;
	}
}
//--------------------------------------------
Vertex* MemInit( int size )
{
	Vertex* q = ( Vertex * )calloc( size, sizeof( Vertex ) );
	if( !q )
	{
		perror( "MEMInitError: memory was not allocated " );
		return 0;
	}
}
