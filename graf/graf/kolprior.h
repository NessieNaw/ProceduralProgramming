#pragma once


typedef struct tagPQItem 
{ 
  int nKey; 
  int nPrior;
   
}PQItem;
//-------------------------------
typedef struct tagPQueue 
{ 
	PQItem* pTab;
	int PQSize;
	int PQCurrSize;
	
}PQueue;
//-------------------------------
PQueue* PQItnit( int );
int PQIsEmpty( PQueue* );
void PQEnqueue( PQueue* , int, int );
int PQDequeue( PQueue* );
void PQRealese( PQueue* );
void PQPrint( PQueue*, int );
void DecreaseKey( PQueue*, int, int );
void IncreaseKey( PQueue*, int, int );
