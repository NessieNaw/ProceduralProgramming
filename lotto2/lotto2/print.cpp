#include "defs.h"
#include "Data.h"
#include "Print.h"
void PrintSex( FILE* fout, LottoPlayer* p );                        
void PrintDate( FILE* fout, LottoPlayer* p );                      
void PrintBets( FILE* fout, LottoPlayer* p );
//-----------------------------------------
void PrintResults( FILE* fout, int* pNums5, int* pNums2, LottoPlayer** pDraws, int nDrawsNo )
{

	for( int i=0; i<nDrawsNo; i++ )
	{
	LottoPlayer* pPlayer = pDraws[i];
	fprintf( fout, "**%s %s\t", pPlayer->Surname, pPlayer->Name );
	PrintSex( fout, pPlayer );
	PrintDate( fout, pPlayer );

	IBAN* v1 = &( pPlayer->BankInfo.IbanStr );
	Swift* v2 = &( pPlayer->BankInfo.SwiftStr );

	fprintf( fout, "Swift:%.8s%.3s\tIban:%.2s%.4s%.10s%.14s  ", v2->SwiftCode, 
												v2->SwiftBank, 
												v1->IbanCountry,										
												v1->IbanControl,
												v1->IbanBank,
												v1->IbanUser );
	fprintf( fout, "\n----------------  BETS  ----------------\n" );
	PrintBets( fout, pPlayer );
	}

	fprintf( fout, "\n====================================\n      S T A T I S T I C S       \n=====================================\n\n\n" );

	int* p5 = pNums5;
	for( int i = 0; i < RESULT5; i++, p5++ )
	{
		fprintf( fout, "%2d:%2d  ", i+1, *p5 );
		if(  !(  ( i+1 ) % 10  )  ) fprintf( fout, "\n" );
	}

	fprintf( fout, "\n" );

	int* p2 = pNums2;
	for ( int i = 0; i < RESULT2; i++, p2++ )
	{
		fprintf( fout, "%2d:%2d  ", i + 1, *p2 );
	}
	//fclose( fout );
}
//-----------------------------------------
void PrintSex( FILE* fout, LottoPlayer* p )
{
	switch ( p->SexType )
	{
	case female: fprintf( fout, "*female*    " ); break;
	case male: fprintf( fout, "*male*    " );
	}
}
//-----------------------------------------
void PrintDate( FILE* fout, LottoPlayer* p )
{
	switch ( p->DateInfo->day_name )
	{
	case sunday: fprintf( fout, "Sun, " ); break;
	case monday: fprintf( fout, "Mon, " ); break;
	case tuesday: fprintf( fout, "Tue, " ); break;
	case wednesday: fprintf( fout, "Wed, " ); break;
	case thrusday: fprintf( fout, "Thr, " ); break;
	case friday: fprintf( fout, "Fri, " ); break;
	case saturday: fprintf( fout, "Sat, " );
	}

	fprintf( fout, "%d/", p->DateInfo->date_day );

	switch ( p->DateInfo->date_month )
	{
	case jan: fprintf( fout, "Jan/" ); break;
	case feb: fprintf( fout, "Feb/" ); break;
	case mar: fprintf( fout, "Mar/" ); break;
	case apr: fprintf( fout, "Apr/" ); break;
	case may: fprintf( fout, "May/" ); break;
	case jun: fprintf( fout, "Jun/" ); break;
	case jul: fprintf( fout, "Jul/" ); break;
	case aug: fprintf( fout, "Aug/" ); break;
	case sep: fprintf( fout, "Sep/" ); break;
	case oct: fprintf( fout, "Oct/" ); break;
	case nov: fprintf( fout, "Nov/" ); break;
	case dec: fprintf( fout, "Dec/" );
	}

	//!!!!!!!!!!!!!!
	fprintf( fout, "%d\n", p->DateInfo->date_year );
}
//-----------------------------------------
void PrintBets( FILE* fout, LottoPlayer* p )
{
	pBets* pBet = p->pTabDraw;
	for( int i = 0; i < p->CurrDraws; i++, pBet++ )
	{
		int* p5 = pBet->Bet5;
		for( int j = 0; j<SIZE5; j++ )
			fprintf( fout, " %2d ", *p5++ );
		
		fprintf( fout, "  |  " );

		int* p2 = pBet->Bet2;
		for( int j = 0; j<SIZE2; j++ )
			fprintf( fout, " %2d ", *p2 );
		
		fprintf( fout, "\n" );
	}

	fprintf( fout, "\n" );
}
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------