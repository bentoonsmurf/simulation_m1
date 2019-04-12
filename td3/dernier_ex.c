
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
long double valeur[100];
#define lbda 1.0

double transformation_inverse(){
long double r = (long double) random()/RAND_MAX;

  while(r==0 || r==1){
    r = (long double) random()/RAND_MAX;
  }
  return -logl(r)/(lbda);
}


int main(){

	for (int k =0;k<100; k++){
		valeur[k]= transformation_inverse();
	}
		for (int i=0;i<100;i++){
		printf(" %Lf \n",valeur[i]);
	}
}
