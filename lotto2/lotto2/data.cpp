#include "defs.h"
#include "Data.h"


int  AllocAddMem( LottoPlayer*** pTab, int nCurrSize );
int	 AllocAddMemDraw( pBets** pTab, int nCurrSize );
int  SetSex( LottoPlayer* p, char c );
int  SetDate( LottoPlayer* p, int d, int m, int y );

//===========================================================================
int  ReadData( LottoPlayer*** pAllDraws, const char* sfileName )
{
	FILE* fin = NULL;			 
    fopen_s( &fin, sfileName, "r" );
	//if ( ( fin = fopen_s( sfileName, "r" ) ) == NULL )
	{
		printf( "ERROR: file %s not exists", sfileName );
		return 0;
	}
	int PlayersNo = 0;	
	int MaxPlayers = 0;	
	
	LottoPlayer** pDraws = *pAllDraws;
	
	while ( !feof( fin ) )	
	{
		char c;
		if(  ( c = getc( fin ) ) != '*' )
				ungetc( c, fin );

			if( PlayersNo == MaxPlayers )
			{ 
				MaxPlayers += AllocAddMem( &pDraws, PlayersNo );
				if ( PlayersNo == MaxPlayers ) break;
			}

			LottoPlayer* pPlayer = pDraws[PlayersNo] = ( LottoPlayer* )calloc( 1, sizeof( LottoPlayer ) );
			if ( !pPlayer )
			{
				printf( "\nread data: memory was not allocated \n" );
				break;
			}
			//memset( n, 0, sizeof( LottoPlayer ) );
			char SexType;	
			int d, m, y;	
			fscanf_s( fin, "%s %s %c %8c%3c %2c%2c%10c%14c %d/%d/%d %10c",	
															pPlayer->Surname, 
															pPlayer->Name, 
															&SexType,
															pPlayer->BankInfo.SwiftStr.SwiftCode,
															pPlayer->BankInfo.SwiftStr.SwiftBank,
															pPlayer->BankInfo.IbanStr.IbanCountry,
															pPlayer->BankInfo.IbanStr.IbanControl,
															pPlayer->BankInfo.IbanStr.IbanBank,
															pPlayer->BankInfo.IbanStr.IbanUser,
															&d, &m, &y, 
															pPlayer->Pesel );						
#ifdef _DEBUG_LOTTO_
printf( " ----- \n\n " );
printf( " name %s",pPlayer->Surname );
printf( " fname %s", pPlayer->Name );
printf( " sex %d", SexType );
printf( " iban %s", pPlayer->BankInfo.SwiftStr.SwiftCode );
printf( " iban %s", pPlayer->BankInfo.SwiftStr.SwiftBank );
printf( " iban %s", pPlayer->BankInfo.IbanStr.IbanCountry );
printf( " iban %s", pPlayer->BankInfo.IbanStr.IbanBank );
printf( " swift %s", pPlayer->BankInfo.IbanStr.IbanUser );
printf( " data %d/%d/%d ", d, m, y );
printf( " pesel %d", pPlayer->Pesel );

#endif 			
			if ( !SetSex( pPlayer, SexType ) || !SetDate( pPlayer, d, m, y ) )
			{
				printf( "\nCannot set sex or date.\n" );
				break;
			}

			fscanf_s( fin, "\n" );

#ifdef _DEBUG_PRINT_
			printf( "\n %s %s \n", &pPlayer->Name, &pPlayer->Surname );
#endif // _DEBUG_PRINT_

		int DrawRead = 0;
		pBets* pDrawTab = NULL;

		while(  ( c = getc( fin )  ) != '*' && !feof( fin )  )				
		{
			ungetc( c, fin );
			
			if(  DrawRead == pPlayer->AllDraws )
			{
				pPlayer->AllDraws += AllocAddMemDraw(  &pPlayer->pTabDraw , DrawRead  );
				if ( DrawRead == pPlayer->AllDraws ) break; //!!!!!!!!!!!!!!!
			}

			pDrawTab = pPlayer->pTabDraw;
			
			int* p2 = pDrawTab[DrawRead].Bet2 = ( int* )calloc( SIZE2, sizeof( int ) );
			int* p5 = pDrawTab[DrawRead].Bet5 = ( int* )calloc( SIZE5, sizeof( int ) );

			if(  !p2 || !p5 )
			{
				printf( "\n read data error\n" );
				break;
			}

			for(  int k = 0; k < SIZE5; k++ )
					fscanf_s( fin, "%d",	&p5[k] );
			//for( int i = 0; i < SIZE2 ; i++ )
			fscanf_s( fin, "%d %d", p2, p2+1  );
			
#ifdef _DEBUG_PRINT_
	printf( "\n " );
		for ( int i = 0; i < SIZE5; i++ )
			printf( " %2d ", p5[i] );
		printf( " | " );
		for ( int i = 0; i < SIZE2; i++ )
			printf( "%2d ", p2[i] );
		printf( "\n" );
#endif // _DEBUG_PRINT_

			DrawRead++;
			fscanf_s( fin, "\n" );
		}
		pPlayer->CurrDraws = DrawRead;
		PlayersNo++;
	}

	fclose( fin );
	*pAllDraws = pDraws;

	return PlayersNo;		
}
//-----------------------------------------
int  AllocAddMem( LottoPlayer*** pTab, int nCurrSize )
{	
	LottoPlayer** copy = *pTab;
	*pTab = ( LottoPlayer** )realloc( *pTab, nCurrSize*sizeof( *( *pTab ) ) + RESIZE5 * sizeof(  *( *pTab )  ) );

	if(  !*pTab  )
	{
		printf( "\nAllocAddMem: Memory not reallocated. \n" );
		*pTab = copy;
		return 0;
	}

	memset(  *pTab + nCurrSize, 0, RESIZE5*sizeof(  *( *pTab )  ) );
	return RESIZE5;
}
//-----------------------------------------
int AllocAddMemDraw ( pBets** pTab, int nCurrSize )
{
	pBets* copy = *pTab;
	*pTab = ( pBets* )realloc( *pTab, nCurrSize * sizeof( *( *pTab ) ) + RESIZE3 * sizeof(  *( *pTab )  ) );
	
	if(  !*pTab  )
	{
		printf( "\nAllocAddMemBets: Memory not reallocated. \n" );
		*pTab = copy;
		return 0;
	}
	
	memset(  *pTab + nCurrSize , 0, RESIZE3 * sizeof(  *( *pTab )  ) );

	return RESIZE3;
}
//-----------------------------------------
void FreeMem( LottoPlayer** pTab, int nDrawsNo )
{
	for ( int i = 0; i<nDrawsNo; i++ )
	{
		LottoPlayer* p1 = pTab[i];
		pBets* p2 = p1->pTabDraw;
		for ( int j = 0; j < p1->CurrDraws ; j++, p2++ )
		{
			free( p2->Bet2 );
			free( p2->Bet5 );
		}
		free( p1->DateInfo );
		free( p1 );
	}
	//	free( &pTab )2
	free( pTab );
}
//-----------------------------------------
int SetSex( LottoPlayer* p, char c )
{			
	switch ( c )
	{
		case 'f':
		case 'F': p->SexType = female; return 1;
		case 'm':
		case 'M': p->SexType = male; return 1;
		default: return 0;
	}
}
//-----------------------------------------
int  SetDate( LottoPlayer* p, int d, int m, int y )
{	
	if(  !(  d >= 1 && d <= 31 && m >= 1 && m <= 12 && y >= 1900  )  )
	{
		printf( "SetDate: incorrect date\n" );
		return 0;
	}

	struct tm time_r = {0};
	if(  !&time_r  )
	{
		printf( "Memory Allocation Error." );
		return 0;
	}

		time_r.tm_mday = d;
		time_r.tm_mon = m-1;
		time_r.tm_year = y-1900;
	
	if(  mktime( &time_r ) == -1 )
		{
			printf( "Data computing error. " );
			return 0;
		}

	Date* p1 = p->DateInfo = ( Date* )calloc( 1, sizeof( Date ) );
	if( !p1 )
	{
		printf( "DateInfo Allocation Error. " );
		return 0;
	}

	p1->date_day = d;
	p1->date_year = y;

	switch ( m )	
	{
		case 1: p1->date_month = jan; break;
		case 2: p1->date_month = feb; break;
		case 3: p1->date_month = mar; break;
		case 4: p1->date_month = apr; break;
		case 5: p1->date_month = may; break;
		case 6: p1->date_month = jun; break;
		case 7: p1->date_month = jul; break;
		case 8: p1->date_month = aug; break;
		case 9: p1->date_month = sep; break;
		case 10: p1->date_month = oct; break;
		case 11: p1->date_month = nov; break;
		case 12: p1->date_month = dec; break;
	}

	switch ( time_r.tm_wday )									
	{
		case 0: p1->day_name = sunday;  break;
		case 1: p1->day_name = monday;  break;
		case 2: p1->day_name = tuesday;  break;
		case 3: p1->day_name = wednesday; break;
		case 4: p1->day_name = thrusday; break;
		case 5: p1->day_name = friday;   break;
		case 6: p1->day_name = saturday; break;
	}
	
	return 1;
}
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------