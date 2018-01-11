#include "InsertionSelectionHalf.h"
#include "stdafx.h"
#include <iostream>
#include <string.h>

using namespace std;

//=================================
void InsertionSort( int* t, int nSize )
{	
	 for( int i = 1; i < nSize; i++ )
    {
        int x = t[i];								
        int j = i - 1;
        while( ( j >= 0 )&&( t[j] > x ) )			
			t[j+1] = t[j--];									    
														
		t[j+1] = x;
    }
}
//=================================

 void SelectionSort( int* t, int nSize )
{
 for( int i = 0; i < nSize-1; i++ )
    {
        int min = t[i]; 
		int imin = i;
        for( int j = i + 1; j <= nSize-1; j++ )
        {
            if( t[j] < min )
            {
				min = t[j];
				imin = j;													    
            }
        }
		t[imin] = t[i];
		t[i] = min;
   }
}

//=================================

void HalfSort( int* t, int nSize ) 
{
	
	for( int i = 1; i < nSize; i++)
	{
		int x = t[i];
		int l = 0;
		int p = i - 1;
		while( l <= p )
		{
			int m = ( l + p )/2;
			if( x < t[m] )
				p = m - 1; 
			else
				l = m + 1;
		}
		for( int j = i - 1; j >= l; j-- )
			t[j+1] = t[j];
		t[l] = x;
	}
}

//=================================
