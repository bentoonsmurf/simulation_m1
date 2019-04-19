#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int nombre_arrivee(double p0,double p2){
	double p1 =1 -p0-p2;
	double r=(double)random()/RAND_MAX;
	
	if(r<p0){
		return 0;
	}else
	{
		if(r<p0+p1)
			return 1;
		else
			return 2;		
		
	}
}

int bernouilli(double p){
	int i;
	int r;
	i=0;
	int value;

		r=random()%100;
		if (r<100*p) 
			value=0;
		else 
			value =1;
		printf("%d --> %d\n",r,value);
		i++;

	printf("count_1 --> %d\n",count_1);
	//double r=(double)random()/RAND_MAX;
	return value;
}

void aleatoire_proba(double p){
	int i;
	int r;
	i=0;
	int value;
	int count_1=0;
	while(i<100){
		
		r=random()%100;
		if (r<100*p) 
			value=0;
		else 
			value =1;
		printf("%d --> %d\n",r,value);
		i++;
		count_1=count_1+value;
	}
	printf("count_1 --> %d\n",count_1);
	
}

int main(){
	srandom(getpid()+ time(NULL));

	aleatoire_proba(0.7);
	
	return 0;
}


