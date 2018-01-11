#include "stdafx.h"
#include "fifo.h"
#include <stdlib.h>
#include <memory.h>

#define NSIZE 5

int main( int argc, char* argv[] )
{
	Queue* Queue = QCreate( NSIZE );
	printf(" \n\n max %d\n",  Queue->nMaxElem );
	printf(" \n\n cur %d\n",  Queue->nCurrent );
	
	free( Queue );
    return 0;
}

