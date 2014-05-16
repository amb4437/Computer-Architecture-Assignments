#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "common.h"

void fast() {
    
    /* Replace this with your implementation */
    
    int cache = 8;
    int column, row, rowBounds, columnBounds;
    
	for(row = 0; row < N; row += cache ){
		for(column = 0; column < N; column += cache ){
			rowBounds = row + cache;
			columnBounds = column + cache;
            
			for( int i = row; i < rowBounds; i++ ){
				for( int j = column; j < columnBounds; j++ ){
					out[j][i] = in[i][j];
				}
			}
		}
	}

}
