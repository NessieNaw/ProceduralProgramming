// FIFOLIST.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.

#include "fifo.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#define _FIFO_DBUG_

int main( int argc, char* argv[] )
{
	QueueList* Que = QCreate( );
	if( !Que )
	{
		perror( " Main: Memory was not allocated " );
		return 1;
	}
	QEnque( Que, 1 ); 
	QEnque( Que, 2 );
#ifdef _FIFO_DBUG_
	printf( " %d \n", *( Que->pFront ) );
	printf( "\n" );
	printf( " %d \n", *( Que->pTail ) );
		printf( "\n" );
#endif
	QClear( Que );
	printf( "\n -------------- \n" );
	QEnque( Que, 3 );
	QEnque( Que, 4 );
	QEnque( Que, 5 );
	QDecque( Que );
#ifdef _FIFO_DBUG_
	printf( " %d \n", *( Que->pFront ) );
	printf( "\n" );
	printf( " %d \n", *( Que->pTail ) );
		printf( "\n" );
#endif
	QDel( &Que );

    return 0;
}

