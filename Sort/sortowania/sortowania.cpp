#include <stdlib.h> 
#include "stdafx.h"
#include <time.h>
#include <malloc.h>
#include <iostream>
#include <memory.h> 
#include <string.h>
#include <stdarg.h>

using namespace std;

//----sortowania-----
#include "InsertionSelectionHalf.h"
#include "MergeMerge.h"
#include "Quick.h"
#include "StackMix.h"

//-------------------
typedef void( *pF )( int*, int ); //define pointer type

void PrintTab( int* pTab, int nSize );
int InitTab( int* pTab, int nSize );
int Test( pF sorttab[], const char* nametable[], int nSizeTabf, int* pTab, int* pTabTest, int nSizeTab  );
void Copy( int*, int*, int );

//-----------------------------
#define RANDOM 100
#define COL 20
#define _DBUG_
//=================================
int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		perror( " MAIN ERROR: Program run: <name> <size of array> \n " );
		return 1;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	int SIZE = atoi( argv[1] );
	pF sorttab[] = { InsertionSort, SelectionSort, HalfSort ,MixSort , Stacksort , MergeSortNR,  }; //names of functions are pointers
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	int* Tab = ( int* )malloc( SIZE*sizeof( int ) );
	memset( Tab, 0, SIZE*sizeof( int ) );
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	int* TestTab = ( int* )malloc( SIZE* sizeof( int ) );
	memset( TestTab, 0, SIZE*sizeof( int ) );
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	int nSize = sizeof( sorttab )/sizeof( pF );
	const char* nametable[] = { " Insertion ", "Selection", "Half", "Mix ", "Stack" , "MergeNR" };
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	Test( sorttab, nametable, nSize, Tab, TestTab, SIZE );

	printf( " \n\n ");


	free( TestTab );
	free( Tab );
    return 0;
}
//=================================

void PrintTab( int* pTab, int nSize )
{
	for ( int i=0; i<nSize; i++ )
	{
		printf("%d ", *pTab++);
		if( (i+1)%COL == 0 )
			printf("\n");
	}
	printf("\n\n");
}
//=================================

int InitTab( int* pTab, int nSize )
{
	srand( ( unsigned ) time( NULL ) );
	for( int i = 0; i < nSize; i++ )
		*pTab++ = ( rand() % RANDOM ) + 1; 
	return 0;
}

//=================================
int Test( pF sorttab[], const char* nametable[], int nSize, int* pTab, int* pTest, int nSizeTab )
{
	InitTab( pTab, nSizeTab );

#ifdef _DBUG_
	printf( "\n" ); 
	PrintTab( pTab, nSizeTab ); 
#endif
	printf( "\n" ); 
	printf( "ilosc sortowan z funcji %d " , nSize );
	printf( "\n\n" ); 
	printf( " plus dwa sortowania spoza funcji \n\n" );

	for( int i = 0; i < nSize; i++ )
	{	
		Copy( pTest, pTab, nSizeTab );
#ifdef _DBUG_
		PrintTab( pTab, nSizeTab ); 
#endif
		clock_t poczatek = clock();
		sorttab[i]( pTest, nSizeTab );
		clock_t koniec = clock(); 

		double dif = ( double )( koniec - poczatek )/( CLOCKS_PER_SEC );
#ifdef _DBUG_
	PrintTab( pTest, nSizeTab ); 
	printf( "\n" ); 
#endif	
	printf( " czas sort: %s %f", nametable[i], dif );
	printf( "\n\n" ); 
	
	}
	
//**********MERGESORT******************
	Copy( pTest, pTab, nSizeTab );
#ifdef _DBUG_
		PrintTab( pTab, nSizeTab ); 
#endif
		int* temp = ( int* )malloc( nSizeTab*sizeof( int ) );
		memset( temp, 0, nSizeTab*sizeof( int ) );
		clock_t poczatekM = clock();
		int a = 0;
		MergeSort( pTest, temp, nSizeTab, a, nSizeTab - 1 );
		int i = 0;
		clock_t koniecM = clock(); 

	double difM = ( double )( koniecM - poczatekM )/( CLOCKS_PER_SEC );
#ifdef _DBUG_
	PrintTab( pTest, nSizeTab ); 
#endif

	printf( " czas sort Merge:  %f",  difM );
	printf( "\n\n" );


//**************************************
	
//**********Quick SORT******************
	Copy( pTest, pTab, nSizeTab );
#ifdef _DBUG_
		PrintTab( pTab, nSizeTab ); 
#endif
		clock_t poczatekQ = clock();
		int j = 0;
		QuickSort( pTest, j, nSizeTab-1 );
		clock_t koniecQ = clock(); 

	double difQ = ( double )( koniecQ - poczatekQ )/( CLOCKS_PER_SEC );
#ifdef _DBUG_
	PrintTab( pTest, nSizeTab ); 
#endif
	printf( " czas sort Quick:  %f",  difQ );
	printf( "\n\n" ); 

	
//**************************************
	return 0;
}

//=================================
void Copy( int* TestTab, int* pTab, int size )
{
	memcpy( TestTab, pTab, sizeof( int )*size) ; //number of elements * size of element  is a number of memory to be copied from ptab to testtab
}//=================================

