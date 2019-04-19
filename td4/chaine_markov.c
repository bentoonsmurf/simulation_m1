#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define lambda 9
	
#define mu 10
#define mu2 10
#define b 1000
#define EPSILON 1e-5
#define MAXEVENT 1000000
#define MAXTEMPS 5000

double temps=0;
int n1=0;
int n2=0;
int nb_rejet=0;
double nb_arrive=0;

// AC FS FS2

typedef struct Event{
  //0 pour l'arrivée 1 pour la sortie
  int type;
  double date;
  int etat;
}event;

typedef struct Echeancier{
  event Tab[MAXEVENT];
  int taille;
}echeancier;

echeancier e;

double Exponentielle(int lbda){
double r = (double) random()/RAND_MAX;

  while(r==0 || r==1){
    r = (double) random()/RAND_MAX;
  }
  return -log(r)/(lbda*1.0);
}

void Ajouter_ech(event evt){
  if(e.taille<MAXEVENT){
    //On peut ajouter un event
    e.Tab[e.taille] = evt ;
    e.taille++;
  }
  else{
    printf("Echéancier plein !\n");
  }
}

void init_Ech(){
  e.taille=0;
  event evt;
  evt.type=0;
  evt.date=0;
  evt.etat=0;
  Ajouter_ech(evt);
}
void file_vide(event e){
	if(n==0){
		temps_vide += e.date-temps;
	}
	
}
 void Arrivee_event(event evt){
   n1++;
   nb_arrive++;
	event e1;
   e1.type=0; //AC
   e1.date = evt.date+Exponentielle((n+1)*lambda);
   e1.etat=0;
   Ajouter_ech(e1);

   if(n==1){
     event e2;
     e2.type=1; //FS
     e2.date = evt.date + Exponentielle(n*mu);
     e2.etat=0;
     Ajouter_ech(e2);
     if(n2==b){
		 nb_rejet++;
		 n1--;
	 }
     if(n2==0){
	 event e3;
     e3.type=2; //FS2
     e3.date = evt.date + Exponentielle(n*mu2);
     e3.etat=0;
     Ajouter_ech(e3);
	 }
   }
   temps=evt.date;
 }

void Service1_event(event evt){
//	file_vide(evt);
  if(n1>0 && n2<b){
    n1--;
    n2++;
    if(n2 == 1){
		event e1;
      e1.type=2;//fs2
      e1.date = evt.date+Exponentielle(n*mu2);
      e1.etat=0;
      Ajouter_ech(e1);
	}
	 if(n1 > 0 && n2 <b){
		event e2;
      e2.type=1;//fs1
      e2.date = evt.date+Exponentielle(n*mu);
      e2.etat=0;
      Ajouter_ech(e2);
	}
	

  
  }

if (n2 == b && n1> 0) {
	n1--;
	nb_rejet++;
}
  temps=evt.date;
}



void Service2_event(event evt){
//	file_vide(evt);
  if(n2>0){
    n2--;
    
    if(n2> 0){
		event e1;
      e1.type=2;//fs2
      e1.date = evt.date+Exponentielle(n*mu2);
      e1.etat=0;
      Ajouter_ech(e1);
	}
	
  }

  temps=evt.date;
}



void affiche_echeancier(){
  event evt;
  printf("==> temps %f et N ) %ld taille : %d !",temps,n,e.taille);
  for(int i=0;i<e.taille;i++){
    evt = e.Tab[i];
    if(evt.type==0){
      printf("(AC %lf , %d),", evt.date,evt.etat);
    }
    if(evt.type==1){
      printf("(FS %lf , %d),", evt.date,evt.etat);
    }
  }
  printf("\n\n");
}

void affiche_proba_temps_vide(){
	
	printf("temps vide = %f",(double)temps_vide/temps);
}
int condition_arret (long double old, long double new){
  if(fabs(old-new)<EPSILON && temps>1000){
    compteur++;
  }
  if(compteur>1e3){
    return 1;
  }
  return 0;
}

event extraire(){
  event min;
  int imin;
  for(int i=0;i<e.taille;i++){
    if(e.Tab[i].etat == 0){
      min =e.Tab[i];
      imin=i;
      break;
    }
  }

  for(int i=0;i<e.taille;i++){
    if(min.date >e.Tab[i].date && e.Tab[i].etat == 0){
      min=e.Tab[i];
      imin=i;
    }
  }
  e.Tab[imin].etat=1;

  return min;
}

void simulation(FILE* f1){
long double oldNmoyen=0;
long double Nmoyen=0;

  init_Ech();

  while(condition_arret(oldNmoyen,Nmoyen)==0){
    event evt = extraire();
    cumul+=(evt.date-temps)*n; //intervalle de temps * le nombre de client dans cette intervalle

    oldNmoyen=Nmoyen;
    Nmoyen=cumul/temps;

    if(temps==0){
      fprintf(f1,"0 0 \n");
    }
    else{
      fprintf(f1,"%f %Lf \n",temps,Nmoyen);
    }

    if(evt.type==0){
      Arrivee_event(evt);
    }
      if(evt.type==1){
      Service1_event(evt);
    }
    if(evt.type==2){
      Service2_event(evt);
    }
  
  }
  printf("\n nombre moyen  = %Lf\n",Nmoyen);
}

int main(){
FILE* f1= fopen("donnee","w");

  srandom(getpid()+ time(NULL));
  simulation(f1);
  //affiche_echeancier();

    fclose(f1);
}
