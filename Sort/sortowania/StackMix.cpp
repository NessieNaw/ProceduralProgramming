#include "StackMix.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
void update( int* t, int i, int n );
void Stacksort( int* t, int nSize )
{
for( int i = ( nSize/2 ) + 1; i >= 0; i--) 
    update( t, i, nSize );


   for( int i = nSize - 1; i > 0; i-- )
	{
		int temp = t[i];
		t[i] = t[0];
		t[0] = temp;
		update( t, 0, i - 1 );
	}
}	
//--------------------------
void update( int* pTab, int l, int p) 
{
	int i = l;
	int j = 2*i+1;
	int x = pTab[i];
	while( j <= p )
	{
		if( j < p )
		{
			if( pTab[j] < pTab[j+1] )
				j++;
		}
		if( x >= pTab[j] )break;
		pTab[i] = pTab[j];
		i = j;
		j = 2*i +1;
	}
	pTab[i] = x;
}
//=============================================
void MixSort( int* t, int n )
{	
	int k = n - 1;
	int l = 1;
	int p = n - 1;
	
while( l < p )
	{
for( int j = p; j >= l; j-- ) 
{
	if( t[j-1] > t[j] )				
	{
		int	x =  t[j-1];						 
		 t[j-1] =  t[j];					
		 t[j] = x;								
	}
	k = j;
}
	l = k + 1; 
for( int j = l; j <= p; j++ )
{
	if(  t[j-1] >  t[j] )				 
	{
		int x =  t[j-1];						 
		 t[j-1] =  t[j];				
		 t[j] = x;								
	}
	k = j;
}
	p = k-1; 
}
}
//=============================================
