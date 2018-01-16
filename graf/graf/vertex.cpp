#include "vertex.h"
#include "prior.h"
#include <stdlib.h>
#include <malloc.h>

double Dijkstra( Vertex* village, int nSize, int nFirst )
{
	PQueue* q = PQItnit( nSize ); 

	double* PathLen = ( double* )calloc( nSize, sizeof( double ) ); // wykreowaæ tablice o rozmiarze maks tyle ile wierzch
	if( !PathLen )
	{
		perror( "DijksreaERROR1: memory was not allocated " );
		return 0;
	}

	double* PathTime = ( double* )calloc( nSize, sizeof( double ) ); 
	if( !PathTime )
	{
		perror( "DijksreaERROR2: memory was not allocated " );
		return 0;
	}

	int* Path = ( int* )calloc( nSize, sizeof( int ) ); 
	if( !Path )
	{
		perror( "DijksreaERROR3: memory was not allocated " );
		return 0;
	}
	
	for( int i = 0; i < nSize; i++ )
	{
		if( i == nFirst ) continue;
		PathLen[i] = INT_MAX;
		Path[i] = -1;
		village[nFirst].PathLen[i] = - 1;
	}

	PQEnqueue( q, nFirst, 0 );
	PathLen[nFirst] = 0;

	while( !( PQIsEmpty( q ) ) )
  {
    int k = PQDequeue( q ); // pobierz z kolejki prioryt elem 
    if( !village[k].type  ) //jesli sklep
	{
		int ptr = 0;
		for( int j = k; j > - 1; j = Path[j] )
		{
			village[nFirst].PathLen[ptr++] = j;
			village[nFirst].Time += PathTime[j];
		}
			//village[nFirst].Number = k;
			//village[nFirst].Time = PathTime[k];
			//village[nFirst].Road = PathLen[k];
			//village[nFirst].PathLen[0] = k;

		for( int j = 0; j < ptr/2 ; j++ )//for( int i = 1; k != nFirst; i++ )
		{
			int temp = village[nFirst].PathLen[ptr - j - 1];
			village[nFirst].PathLen[ptr - j - 1] = village[nFirst].PathLen[j];
			village[nFirst].PathLen[j] = temp;

			/*[nFirst].PathLen[i] = Path[k];
			k = Path[k];*/
		}
		village[nFirst].Shop = k;
		free( PathLen );
		free( Path );
		PQRealese( q );
		return PathLen[k];
	}
     
    List* v = village[k].pVertexList;
	while( v )
	{ 
	  int nNode = v->number; //j-ty nastepnik k, do ktorego jest krawedz;
	  double t = v->road; 
	if( ( PathLen[k] + t ) < PathLen[nNode] )
	  {
        PathLen[nNode] = PathLen[k] + v->road;
		PathTime[nNode] = PathTime[k] + v->time;
		PQEnqueue( q, nNode, PathLen[nNode] );
		Path[nNode] = k;
					//droge tu ma liczyæ???
	  }
	  v = v->pNext;
	}
  }
  
  return 0;
}

//-----------------------------------------
void DFS( Vertex* q, int n, int* visit )   
{
	List* j = q[n].pVertexList;
	visit[n] = 1;
	while( j )				//for( List* j = q[n].pVertexList; j ; j = j->pNext )
	{
		j->time = j->road/VEL * TIM ;
		if( ( visit[j->what] ) == 0 ) 
			DFS( q, j->what, visit ); 
		j = j->pNext;
	}
}