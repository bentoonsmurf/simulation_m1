#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#define epsilon 1e-3
/*
on a besoin du temps de la simulation
a savoir une variable d'arret
 
*/

long int temps=1;
long int n=0;
long int cumul=0;
long int arret=1e6;
long int compteur_file_vide=0;
long double moyenne_precedente;
long int compteur_stabilite=0;
long int compteur=0;

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
void arrive_event(){
	n+= nombre_arrivee(0.4,0.35);
	cumul+=n;
}

void service_client(){
	if(n>0){
		n--;
		arret--;
	}
	
}



long double abso(long double a){
	if(a<0)return -a;
	return a;
	
}


int condition_arret(long double old , long double new){
	if (fabs(old-new)<epsilon && temps>100){
		compteur++;
		if (compteur> 1000)
		return 1;
	}
	
	return 0;
}

void simulateur(FILE* f1){
	long double nmoyen=0;//arret>0
	
	while(condition_arret(moyenne_precedente,nmoyen) ==0 ){
		
		arrive_event();
		
		moyenne_precedente=nmoyen;
		nmoyen=(long double)cumul/temps;
		fprintf(f1,"%5ld    %Lf \n",temps,nmoyen);
		
		service_client();
		compteur_file_vide += n==0;
		
		temps++;
		
		
	}
	double d=(double)compteur_file_vide/temps;
	printf("\n la file est vide %f du temps",d);

}

int main(){
	srandom(getpid()+ time(NULL));
	FILE *f1 =fopen("simulation_CST.data","w");
	simulateur(f1);
	fclose(f1);
	return 0;
}

