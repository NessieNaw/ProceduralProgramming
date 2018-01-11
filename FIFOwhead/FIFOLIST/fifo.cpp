
#include "fifo.h"
#include <stdlib.h>
#include <memory.h>

//======================================================
QueueList* QCreate( )
{
	QueueList* que = ( QueueList* )calloc( 1, sizeof( QueueList ) );
	QItem* p = ( QItem* )calloc( 1, sizeof( QItem ) );
	if( !que || !p )
	{
		perror( " QCreate: Memory was not allocated " );
		return NULL;
	}
	que->pFront = que->pTail = p;
	return que;
}
//======================================================
int QEmpty( QueueList* q )
{
	return !( q->pFront->pNext );//bo na nastepny
}
//======================================================
void QEnque( QueueList* q, int x )
{
	QItem* v= ( QItem* )calloc( 1, sizeof( QItem ) );
	if( !v )
	{
		perror( " QEnque: Memory was not allocated " );
		return;
	}
	q->pTail->pNext = v;
	q->pTail = v;
	v->nKey = x;
	
}
//======================================================
int QDecque( QueueList* q )
{
	if( QEmpty( q ) )
	{
		perror( " \nQDecque!!! \n" );
		return 1;
	}
	QItem* v = q->pFront->pNext;
	int r = v->nKey;
	q->pFront->pNext = v->pNext;
	if ( QEmpty ( q ) )
		q->pTail = q->pFront;
	return r;
}
//======================================================
void QClear( QueueList* q ) 
{
	while( !QEmpty( q ) )
		QDecque( q );
}
//======================================================
void QDel( QueueList** q )
{
	QClear( *q );
	free( *q );
	*q = NULL; 
}
//======================================================
//======================================================
//======================================================
//======================================================
//======================================================
//======================================================