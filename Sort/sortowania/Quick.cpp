#include "Quick.h"
#include <math.h>
#include <stdlib.h>

void QuickSort( int* pTab, int L, int R )
{	 
	int i = L;
	int j = R;
	int x = *( pTab + ( ( i + j )/2 ) );
	do
	{
		while( pTab[i] < x )																																	//for( pTab ;  *(pTab+i) < x ; pTab++)
			i++;
		while( x < pTab[j] ) 
			j--;
		if( i <= j )
		{
			int temp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = temp;
			i++;
			j--;
		}
	} while( i<=j );
	if( L<j ) QuickSort( pTab, L, j );
	if( R>i ) QuickSort( pTab, i, R );
}
