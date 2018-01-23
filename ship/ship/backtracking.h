#pragma once
#include <stdio.h>
#include <stdio.h>
#include <malloc.h>

enum directions{ UP, RIGHT, DOWN, LEFT };

int move( int** pTab, int nRow, int nCol, int nDepth, int move_nr, int x, int y, int* px, int* py, int** pRoot );
int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest  );
//void clearRoot( int** pRoot, int nRow, int nCol );
//void setTab( char* sFile, int** pTab, int nRow, int nCol, int* t );
void setTab( char* sFile, int** pTab, int nRow, int nCol  );
