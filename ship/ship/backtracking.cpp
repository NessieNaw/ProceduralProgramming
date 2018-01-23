#include "backtracking.h"

//----------------------------
void setTab( char* sFile, int** pTab, int nRow, int nCol )
{
	FILE* fin = NULL; 
	if ( ( fin = fopen( sFile, "r") ) == NULL )
	{
		perror ( "ERROR: FILE NOT FOUND!!! " );
			return;
	}
	for( int i = 0; i < nRow; i++ )
	{
		int* p = *pTab++;
		for( int j = 0; j < nCol; j++ )
			fscanf( fin, "%d", p++ );
	}
	fclose( fin );
}
//----------------------------
int move( int** pTab, int nRow, int nCol, int nDepth, int move_nr, int x, int y, int* px, int* py, int** pRoot )
{
	switch( move_nr )
	{
	case RIGHT: *px = x; *py = y+1;break;
	case LEFT: *px = x; *py = y-1;break;
	case DOWN: *px = x+1; *py = y;break;
	case UP: *px = x-1; *py = y;break;
	}
	
	if( ( *px < nRow )&&( *py < nCol)&&( *px >= 0 ) &&( *py >= 0 )&&( pTab[*px][*py] >= nDepth + 1 )&&( pRoot[*px][*py] == 0 ) )
		//return 0;
	//else if( pTab[*px][*py] >= nDepth + 1 ) 
	//	return 0;
	//else if( pRoot[*px][*py] != 0 )
	return 1;
	return 0;
}
//----------------------------
int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest  )
{
	pRoot[x][y] = 1;
	
	if( ( x == x_dest )&&( y == y_dest ) ) 
    return 1;
		int i = x;
		int j = y;
	
		//if( move( pTab, nRow, nCol, nDepth,DOWN, x, y , &i, &j,pRoot ) )
		//if( move( pTab, nRow, nCol, nDepth,UP, x, y , &i, &j,pRoot ) )
		//if( move( pTab, nRow, nCol, nDepth,RIGHT, x, y , &i, &j,pRoot ) )
		for( int k = UP; k <= LEFT; k++ )
		if( move( pTab, nRow, nCol, nDepth,k, x, y , &i, &j,pRoot ) )
		if(	root( pTab, nRow, nCol, nDepth, i, j, pRoot, x_dest, y_dest ) )
				/*   // sprwadzic wszystkie mozliwosci ruchu
					//jesli ruch jest mozliwy w zadanym kierunku 
					//jesli wykonanie kolejnego kroku sie powiodlo - rekurencyjnie root()
			root( pTab, nRow, nCol, nDepth, i, j, pRoot, x_dest, y_dest );*/
		return 1;
	
	pRoot[x][y] = 0;
	return 0;
	
	
}
//----------------------------
//----------------------------
//----------------------------
//----------------------------
//----------------------------