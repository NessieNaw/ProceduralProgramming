#include "list.h"
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include "global.h"

using namespace std;

int IsEmpty( ListItem* pList ) 
{ 
	return !( pList -> m_pNext ); 
}
//==========================================
void Insert( ListItem* pAfter, LISTINFO* x ) 
{
	ListItem* p = ( ListItem* )malloc( sizeof( ListItem ) );
	
	if( !p )
	{  perror("Insert! : Memeory was not set \n");
	   return;
	}
 	memset( p, 0, sizeof( ListItem ) );
 	p->m_pInfo = x; 
	p->m_pNext = pAfter->m_pNext;  
	pAfter->m_pNext = p;
	
}
//==========================================
void InsertFront( ListItem* pAfter, LISTINFO* x )
{
	Insert( pAfter, x );
}
 //==========================================
ListItem* Front( ListItem* pList ) //zwraca wartoœæ szczytu, elementu szczytowego
{
	if( !IsEmpty( pList ) )
		return( pList -> m_pNext ); //zwraca wartosc szczytowa elementu
	return NULL;
}
//==========================================
void FreeList( ListItem* pList )
{
	while( !IsEmpty )
		{		
			RemoveFront( pList );
			pList ->m_pNext = NULL;
		}
}
//==========================================
void DelList( ListItem** pList ) 
{
	FreeList( *pList );
	free( *pList );
	*pList = NULL;
}
//==========================================
ListItem* MakeEmptyList( )
{
	ListItem* List = ( ListItem* )malloc( sizeof( ListItem ) ); 
	if( List )
	{ 
		memset( List, 0, sizeof( ListItem )); 
	}
	else
		perror( "MakeEmptyList: Memory is not set" );
	return List;
}
//==========================================
void Remove( ListItem* pAfter ) //usuwa element po wskazanym konkretnym
{
	if( IsEmpty( pAfter ) )
	{	perror( "Remove: Nie ma nastepnego elementu. \n" );
        return;	
	}
	ListItem* p = pAfter ->  m_pNext;
	pAfter ->  m_pNext = p ->  m_pNext;
	free( p->m_pInfo );
	free( p );	
}
//==========================================
void RemoveFront( ListItem* pList )
{
	Remove( pList );
}
//==========================================
void SortList( ListItem* pList, int ( __cdecl *comp )( const void*, const void* ) )
{	
	if( IsEmpty( pList ) )
	{
		perror( "SortList: Empty List " );
	}
	ListItem* pFirst = pList;					//ustawia na pierwszy el, i do konca po jednym, zostawia po sobie najmniejszy el
	while( pFirst-> m_pNext )					//wyszukuje najmniejszy i wstawia na poczatek, i tak od pierwszego do konca
	{
		ListItem* pMin = pFirst;				//najmniejszy el, ustawia na pFirst, pozniej skacze do konca i sprawdza czy ktorys jest mniejszy, jesli sie znajdzie najmniejszy  to zamienia
		ListItem* pNext = pMin -> m_pNext;		//skacze po kolejnych el od pFirst do konca
		while( pNext -> m_pNext )					//znajduje najmniejszy el
		{
			if( comp( pMin -> m_pNext -> m_pInfo, pNext -> m_pNext -> m_pInfo ) == 1 )
				pMin = pNext;					//ustawia najmniejszy
			pNext = pNext -> m_pNext;				//wskazyje nastepny
		}
		if( pFirst != pMin )					//jesli najmniejszy jest inny niz pierwszy to zamienia pFirst z pMin
		{
			pNext = pMin -> m_pNext -> m_pNext;	 //kolejnemu podstawia nastepny od znalezionego ¿eby nie zapomniec co jest za tym przenoszonym
			pMin -> m_pNext -> m_pNext = pFirst -> m_pNext;	// wskazuje na to na co pFirst
			pFirst -> m_pNext = pMin -> m_pNext;	//pFirst wskazuje na el ement po pMin
			pMin -> m_pNext = pNext;				//pMin wskazuje na pNext
		}
		pFirst = pFirst -> m_pNext;
	}
}
		
//==========================================
void PrintList( ListItem* pList, int Size)
{
	ListItem* p = ( ListItem* )malloc( sizeof( ListItem ) );
	if( p )
	{
		memset( p, 0, sizeof( ListItem* ) );
		p = Front( pList );
		int i = 1;
	while( p != NULL)
	{
		printf( "%d ", p -> m_pInfo -> m_nKey );
		if( i++% Size == 0 )
		{
			printf( "\n\n\n" );
		}
		p = p -> m_pNext;
	}
}
}
//==========================================
ListItem* Find( ListItem* pList, const void* x, ListItem** pPrev, int ( __cdecl *comp )( const void*, const void* ) )	//wyszukuje elementu x
{
	ListItem* p = ( ListItem* )malloc( sizeof ( ListItem ) );
	if( p )
	{
		memset( p, 0, sizeof( ListItem ) );
		p = pList -> m_pNext;
	while( p )
	{
		if( comp( x, p -> m_pInfo ) == 0 ) 
			return *pPrev = p;
		p = p -> m_pNext;
	}
	
	*pPrev = NULL;		
	return 0;
	}
	else
		perror ( "FIND! " );
}
//==========================================
//==========================================
//==========================================
//==========================================
