#include "stdafx.h"
#include "backtracking.h"

#define DEPTH_MIN 10
#define N 10;
#define M 10

#define _Sea_

int CreateSea( int*** pTab, int nRow, int nCol );
void DeleteSea( int*** pTab, int, int  );
void PrintSea( int** pTab, int nrow, int ncol ) ;

//----------------------------
int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		perror( " MAIN!: argc != 2" );
		return 1;
	}
	
	int nrow = N;
	int ncol = M;

	//int** p = NULL;

	int** ptab = NULL; //( int** )calloc( nrow, sizeof( int ) );
	if( !CreateSea( &ptab, nrow, ncol ) )
		{
		perror( " Memory Error: Memory was not allocated " );
		return 1;
		}

		char* f = argv[1];
	setTab( f, ptab, nrow, ncol );
	



	//int ** q = NULL;
	int** proot = NULL; // ( int** )calloc( nrow, sizeof( int ) );
	if( !CreateSea( &proot, nrow, ncol ) || !proot )
		{
		perror( " Memory Error: Memory was not allocated " );
		return 1;
		}
	int x = 0;
	int y = 0;
	int xd = 9;
	int yd = 9;

	if( !root( ptab, nrow, ncol, DEPTH_MIN, x, y , proot, xd, yd ) )
	{
		perror( "** Nie ma mozliwosci doplynac do portu!!\n\n" );
		return 0;
	}
#ifdef _Sea_

	PrintSea( proot, nrow, ncol );
#endif 
	DeleteSea( &ptab, nrow, ncol );
	DeleteSea( &proot, nrow, ncol );
    return 0;
}

//----------------------------
//----------------------------

int CreateSea( int*** pTab, int nRow, int nCol )
{
	*pTab  = ( int** )calloc( nRow,sizeof( int* ) );
	if( !pTab )
	{
		perror( "Create1: Sea can not be created" );
		return 0;
	}
	int** p = *pTab;
		for( int i = 0; i < nRow; i++ )
	{
		*p = ( int* )calloc( nCol,sizeof( int ) );
			if( !(*p++) ) 
			{
			perror( "Create2: Sea can not be created" );
			return 0;
		}
	}
	return 1;
}
//----------------------------
void DeleteSea( int*** pTab, int nrow, int ncol )
{
	int** p = *pTab; 
	for( int i = 0; i < nrow; i++ )
	//for( int j = 0; j < ncol; j++ )
		free( *p++ );
	free( *pTab );
	*pTab = NULL;

}
//----------------------------
void PrintSea( int** pTab, int nrow, int ncol ) 
{
	//double** p = pTab;
	for( int i = 0; i < nrow; i++ )
	{
		int* v = *pTab++;//*p++;
		for( int j = 0; j < ncol; j++ )
		{
			printf( "%d ", *v++ );
		}
	printf( "\n" );
	}
}
//----------------------------
