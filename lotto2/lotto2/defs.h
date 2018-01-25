#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <malloc.h>
#include <cstdlib>
#include <time.h>
#include "stdafx.h"


#define SIZE 20	
#define PESELSIZE 10
#define IBANCTR 2
#define IBANCTR1 2
#define IBANBANK 10
#define IBANUSER 14
#define SWIFTCODE_SIZE 8
#define SWIFTBANK_SIZE 3

#define SIZE5 5
#define SIZE2 2

#define RESIZE3 3
#define RESIZE5 5

#define RESULT5 50
#define RESULT2 10

#define _DEBUG_PRINT_
//#define _DEBUG_LOTTO_
typedef enum  { female, male } Sex;
typedef enum { sunday, monday, tuesday, wednesday, thrusday, friday, saturday } Day;
typedef enum { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec } Month;

typedef struct
{
	int* Bet2;
	int* Bet5;
}pBets;

typedef struct
{
	char SwiftCode[SWIFTCODE_SIZE];
	char SwiftBank[SWIFTBANK_SIZE];
}Swift;

typedef struct
{
	char IbanCountry[IBANCTR1];
	char IbanControl[IBANCTR];
	char IbanBank[IBANBANK];
	char IbanUser[IBANUSER];
}IBAN;

typedef struct
{
	IBAN IbanStr;
	Swift SwiftStr;
}SI;

typedef struct
{
	int day_name;
	int date_day;
	int date_month;
	int date_year;
}Date;

typedef struct
{
	char Name[SIZE];
	char Surname[SIZE];
	Sex SexType;
	SI BankInfo;
	char Pesel[PESELSIZE];
	Date* DateInfo;
	pBets* pTabDraw;				
	int AllDraws;				
	int CurrDraws;				
}LottoPlayer;