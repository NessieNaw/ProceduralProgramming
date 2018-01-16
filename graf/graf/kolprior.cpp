#include "kolprior.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

void UpdateDown( PQueue*, int l, int p );
void UpdateUp( PQueue*, int l, int p );

//=================================
//=================================
PQueue* PQItnit( int nSize )
{
	PQueue* PQue = ( PQueue* )calloc( 1, sizeof( PQueue ) );
	if( !PQue )
	{
		perror( "PQInit1: memory not allocated" );
		return NULL;
	}

	PQue->pTab = ( PQItem* )calloc( nSize, sizeof( PQItem ) );
		
	if( !PQue->pTab )
	{
		perror( "PQInit2: memory not allocated" );
		return NULL;
	}
	PQue->PQSize = nSize;
	return PQue;

}
//=================================
int PQIsEmpty( PQueue* PQue )
{
	return !( PQue->PQCurrSize );
}
//=================================
void PQEnqueue( PQueue* PQue, int Prior, int Key )
{	//wstawiæ na koñcu i uaktualniæ w górê
	if( PQue->PQCurrSize == PQue->PQSize )
	{
		perror( " PQEnqueue: Array is full " );
		return;
	}
	PQue->pTab[PQue->PQCurrSize].nKey = Key;
	PQue->pTab[PQue->PQCurrSize].nPrior = Prior;
	UpdateUp( PQue, 0, PQue->PQCurrSize++); // dzia³a na tablicy od zera do ostatniego bie¿¹cego elementu //pque->currsize++
}
//=================================
int PQDequeue( PQueue* PQue )
{
	if( !PQIsEmpty( PQue ) )
	{
		perror( " PQDequeue: Array is empty " );
		return 1;
	}
	int p = PQue->pTab[0].nKey;
	PQue->pTab[0] = PQue->pTab[PQue->PQCurrSize];//przelozenie ost na pierwszy //pque->currsize--
//kopiowanie struktur jest niebezpieczne gdy struktura zawiera wskaznik do dynamicznej pamiêci
	UpdateDown( PQue, 0, PQue->PQCurrSize--);

	return p;
}
//=================================
void PQRealese( PQueue* PQue )
{
	while( !PQIsEmpty( PQue ) )
		PQDequeue( PQue );
//PQue->pTab[PQue->PQCurrSize].nKey = NULL;
//PQue->pTab[PQue->PQCurrSize].nPrior = NULL;
	free( PQue->pTab );
	free( PQue );
	/*
	free( PQue->PTab );
	free( PQue );
	PQue->PQSize = 0;
	PQue = NULL;*/
}
//=================================
void DecreaseKey( PQueue* PQue, int Key, int Prior )
{
	if( !( Prior >= PQue->pTab[Key].nPrior ) )
	{
		perror(" DecreaseKey: prior cannot be decreased " );
		return;
	}
	PQue->pTab[Key].nPrior = Prior;
	UpdateDown( PQue, Key, PQue->PQCurrSize-1 ); 
}
//=================================
void IncreaseKey( PQueue* PQue, int Key, int Prior )
{
	if( !( Prior < PQue->pTab[Key].nPrior ) )
	{
		perror(" IncreaseKey: prior cannot be increased " );
		return;
	}
	PQue->pTab[Key].nPrior = Prior;
	UpdateUp( PQue, 0, Key ); 
}
//=================================
void UpdateDown( PQueue* PQue, int l, int p )
{
	if( l == p ) return;
	int i = l;//skrajny lewy
	int j = 2*i + 1;//ojciec
	PQItem x = PQue->pTab[i];//!!!!!
	while( j <= p )
	{
		if( j < p )
		{
			if( PQue->pTab[j].nPrior < PQue->pTab[j+1].nPrior )
				j++;
		}
		if( x.nPrior >=  PQue->pTab[j].nPrior )break;
		 PQue->pTab[i] =  PQue->pTab[j];
		i = j;
		j = 2*i +1;
	}
	 PQue->pTab[i] = x;//!!!!!
}
//=================================
void UpdateUp( PQueue* PQue, int l, int p )
{
	int i = p;
	int j = ( i - 1 )/2;
	PQItem temp = PQue->pTab[i];
	while( i > l && PQue->pTab[j].nPrior < temp.nPrior ) 
	{
		PQue->pTab[i] = PQue->pTab[j];
		i = j;
		j = ( i - 1 )/2;
	}
	PQue->pTab[i] = temp;
}
//=================================
void PQPrint( PQueue* PQue , int i ) // drukowanie w porzadku inorder
{ 
	if( PQue->pTab[i].nPrior > 0 ) 
	{
		PQPrint( PQue, 2*i + 1 ); //lewy
		printf( "prior %d . klucz %d \n\n", PQue->pTab[ ( i - 1 )/2 ].nPrior, PQue->pTab[ ( i - 1 )/2 ].nKey ); //odwiedzenie œrodka
		PQPrint( PQue, 2*i + 2 ); //prawy
	}
}
//for( i = 0; i < PQue->PQCurrSize; i++ ) 
//=================================
//=================================
//=================================