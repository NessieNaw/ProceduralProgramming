#include "stdafx.h"
#include "headFIFO.h"
#include <stdlib.h>
#include <memory.h>

//======================================================
QueueList* QCreate( )
{
	QueueList* que = ( QueueList* )calloc( 1, sizeof( QueueList ) );
	if( !que )
	{
		perror( " QCreate: Memory was not allocated " );
		return NULL;
	}
	que->pFront = que->pTail = NULL;
	return que;
}
//======================================================
int QEmpty( QueueList* q )
{
	return !q ->pFront;
}
//======================================================
void QEnque( QueueList* q, int x )
{
	QItem* que = ( QItem* )calloc( 1, sizeof( QItem ) );
	if( !q )
	{
		perror( " QEnqueue: Memory was not allocated " );
		return ;
	}
	if( QEmpty( q ) )
		q->pFront = que;
	else
		q->pTail->pNext = que;
		que->nKey = x;
		q->pTail = que;
}
//======================================================
int QDecque( QueueList* q )
{
	if( QEmpty( q ) )
	{
		perror( " \nQDecque!!! \n" );
		return 1;
	}
	QItem* que = q->pFront;
	int x = que->nKey;
	q->pFront = que->pNext;
	free( que );
	if( QEmpty( q ) ) 
		q->pTail = NULL;
	return x;
}
//======================================================
void QClear( QueueList* q ) 
{
	while( !QEmpty( q ) )
		QDecque( q );
		q->pFront = NULL;
		q->pTail = NULL;
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