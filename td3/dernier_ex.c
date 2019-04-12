
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
long double* valeur;
long double* fcrempart;
long double* fcrempart2;
#define lbda 1.0
#define TAILLEMAX 1e2
void fusion(long double tableau[],int deb1,int fin1,int fin2)
        {
        long double *table1;
        int deb2=fin1+1;
        int compt1=deb1;
        int compt2=deb2;
        int i;
        
        table1=malloc((fin1-deb1+1)*sizeof(long double));

        //on recopie les éléments du début du tableau
        for(i=deb1;i<=fin1;i++)
            {
            table1[i-deb1]=tableau[i];
            }
                        
        for(i=deb1;i<=fin2;i++)
            {        
            if (compt1==deb2) //c'est que tous les éléments du premier tableau ont été utilisés
                {
                break; //tous les éléments ont donc été classés
                }
            else if (compt2==(fin2+1)) //c'est que tous les éléments du second tableau ont été utilisés
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute les éléments restants du premier tableau
                compt1++;
                }
            else if (table1[compt1-deb1]<tableau[compt2])
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute un élément du premier tableau
                compt1++;
                }
            else
                {
                tableau[i]=tableau[compt2]; //on ajoute un élément du second tableau
                compt2++;
                }
            }
        free(table1);
        }
void tri_fusion_bis(long double tableau[],int deb,int fin)
        {
        if (deb!=fin)
            {
            int milieu=(fin+deb)/2;
            tri_fusion_bis(tableau,deb,milieu);
            tri_fusion_bis(tableau,milieu+1,fin);
            fusion(tableau,deb,milieu,fin);
            }
        }

void tri_fusion(long double tableau[],int longueur)
     {
     if (longueur>0)
            {
            tri_fusion_bis(tableau,0,longueur-1);
            }
     }
        
double transformation_inverse(){
long double r = (long double) random()/RAND_MAX;

  while(r==0 || r==1){
    r = (long double) random()/RAND_MAX;
  }
  return -logl(r)/(lbda);
}

void fct_expermital(){
		for (int k =0;k<TAILLEMAX; k++){
		
		fcrempart[k]=((long double) k+1) / TAILLEMAX;
	}
	
}
void generation_valeur(){
	
	for (int k =0;k<TAILLEMAX; k++){
		valeur[k]= transformation_inverse();
	}
}

void init(){
		
  srandom(getpid()+ time(NULL));
  valeur= calloc(TAILLEMAX,sizeof(long double));
	fcrempart=calloc(TAILLEMAX,sizeof(long double));
	fcrempart2=calloc(TAILLEMAX,sizeof(long double));
}



void fct_theorique(){

init();
generation_valeur();
tri_fusion(valeur,TAILLEMAX);

	
}

void ecrire(){
	FILE* f= fopen("data.data","w");
		for (int k =0;k<TAILLEMAX; k++){
		fprintf(f,"%.15Lf      %.15Lf      %.15Lf \n",valeur[k],fcrempart[k],fcrempart2[k]);
		}
		fclose(f);
}

void moyenne_exp(){
	long double somme=0;
	for(int i=0;i<TAILLEMAX;i++){
		somme+= valeur[i]*(1.0/TAILLEMAX);
	}
	printf("moyenne = %Lf \n",somme);
}

int main(){

fct_theorique();
fct_expermital();
ecrire();
moyenne_exp();

	
}
/*

	for (int k =0;k<100; k++){
		valeur[k]= transformation_inverse();
	}
	tri_fusion(valeur,100);
		for (int i=0;i<100;i++){
		printf(" %Lf \n",valeur[i]);
	}
*/
