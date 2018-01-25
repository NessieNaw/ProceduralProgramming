#include "defs.h"  
#include "print.h"    
#include "data.h"    

void CalcStat( int* pNums5, int* pNums2, LottoPlayer** pDraws, int nDrawsNo );
void Sort( LottoPlayer** pDraws, int nDrawsNo );
int strCompare( char* s1, char* s2 );
//-----------------------------------------
int main( int argc, char* argv[] )
{	if ( argc != 3 )
	{
		printf( "program start failure  \n" );
		return 1;
	}
	//!!!!!!!!!!
	LottoPlayer** pPlayersTab = NULL;//( LottoPlayer** )calloc( 5, sizeof( LottoPlayer* ) );

	int CurrPlNum = ReadData( &pPlayersTab, argv[1] );
	//if
	if(  !( CurrPlNum ) )
	{ 
		printf( "\nerror no players found\n" );
		return 2;
	}
	int* pRes5 = ( int* )calloc( RESULT5, sizeof( int ) );
	int* pRes2 = ( int* )calloc( RESULT2, sizeof( int ) );

	if ( !pRes2 || !pRes5 )
	{
		printf( "Memory Allocation Error.\n" );
		return 0;
	}
 
	CalcStat( pRes5, pRes2, pPlayersTab, CurrPlNum );
	Sort(  pPlayersTab, CurrPlNum  );

	
	FILE* Fout; fopen_s( &Fout, argv[2], "w" );
	if(  !Fout  )
	{
		printf( "\nCan not open \"%s\" file to write. Error.\n", argv[2] );
		return 0;
	}
	PrintResults( Fout, pRes5, pRes2, pPlayersTab, CurrPlNum );
	
	fclose( Fout );
	FreeMem( pPlayersTab, CurrPlNum );
	pPlayersTab = NULL;

	
	return 0;
}
//------------------------------------------------
void CalcStat( int* pNums5, int* pNums2,  LottoPlayer** pDraws, int nDrawsNo )
{
	int* p2 = pNums2;
	int* p5 = pNums5;

	if( nDrawsNo < 1 ) return;
	for ( int i = 0; i < nDrawsNo; i++  )
	{
		LottoPlayer* pPlayer = pDraws[i];
			//pBets* v = pTab[i]->Bets;
		for ( int j = 0; j < pPlayer->CurrDraws; j++ )
		{
			pBets pDraw = pPlayer->pTabDraw[j];

			int* pDraw5 = pDraw.Bet5;
							//pBets* p = v;
			for ( int k = 0; k < SIZE5; k++, pDraw5++ )
			{
				if(  *pDraw5 < 0 && *pDraw5 > RESULT5 )
					printf( "\nPerror: number is out of range \n\n" );
				p5[*pDraw5-1]++;
					
			}

			int* pDraw2 = pDraw.Bet2;
			for ( int k = 0; k < SIZE2; k++, pDraw2++ )
			{
				if ( *pDraw2 < 0 && *pDraw2 > RESULT2 )
					printf( "\nPerror: number is out of range \n\n" );
				p2[*pDraw2-1]++;
					
			}

		}
	}
}
//------------------------------------------------
void Sort( LottoPlayer** pDraws, int nDrawsNo )
{
	for(  int i = 0; i<nDrawsNo-1; i++ )
	{
		int indeks = i;
		LottoPlayer* min = pDraws[i];

		int res;

		for(  int j = i+1; j<nDrawsNo; j++ )
		{
			if(  ( res = strCompare( min->Surname, pDraws[j]->Surname )  ) > 0  ) 
			{
				min = pDraws[j];
				indeks = j;
			}
			else if(  !res  )	
			{
				if(  strCompare( min->Name, pDraws[j]->Name ) > 0 )
				{
					min = pDraws[j];
					indeks = j;
				}
			}
		}
		pDraws[indeks] = pDraws[i];
		pDraws[i] = min;
	}
}
//------------------------------------------------
int strCompare(  char* s1, char* s2 )
{
	char* copyS1 = ( char* )calloc( strlen( s1 )+1, sizeof( char ) );
	char* copyS2 = ( char* )calloc( strlen( s2 ) + 1, sizeof( char ) );
	memcpy( copyS1, s1, strlen( s1 )+1 );
	memcpy( copyS2, s2, strlen( s2 )+1 );

	//_strlwr_s( copyS1 ); //dla ma³ych liter
	//_strlwr( copyS2 );

	int res = strcmp( copyS1, copyS2 ); 

	free( copyS1 );
	free( copyS2 );

	return res;
}