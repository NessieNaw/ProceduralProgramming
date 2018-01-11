#pragma once
#define _FIFO_FIRST_
#ifdef _FIFO_FIRST_


//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct tagQueue 
{ 
  int pFront;
  int nCurrent;
  int pTail;
  int nMaxElem;
  int* pTab;

}Queue;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - -

Queue* QCreate( int ); 
int QEmpty( Queue* );
void QEnque( Queue* , int );
int QDecque( Queue*  );
void QClear( Queue*  );
void QDel( Queue**  );


#endif