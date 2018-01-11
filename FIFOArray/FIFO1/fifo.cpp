#include "fifo.h"
#include <stdlib.h>
#include <memory.h>

//======================================================
Queue* QCreate( int nSize )
{
	Queue* Que = ( Queue* )calloc( 1, sizeof( Queue ) );
	if( !Que )
	{
		perror( "QCreate1: memory not allocated" );
		return NULL;
	}
	Que->nMaxElem = nSize;
	Que->pTab = ( int* )calloc( nSize, sizeof( int ) );
	if( !Que->pTab )
	{
		free(Que);
		perror( "QCreate2: memory not allocated" );
		return NULL;
	}
	return Que;
}
//======================================================
int QEmpty( Queue* que ) 
{
	return !( que->nCurrent ); 
}
//======================================================
void QEnque( Queue* que, int x )
{	
	if( que->nCurrent == que->nMaxElem ) 
	{
		perror( "\n QENGUE: \n: Overflow!!! \n " );
		return;
	}
	que->pTab[que->pTail] = x; 
	que->pTail = ( que->pTail + 1) % ( que->nMaxElem );
	que->nCurrent++;
}
//======================================================
int QDecque( Queue* que )
{
	if( QEmpty( que ) )
	{
		perror( "QDeque: tab is empty" );
		return 1;
	}
	int p = que->pTab[que->pFront];
	que->pFront = ( que->pFront +1 ) % ( que->nMaxElem );
	que->nCurrent--;
	return p;
}
//======================================================
void QClear( Queue* q )
{
	while( !QEmpty( q ) )
		QDecque( q );
		q->pFront = q->pTail = 0; 
}
//======================================================
void QDel( Queue** q )
{
	QClear( *q );
	free( *q );
	*q = NULL; 
}

//======================================================
//======================================================
//======================================================