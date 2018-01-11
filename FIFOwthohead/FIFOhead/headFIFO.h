#pragma once
#define _FIFO_HEAD_
#ifdef _FIFO_HEAD_

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct tagQItem 
{ 
  int nKey; 
  tagQItem* pNext;
 
}QItem;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct tagQueueList 
{ 
  QItem* pFront;
  QItem* pTail;

}QueueList;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - -

QueueList* QCreate( ); 
int QEmpty( QueueList* );
void QEnque( QueueList* , int );
int QDecque( QueueList*  );
void QClear( QueueList*  );
void QDel( QueueList**  );


#endif