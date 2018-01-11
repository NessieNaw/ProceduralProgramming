
#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>  // min

#include "MergeMerge.h"

//======================================================
void Merge( int*, int*, int , int , int , int  );
void MergeSort( int* t, int* temp, int nSize, int l, int p )
{
	if( l < p )
	{
		int m = ( l + p )/2;
		MergeSort( t, temp, nSize, l, m );
		MergeSort( t, temp, nSize, m + 1, p);
		Merge( t, temp, nSize, l, m , p ); 
	}
}
//---------------------------------

void Merge( int* t, int* temp, int nSize, int l, int m, int p )
{
	memcpy( temp, t, nSize*sizeof( int ) );
	int i = l;
	int j = m + 1;
	int q = l;		
	
while( (i <= m) && (j <= p) )
{										
	if( t[j] < temp[i] )		
		t[q++] = t[j++];	
	else
		t[q++] = temp[i++];					
}										
while( i <= m )									
	t[q++] = temp[i++];			
									
}										
//======================================================
bool Copy( int* t, int* i, int* tmp, int* ix, int size )
{

		t[(*i)++] = tmp[(*ix)++];
		if( *ix == size )
			return true;
		return tmp[*ix -1 ] > tmp[*ix];
			
}
//------------------------------------
void CopySerie( int* t, int* i, int* tmp, int* ix, int size )
{
	bool end = false;
		do
		{end = Copy( t, i, tmp, ix, size );
		}while( !end );
}
//------------------------------------
void MergeSortNR( int* t, int nSize )
{
	int* tab0 = ( int* )malloc( nSize* sizeof( int ) );
	memset( tab0, 0, nSize*sizeof( int ) );

	int* tab1 = ( int* )malloc( nSize* sizeof( int ) );
	memset( tab1, 0, nSize*sizeof( int ) );

	int nserie;
do{
	
	int i = 0;
	int j = 0;
	int k = 0;

	while( i < nSize ) 
	{
		while( ( i < nSize -1 ) && ( t[i] <= t[i+1] ) )
			tab0[j++] = t[i++];
		if( i < nSize )
			tab0[j++] = t[i++]; 
		while( ( i < nSize - 1 ) && ( t[i] < t[i+1] ) )
			tab1[k++] = t[i++];
		if( i < nSize )
			tab1[k++] = t[i++];
	}
	int nlast1 = j;
	int nlast2 = k;
	nserie = 0;
	i = 0;
	k = 0;
	j = 0;
	while( ( j < nlast1)&&( k < nlast2 ) )
	{
			bool endserie = false;
			while( !endserie )
			{
				if( tab0[j] <= tab1[k] )
				{
					endserie = Copy( t, &i, tab0, &j, nlast1 );
					if( endserie )
					CopySerie( t, &i, tab1, &k, nlast2 );
				}
				else
					{
					endserie = Copy( t, &i, tab1, &k, nlast2 );
					if( endserie )
					CopySerie( t, &i, tab0 , &j , nlast1 );
				}
			}
			nserie++;
	}
	while( j < nlast1 )
	{
		CopySerie( t, &i, tab0, &j, nlast1 );
		nserie++;
	}
	while( k < nlast2 )
	{
		CopySerie( t, &i, tab1, &k, nlast2 );
		nserie++;
	}
} while( nserie > 1 );

free(  tab0 );
free( tab1 );
}
