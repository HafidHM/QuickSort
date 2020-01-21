#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NMAX 50000		/* peut etre modifie si necessaire */

#define germe 5
int cmpt = 0;  /* Compteur des comparaisons effectuees soit avec la fonction tri_insertion  ou la fonction tri_segmentation */

/*
generation_aleatoire
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647] selon une loi uniforme.
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/

void generation_aleatoire(int t[], int n) {
  int i ;

  for (i=0 ; i<n ; i++) {
	  t[i] = rand() ;
  } ;
}

/*
generation_aleatoire_non_uniforme
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647].
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/
void generation_aleatoire_non_uniforme(int t[], int n) {
  int i;
  int x = 0;

  for (i=0; i < n; i++) {
    t[i] = x;
    x = x + ((rand() % 10) - 2);
  }
}


/*
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_insertion(int t[], int n) {
  int i,j,drp = 0;
  int Clef;
  
  cmpt = 0;
  for(i=1; i < n; i++) {
    
    Clef = t[i];
    
    j = i - 1;
    
    /* Decalage des valeurs du tableau */
    while((j >= 0) && (t[j] > Clef)) {
      cmpt++;
      t[j+1] = t[j];
      j = j - 1;
      drp = 1;
    }
    if(!drp){
      cmpt++;
    }
    drp = 0;
    /* insertion de la clef */
    t[j+1] = Clef;
  }

  printf("Le nombre des comparaisons effectuées entre les éléments du tableau T: %d\n", cmpt);
}



void echange(int t[],int x ,int y){
  int tmp;
  tmp=t[x];
  t[x]=t[y];
  t[y]=tmp;
}

int partition(int t[],int debut,int fin,int Pivot){
  int i;

  i=debut;
  while(i<fin){
    if(t[i+1]<=t[debut]){
      i++;
    }else{
      echange(t,i+1,fin);
      fin--;
  
    }
    cmpt++;
  }
  echange(t,debut,i);
  return i;
}


void trier_Partie(int t[],int debut,int fin){
  int i,Pivot;
  if(debut<fin){

    Pivot=t[debut];
    i=partition(t,debut,fin,Pivot);
    trier_Partie(t,debut,i-1);
    trier_Partie(t,i+1,fin);
  }
}

/*
tri_segmentation
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est  trie en ordre croissant
*/
void tri_segmentation(int t[], int n) {
  /* A completer */
  trier_Partie(t,0,n-1);
  printf("\nLe nombre des comparaisons effectuées entre les éléments du tableau T: %d", cmpt);
}





void lancer_mesures() {


  int T[NMAX];
  int N,X,i, choix;
  double cmpt_1;
  clock_t debut, fin; 
  double duree;
  


 /* printf("Valeur du germe pour la fonction de tirage aleatoire ? ") ;
  scanf("%d", &germe) ;
*/
  srand(germe) ;

  do {
  	printf("Valeur de N ? ") ;
  	scanf("%d", &N) ;

  } while (N<1 || N > NMAX) ;

  do {
    printf("Valeur de X ? ") ;
    scanf("%d", &X) ;
  } while (X<1 || X > NMAX) ;

  do {
    printf("Choisisez un tri?\nTri par insertion -> 1\tTri par segmentation -> 2\n") ;
    scanf("%d", &choix) ;
  } while (choix<=0 || choix > 2) ;


  switch(choix){
    case 1:
            debut = clock();

            for ( i = 0; i < X; ++i){
               generation_aleatoire(T, N) ; /* initialisation du tableau T */
               tri_insertion(T, N) ;  /* tri de T */
               cmpt_1 +=cmpt;
               cmpt=0;
            }

            fin = clock(); 
            duree = (double)(fin - debut) / CLOCKS_PER_SEC; 
            break;

    case 2:
            debut = clock();

            for ( i = 0; i < X; ++i){
               generation_aleatoire(T, N) ; /* initialisation du tableau T */
               tri_segmentation(T, N) ;  /* tri de T */
               cmpt_1 +=cmpt;
               cmpt=0;
            }

            fin = clock(); 
            duree = (double)(fin - debut) / CLOCKS_PER_SEC;    
      break;
    default: printf("Ce choix n'existe pas\n");
  }
  

  printf("\nLa moyenne: %f\n",cmpt_1/X);   
  printf( "\nTemps d'execution: %f seconds\n", duree);
  
  /* Exercice 5 
     switch(choix){
    case 1:
            debut = clock();

            for ( i = 0; i < X; ++i){
                generation_aleatoire_non_uniforme(T,N);
               tri_insertion(T, N) ; 
               cmpt_1 +=cmpt;
               cmpt=0;
            }

            fin = clock(); 
            duree = (double)(fin - debut) / CLOCKS_PER_SEC; 
            break;

    case 2:
            debut = clock();

            for ( i = 0; i < X; ++i){
                generation_aleatoire_non_uniforme(T,N);
               tri_segmentation(T, N) ;  
               cmpt_1 +=cmpt;
               cmpt=0;
            }

            fin = clock(); 
            duree = (double)(fin - debut) / CLOCKS_PER_SEC;    
      break;
    default: printf("Ce choix n'existe pas\n");
  }

  */



}
