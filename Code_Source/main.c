#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>
#include"head.h"
int main()
{

	system("color 20");
    int op=0;
    initialiserVariables();
    srand(time(NULL));
    genererJeuDeCartes();
   	distribuerZone1();
   	int c=0;
    while(op!=7){
        if(verifieVictoire()){
          quitter();
          return 0;
        }
        if(game_over()){
          system("cls");
          printf("vous avez perdu");
          quitter();
          return 0;
        }
        afficher();
        printf(" mouvements : %d\n", c);
        printf(" 1- de Zone1 vers Zone3\n");
        printf(" 2- de Zone1 vers Zone2\n");
        printf(" 3- de Zone1 vers Zone1\n");
        printf(" 4- de Zone2 vers Zone3\n");
        printf(" 5- de Zone2 vers Zone1\n");
        printf(" 6-aide\n");
        printf(" 7-quitter\n");
        printf(" choisir un mouvement : ");
        scanf("%d", &op);
        getchar();
       
        switch(op){
            case 1:
              de_Zone1_vers_Zone3();
              c++;
              break;
            case 2:
              de_Zone1_vers_Zone2();
              c++;
              break;
            case 3:
			  de_Zone1_vers_Zone1(); 
			  c++;
              break;
            case 4:
              de_Zone2_vers_Zone3();
              c++;
              break;
            case 5:
              de_Zone2_vers_Zone1();
              c++;
              break;
              case 6:
              	help();
              	break;
            case 7:
              system("cls");
              quitter();
              break;
            default:
              printf("\nmouvement invalide (entrer pour continuer)\n");
              getchar();
              break;
        }
    }
	return 0;
}

