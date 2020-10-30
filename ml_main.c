#include<stdio.h>
#include "ml_lib.h"

int main(){
	
	int **m;
	int r=7, c=7;
	
	
	m=createMatrix(r,c);
	
	setValuesMatrix(m,r,c);
	
	printMatrix(m,r,c);
	
	return 0;
}
