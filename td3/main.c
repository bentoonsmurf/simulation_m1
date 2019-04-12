#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
int X0 = 0;
int m;
int a;
int c;
int pgcd(int a, int b)
{
  int r;
  while (b != 0)
    {
      r = a%b;
      a = b;
      b = r;
    }
  return a;
}
int suite( int x0,int i){
	
	if(X0==	x0 && i!=0)return printf("le cycle est de %d  la graine est %d\n", i,X0)	;
	if(i== 2*m) return 0;
	//printf("%d \n", (7*x0+3)%10);
	i++;
	return suite((a*x0+c)%m,i);
	
}
void init(int _a,int _c,int _m){
	a=_a;
	c=_c;
	m=_m;
}
int isPrimeA1(int N) {
  if (N<=1) return 0;
  int n=sqrt(N);
  for (int i=2; i<=n; ++i) 
	if (N%i==0) return 0;
  
  return 1;
}

int cond2(){
	
	for (int p=3; p<=m-1;p=p+2){
		if (isPrimeA1(p))
			if (m%p==0)
				if((a-1)%p !=0) return 0;
	}
	return 1;
}

int tester_m(){
	if (pgcd(c,m) != 1) return 0;	
	
	if (cond2()==0) return 0;
	if(m%4 == 0){
		if ( (a-1)%4 != 0 ) return 0;
	}
	
	return 1;
}

int main(){
	init(7,3,10);
	/*
	for (int k =3;k<100; k++){
			init(7,3,k);
		//if (tester_m()==1) printf(" le nombre est %d \n", m);
	}
	*/
	for (int k =3;k<20; k++){
		printf(" -------------------------------mod %d\n",m);
			init(7,3,k);
		for (int g=0; g<=m-1;g++){
			X0=g;
			suite(g,0);
		}
		printf(" ----------------------------------\n");
	}
}
