#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#define epsilon 1e-3
#define lambda 9
#define mu 10
#define maxevent 100000
#define maxtemps 5000



/*
on a besoin du temps de la simulation
a savoir une variable d'arret
 
*/

long int temps=0;
long int n=0;
long int cumul=0;
long int arret=1e6;
long int compteur_file_vide=0;
long double moyenne_precedente;
long int compteur_stabilite=0;
long int compteur=0;

typedef struct event{
	int type;// 0 arr ive 1 sortie
	double date;
	int etat; // 0 = non traité  1 et deja traité
	
}event;


typedef struct echeancier{
	event tab[maxevent];
	int taille;
	
}echeancier;

echeancier ech;

double exponentiel(int lbda){
	double r=(double)random()/RAND_MAX;// entre 0 et 1 
	
	while (r == 0 || r== 1){
		r=(double)random()/RAND_MAX;
		
	}
	return log(r) / lbda*1.0;// - ln(u)/lambda avec u= unif(0,1)
}

void ajouter_ech(event e){
	if(ech.taille<maxevent){
		ech.tab[ech.taille]=e;
	ech.taille++;
	printf("taille = %d \n",ech.taille);
	}

	else {printf(" echeancier plein"); exit(0);}
}

void init_ech(){
	event e;
	e.type = 0;
	e.date = 0;
	e.etat=0;
	ech.taille=0;
	ajouter_ech(e);
}






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
void arrive_event(event e){
	
	n++;
	event  e1;
	e1.type=0;
	e1.date=e.date+exponentiel(lambda);
	e1.etat=0;
	ajouter_ech(e1);
	// extraire l'evenement qui a la plus petitre date
	if(n==1){// servir client 
		event e2;
		e2.type=1;
		e2.date=e.date+exponentiel(mu);
		e2.etat=0;
		ajouter_ech(e2);
	}
	temps= e.date;
}
void service_event(event e){
	if(n>0){
	n--;
	if(n>0){
		event  e1;
		e1.type=1;
		e1.date=e.date+exponentiel(mu);
		e1.etat=0;// changé dans simulation
		ajouter_ech(e1);
	
	}
}temps= e.date;
}

void afficher(){
	event e;
	printf("---> temps %f et  = %ld taille  %d | ",temps,n,ech.taille);
	for(int i=0; i<ech.taille;i++){
		e=ech.tab[i];
		if (e.type == 0)
			printf("ac %lf , %d ",e.date,e.etat);
		if (e.type == 1)
		printf("(fs %lf , %d )",e.date,e.etat);
	}
	printf("\n \n");
}

void extraire(){
	int i,imin;
	event min;
	for(i=;i<ech.taille;i++){
		if(ech.tab[i].etat==0){
			min= ech.tab[i];
			imin=i
			break;
		}
	}
	for(i=0;i<ech.taille;i++){
		if (min.date > ech.tab[i] && ech.tab[i].etat== 0){
			min=ech.tab[i];
			imin = 1;
		}
	}
	ech.tab[imin].etat=1;
	return min;
	
}







int condition_arret(long double old , long double new){
	if (fabs(old-new)<epsilon && temps>100){
		compteur++;
		if (compteur> 1000)
		return 1;
	}
	
	return 0;
}
/*
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

*/
int main(){
	srandom(getpid()+ time(NULL));
	FILE *f1 =fopen("simulation_CST.data","w");
	//simulateur(f1);
	fclose(f1);
	return 0;
}

