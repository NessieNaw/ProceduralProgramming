#include "stdafx.h"
#include "matx.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>//fscanf


#define _MATX_BUG_

void ReadData( FILE* , double**, double*, int );

//==========================================
int main( int argc, char* argv[] )
{
if( argc != 2 )
	{
		perror( " MAIN!: argc != 2" );
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

	double** p = NULL;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	double* B = ( double* )calloc( Size, sizeof( double ) );
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	if( !CreateMatrix( &p, Size ) || !B  )
	{
		perror( " Memory Error: Memory was not allocated " );
		return 1;
	}

	ReadData( fin, p, B, Size );
	fclose( fin );


#ifdef _MATX_BUG_
	printf( "\n MAIN MATRIX \n\n" );
	PrintMatrix( p, Size );
#endif
// - - - - - - - - - - - - - - 	
	double d = Det( p, Size );
	printf( "\n det \n= %lf ", d );

	if( fabs( d ) < 1e-17 )
	{
		perror( " \n\n ERROR: DET = 0! NEXT OPERATIONS ARE NOT ALLOWED \n\n" );
		DeleteMatrix( &p, Size );
		return 2;
	}

// - - - - - - - - - - - - - - 	

	double** pI = NULL;
	CreateMatrix( &pI, Size );
	if( !CreateMatrix( &p, Size ) || !B  )
	{
		perror( " Memory Error: Memory was not allocated " );
		return 1;
	}
// - - - - - - - - - - - - - - 		
	InverseMatrix( pI, p, Size , d ); 
#ifdef _MATX_BUG_
	printf(" \n INVERSED MATRIX \n\n " );
	PrintMatrix( pI, Size );
#endif
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	double* pRes = ( double* )calloc( Size, sizeof( double ) );
	if( !pRes  )
	{
		perror( " Memory Error: Memory was not allocated " );
		return 1;
	}

	LayoutEqu( pI, B, pRes, Size );
	printf("\n RESULTS:\n\n");
	for( int i = 0; i < Size; i++ )
	{
		printf( "%.2lf ", pRes[i] );
		putchar( '\n');
	}
// - - - - - - - - - - - - - - 	
	DeleteMatrix( &p, Size );
	DeleteMatrix( &pI, Size );
#ifdef _MATX_BUG_
	printf(" \n MTRIX WAS DELETED \n\n " );
#endif
// - - - - - - - - - - - - - - 	
	free( pRes );
	free( B );
	
    return 0;
}
//==========================================
void ReadData( FILE* fin, double** pMatrix, double* B, int nDim ) 
{	
	for( int i = 0; i < nDim; i++ )
	{
		double*p = *pMatrix++;
		for( int j = 0; j < nDim; j++ )
			fscanf( fin, "%lf", p++ );
		fscanf( fin, "%lf", B++ );
	}
}
//==========================================

