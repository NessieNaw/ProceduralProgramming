#pragma once
#ifndef _SIMPLE_LIST_
#define _SIMPLE_LIST_

#include "global.h"

typedef struct tagListItem
{ 
  LISTINFO* m_pInfo; 
  tagListItem* m_pNext;
 
 
}ListItem;



typedef ListItem* ListType;

int IsEmpty( ListItem* pList);
void Insert( ListItem* pAfter, LISTINFO* pInfo ); //void Insert( ListItem* pAfter, int x ); //wstawia do listy po wksazniku
void InsertFront( ListItem* pList, LISTINFO* x ); //void InsertFront( ListItem* pList, int x ); //wstawia do listy na poczatek
void Remove( ListItem* pAfter );
void RemoveFront( ListItem* pList ); //usuwa pierwszy elem wskazywany przez glowe
ListItem* Front( ListItem* pList ); //zwraca wskaznik na pierwszy
void FreeList( ListItem* pList );
void DelList( ListItem** pList );
ListItem* MakeEmptyList( );//tworzy pusta  liste z glowa
void SortList( ListItem* pList, int ( __cdecl *comp )( const void*, const void* ) );
void PrintList( ListItem* pList, int Size);
ListItem* Find( ListItem* pList, const void* x, ListItem** pPrev, int ( __cdecl *comp )( const void*, const void* ) );	//wyszukuje elementu x i zwraca wskaznik na poprzedni




#endif 
