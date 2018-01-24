#pragma once

int  ReadData( LottoPlayer*** pAllDraws, const char* sfileName );
void FreeMem( LottoPlayer** pTab, int nDrawsNo );