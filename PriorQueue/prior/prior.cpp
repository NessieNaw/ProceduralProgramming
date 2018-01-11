// prior.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include "kolprior.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>

#define SIZE 10
#define LOS 100
int main( int argc, char* argv[] )
{
	PQueue* PQue = PQItnit( SIZE );
	for( int i = SIZE - 1 ; i > 0; i-- )
	{
		int key = (rand()  % LOS ) + 1;
		PQEnqueue( PQue, i + 1 , key );
		
	}
	for( int i = 0; i < SIZE ; i++ )
	{
		
		printf( " prior %d klucz %d  \n\n" ,  PQue->pTab[i].nPrior ,PQue->pTab[i].nKey );
	}
	PQEnqueue( PQue, 6, 100 );
	printf( " ================ \n\n" );
	for( int i = 0; i < SIZE ; i++ )
	{
		
		printf( " prior %d klucz %d  \n\n" ,  PQue->pTab[i].nPrior ,PQue->pTab[i].nKey );
	}
	printf( " ================ \n\n" );

	PQPrint( PQue, 0 );
}

