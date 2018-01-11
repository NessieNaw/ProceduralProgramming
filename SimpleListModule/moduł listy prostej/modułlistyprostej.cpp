
#include <iostream>
#include <time.h>
#include "stdafx.h"
#include "list.h"
#include "global.h"
#include <malloc.h>
#include <stdio.h>

using namespace std;

#define MAX 100
#define COL 25
#define VAL 1
#define X 13

int Comp( const void* p, const void* v);
int main( int argc, char* argv[] )
{
	ListItem* pList = MakeEmptyList();
	for( int i = 0; i < MAX; i++ )
	{
		LISTINFO* pInt = (LISTINFO*)malloc( sizeof(LISTINFO) );
		pInt -> m_nKey = VAL + i; 
		InsertFront( pList, pInt );
	}
	PrintList( pList, COL );
	LISTINFO* pInt = ( LISTINFO* )malloc( sizeof( LISTINFO ) ); 
	pInt -> m_nKey = X; 
	ListItem* pPrev = NULL; 
	RemoveFront( Find( pList, pInt, &pPrev, Comp ) ); 
	PrintList( pList, COL );
	printf( "\n\n\n\n" );
	InsertFront( Find( pList, pInt, &pPrev, Comp ), pInt );
	SortList( pList, Comp );
	PrintList( pList, COL );
	DelList( &pList ); 
	
	printf( "\n" );
	return 0;
}

//==================================================================
int Comp( const void* p, const void* v)
{
	if( ( ( LISTINFO* )p ) -> m_nKey > ( ( LISTINFO* )v ) -> m_nKey )
		return 1;
	if( ( ( LISTINFO* )p ) -> m_nKey == ( ( LISTINFO* )v ) -> m_nKey )
		return 0;
	return -1;
}
