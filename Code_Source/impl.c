#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>
#include"head.h"

tCarte *zone1[8]; //les variables sont déclarés globalement pour eviter la répétition dans les paramètres des fonctions
tCarte *zone3[4];
tCarte *zone2[4];
tCarte *head;
int total=0;
int numZone3[4];
int totalZone1[8];

void initialiserVariables() { // initialise les variables

  head = NULL;
  int i;

  for (i = 0; i < 8; i++) {
    zone1[i] = NULL;
    totalZone1[i] = 0;
    if (i < 4) {
      zone3[i] = NULL;
      zone2[i] = NULL;
      numZone3[i] = 0;
    }
  }
}

void Creer_Carte(int pos, int numero, char forme) { // crée une pile de carte et les ajouter
  tCarte *ptr = head;
  tCarte *New = (tCarte*)malloc(sizeof(tCarte));
  New->numero = numero;
  New->forme = forme;
  
  if (pos == 0) {
    New->next = head;
    head = New;
  } else {
    int i;
    for (i = 0; i < pos - 1; i++) {
      ptr = ptr->next;
    }
    New->next = ptr->next;
    ptr->next = New;
  }
}

void genererJeuDeCartes(){ // génère des cartes aléatoirement puis les insérer
  int position;
  int i, j;  
  for (i = 3; i <= 6; i++) {
    for (j = 1; j <= 13; j++) {
      position = rand() % (total + 1);    
      Creer_Carte(position, j, i);
      total++;
    }
  }
}
void distribuerZone1(){ 
  tCarte *ptr1,*ptr2,*ptrZone1;
	int base,i;
  for( base=0;base<7;base++){ // distribue 6 cartes dans chaque pile de la zone 1
    for( i=0;i<8;i++){ // distribue les 4 dernières cartes dans les piles de la zone 1
      if(base==6 && i>3)//vérifie où placer les 4 dernières cartes
        break;
      ptr1 = head;
      ptr2 = head;
      ptrZone1 = zone1[i];
      while(ptr1->next!=NULL){ // trouve le dernier élément
        ptr1 = ptr1->next;
      }
      if(ptr2->next!=NULL){ // ne perd pas le dernier élément
        while(ptr2->next!=ptr1){ // trouve l'avant-dernier élément, s'il existe
          ptr2 = ptr2->next;
        }
      }
      ptr2->next = NULL;
      if(zone1[i]==NULL){ // insère dans le cas 1 : première position de la pile
        zone1[i] = ptr1;
        ptr1->next = NULL;
      }else{ // insère dans le cas 2 : autres positions de la pile
        while(ptrZone1->next!=NULL){
          ptrZone1 = ptrZone1->next;
        }
        ptrZone1->next = ptr1; // met à jour les pointeurs de base
        ptr1->next = NULL;
      }
      totalZone1[i]++;
    }
  }
}//end 

void afficher(){ 
  char lettre = 'a';

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // commandes du cmd pour définir hConsole
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

  WORD saved_attributes;
  /* Sauvegarder l'état actuel */
  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes; // sauvegarde la configuration de base du cmd ("color 20")

  system("cls");
  int i;
  
tCarte *ptrZone1;
  printf("-----------------------Zone1-----------------------------\n");

for (i = 0; i < 8; i++) { // afficher la zone1
    ptrZone1 = zone1[i];
    if (ptrZone1 == NULL) {
        printf("ligne %d: [    ]", i + 1);
    } else {
        printf("ligne %d: ", i + 1);
        while (ptrZone1 != NULL) {

            if (ptrZone1->forme == 3 || ptrZone1->forme == 4)
                SetConsoleTextAttribute(hConsole, 0x74);
            else
                SetConsoleTextAttribute(hConsole, 0x70);

            if (ptrZone1->numero == 1)
                lettre = 'A';
            if (ptrZone1->numero == 11)
                lettre = 'J';
            if (ptrZone1->numero == 12)
                lettre = 'Q';
            if (ptrZone1->numero == 13)
                lettre = 'K';

            if (lettre == 'a')
                printf("[%02d/%c]", ptrZone1->numero, ptrZone1->forme);
            else
                printf("[%c /%c]", lettre, ptrZone1->forme);
            lettre = 'a';
            SetConsoleTextAttribute(hConsole, saved_attributes);
            printf(" ");
            ptrZone1 = ptrZone1->next;
        }
    }
    printf("\n");
}
printf("\n");
printf("-----------------------Zone2-----------------------------\n");
  for (i = 0; i < 4; i++){ // afficher la zone des cellules libre 
    printf(" %d: ", i + 1);
    if (zone2[i] == NULL){
      printf("[    ] ", i + 1);
    }else{
      if (zone2[i]->forme == 3 || zone2[i]->forme == 4)
        SetConsoleTextAttribute(hConsole, 0x74); // carte rouge
      else
        SetConsoleTextAttribute(hConsole, 0x70); // carte noire

      if (zone2[i]->numero == 1) // lettres à la place des chiffres sur certaines cartes
        lettre = 'A';
      if (zone2[i]->numero == 11)
        lettre = 'J';
      if (zone2[i]->numero == 12)
        lettre = 'Q';
      if (zone2[i]->numero == 13)
        lettre = 'K';

      if (lettre == 'a')
        printf("[%02d/%c]", zone2[i]->numero, zone2[i]->forme); // afficher les cartes
      else
        printf("[%c /%c]", lettre, zone2[i]->forme);

      lettre = 'a';

      SetConsoleTextAttribute(hConsole, saved_attributes); // revient à la configuration de base ("color 20")
      printf(" ");
    }
  }
  printf("\n");
  
  tCarte *ptrZone3;
    printf("-----------------------Zone3-----------------------------\n");

for (i = 0; i < 4; i++) { // affichage de zone 3
    ptrZone3 = zone3[i];
    if (ptrZone3 == NULL) {
        printf("%d- cellule de : %c: [    ]", i + 1, i + 3);
    } else {
        printf("%d- cellule de : %c: ", i + 1, i + 3);
        while (ptrZone3 != NULL) {
            if (ptrZone3->forme == 3 || ptrZone3->forme == 4)
                SetConsoleTextAttribute(hConsole, 0x74);
            else
                SetConsoleTextAttribute(hConsole, 0x70);

            if (ptrZone3->numero == 1)
                lettre = 'A';
            if (ptrZone3->numero == 11)
                lettre = 'J';
            if (ptrZone3->numero == 12)
                lettre = 'Q';
            if (ptrZone3->numero == 13)
                lettre = 'K';

            if (lettre == 'a')
                printf("[%02d/%c]", ptrZone3->numero, ptrZone3->forme);
            else
                printf("[%c/%c]", lettre, ptrZone3->forme);

            lettre = 'a';

            SetConsoleTextAttribute(hConsole, saved_attributes);
            printf(" ");
            ptrZone3 = ptrZone3->next;
        }
    }
    printf("\n");
}
printf("\n");
}
void de_Zone1_vers_Zone3(){ 

  int sourceZone1, destinationZone3;
  printf("Enter la ligne source (Zone1 entre 1 et 8) et le nombre de la destination (Zone3 entre 1 et 4) : Exemple: 1 1\n-> ");
  scanf("%d %d", &sourceZone1, &destinationZone3);
  if((sourceZone1>=1 && sourceZone1<=8) && (destinationZone3>=1 && destinationZone3<=4))
{
  
  	tCarte *ptr1Zone1 = zone1[sourceZone1 - 1];
  	tCarte *ptr2Zone1 = NULL;
  	tCarte *ptrZone3 = zone3[destinationZone3 - 1];

  if (ptrZone3 != NULL) {
    while (ptrZone3->next != NULL) { // dernière carte de la pile de zone3
      ptrZone3 = ptrZone3->next;
    }
  }

  while (ptr1Zone1->next != NULL) { // avant-dernière et dernière position de la ligne de la zone 1
    ptr2Zone1 = ptr1Zone1;
    ptr1Zone1 = ptr1Zone1->next;
  }

  if ((ptr1Zone1->numero) == (numZone3[destinationZone3 - 1] + 1)) { // vérifie les numéros 
    if (ptr1Zone1->forme == destinationZone3 + 2) {//vérifier la forme
      if (zone3[destinationZone3 - 1] == NULL) {
        zone3[destinationZone3 - 1] = ptr1Zone1; // première insertion
      } else {
        ptrZone3->next = ptr1Zone1; // toute autre insertion
      }

      if (ptr2Zone1 == NULL) { // si la zone 1 est vide ou pas
        ptrZone3 = zone1[sourceZone1 - 1];
        zone1[sourceZone1 - 1] = NULL;
      } else {
        ptrZone3 = ptr1Zone1;
        ptr2Zone1->next = NULL;
      }
      numZone3[destinationZone3 - 1] += 1;

    }
    else {
      printf("\nLa forme de la carte doit etre la meme que celle de la pile de la zone3 !\nAPPUYER SUR ENTREE POUR CONTINUER.");
      getchar();
      getchar();
    }
  }
  else {
    printf("\nLe numero de la carte de la table doit etre un de plus que la derniere carte de la pile de la zone3,  a partir de 1 !\nAPPUYER SUR ENTRE POUR CONTINUER.");
    getchar();
    getchar();
  }
}else
	{
		printf("\n Choix invalide entrer un nombre convenable !\nAPPUYER SUR ENTREE POUR CONTINUER.");
    	getchar();
    	getchar();
	}


}
void de_Zone1_vers_Zone2(){ 
  int sourceZone1, destinationZone2;
  printf("Entrer la ligne source (zone1 entre 1 et 8) et la destination (zone2 entre 1 et 4) : Exemple: 1 1\n-> ");
  scanf("%d %d", &sourceZone1, &destinationZone2);
  if((sourceZone1>=1 && sourceZone1<=8) && (destinationZone2>=1 && destinationZone2<=4))
{
  
  if (zone2[destinationZone2 - 1] == NULL) { // si zone2 est vide
    if (zone1[sourceZone1 - 1] != NULL) { // vérifier si zone1 n'est pas vide
      tCarte *ptr1Zone1 = zone1[sourceZone1 - 1];
      tCarte *ptr2Zone1 = NULL;

      while (ptr1Zone1->next != NULL) { // parcourt la position de zone1
        ptr2Zone1 = ptr1Zone1;
        ptr1Zone1 = ptr1Zone1->next;
      }

      if (ptr2Zone1 == NULL) { // vérifie si zone1 va devenir vide
        zone2[destinationZone2 - 1] = zone1[sourceZone1 - 1];
        zone1[sourceZone1 - 1] = NULL;
      } else {
        zone2[destinationZone2 - 1] = ptr1Zone1;
        ptr2Zone1->next = NULL;
      }
    } else {
      printf("\nligne  %d est vide. ENTRER POUR CONTINUER.", sourceZone1);
      getchar();
      getchar();
    }
  } else {
    printf("\nZone2 %d est deja plein. ENTRER POUR CONTINUER.", destinationZone2);
    getchar();
    getchar();
  }
}else
	{
		printf("\n Choix invalide !\nAPPUYER SUR ENTREE POUR CONTINUER.");
    	getchar();
    	getchar();
	}
}//end de_Zone1_vers_Zone2
void de_Zone2_vers_Zone1(){ 
  int sourceZone2, destinationZone1;
  bool corZone2, corZone1; // 1=rouge, 0=noir
  printf("Entrer la source de (zone2 entre 1 et 4) et la destination (zone1 entre 1 et 8) : Exemple: 1 1\n-> ");
  scanf("%d %d", &sourceZone2, &destinationZone1);
  if((sourceZone2>=1 && sourceZone2<=4) && (destinationZone1>=1 && destinationZone1<=8))
{
   
  tCarte *ptrZone1 = zone1[destinationZone1 - 1];
  tCarte *ptrZone2 = zone2[sourceZone2 - 1];




  if (zone2[sourceZone2 - 1] != NULL) { // verifier si zone2 est non vide
    if (zone1[destinationZone1 - 1] == NULL) { // si la zone1 vide
      zone1[destinationZone1 - 1] = zone2[sourceZone2 - 1];
      zone2[sourceZone2 - 1] = NULL;
    } else {
      while (ptrZone1->next != NULL) { // parcourir la table
        ptrZone1 = ptrZone1->next;
      }
      if (ptrZone1 == NULL) { // vérifier si la table est vide
        ptrZone1 = zone2[sourceZone2 - 1];
        zone2[sourceZone2 - 1] = NULL;
      } else {
        if ((ptrZone1->forme == 3) || (ptrZone1->forme == 4)) //  vérifier la couleur
          corZone1 = true;
        else
          corZone1 = false;

        if ((zone2[sourceZone2 - 1]->forme == 3) || (zone2[sourceZone2 - 1]->forme == 4))
          corZone2 = true;
        else
          corZone2 = false;

        if ((corZone2 != corZone1)) {
          if ((zone2[sourceZone2 - 1]->numero == (ptrZone1->numero) - 1)) { // met à jour les pointeurs si la couleur et le numéro sont acceptés
            ptrZone1->next = zone2[sourceZone2 - 1];
            zone2[sourceZone2 - 1] = NULL;
          } else {
            printf("\nLa carte de la zone2 doit être exactement une de moins que la table !\nAPPUYER SUR ENTREE POUR CONTINUER.");
            getchar();
            getchar();
          }
        }
        else {
          printf("\nLa couleur de la zone2 doit etre differente de la couleur de la table !\nAPPUYER SUR ENTREE POUR CONTINUER.");
          getchar();
          getchar();
        }//end else couleur
      }//end else table pleine
    }
  }//end if zone2 non vide
  else {
    printf("\nZone2 vide ! APPUYEZ SUR ENTREE POUR CONTINUER.");
    getchar();
    getchar();
  }//end else zone2 non vide
}else{
	printf("\n choix invalide !\nAPPUYER SUR ENTREE POUR CONTINUER.");
    getchar();
    getchar();
}
}//end de_Zone2_vers_Zone1
void quitter(){ // parcourt tous les tableaux et matrices et libère tout 
  tCarte *ptr;
  int i;

  for(i = 0; i < 4; i++){ // libération de la zone2
    free(zone2[i]);
  }

  for(i = 0; i < 4; i++){ // libération de la zone3
    ptr = zone3[i];
    while(ptr->next != NULL){
      ptr = zone3[i];
      zone3[i] = zone3[i]->next;
      free(ptr);
    }
    free(zone3[i]);
  }

  for(i = 0; i < 8; i++){ // libération de la zone1
    ptr = zone1[i];
    while(ptr->next != NULL){
      ptr = zone1[i];
      zone3[i] = zone1[i]->next;
      free(ptr);
    }
    free(zone1[i]);
  }

}//end 
void de_Zone2_vers_Zone3(){ 

  int sourceZone2, destinationZone3;
  printf("Entrez la source (zone2 entre 1 et 4) et la destination (zone3 entre 1 et 4) : Exemple : 1 1\n-> ");
  scanf("%d %d", &sourceZone2, &destinationZone3);
  if((sourceZone2>=1 && sourceZone2<=4) && (destinationZone3>=1 && destinationZone3<=4))
{  
  	if (zone2[sourceZone2-1] != NULL) {
    	tCarte *ptrZone2 = zone2[sourceZone2-1];
    	tCarte *ptrZone3 = zone3[destinationZone3-1];
    	if (ptrZone3 != NULL) {
      while (ptrZone3->next != NULL) 
	  { // dernière carte de la zone 3
        ptrZone3 = ptrZone3->next;
      }
    }

    if ((ptrZone2->numero) == (numZone3[destinationZone3-1] + 1)) { // vérifie numéro et naipe
      if (ptrZone2->forme == destinationZone3 + 2) {

        if (zone3[destinationZone3-1] == NULL) {
          zone3[destinationZone3-1] = ptrZone2; // première insertion
        } else {
          ptrZone3->next = ptrZone2; // toute autre insertion
          ptrZone2->next = NULL;
        }

        zone2[sourceZone2-1] = NULL;
        numZone3[destinationZone3-1] += 1;

      } else {
        printf("\nLa couleur de la carte doit etre la meme que celle de la pile de naipe !\nAPPUYER SUR ENTREE POUR CONTINUER.");
        getchar();
        getchar();
      }
    } else {
      printf("\nLe numero de la carte du temps doit etre exactement un de plus que la derniere carte de la pile de la zone3, a partir de 1 !\nAPPUYER SUR ENTRÉE POUR CONTINUER.");
      getchar();
      getchar();
    }
  } else {
    printf("\nLe temps doit etre plein !\nAPPUYER SUR ENTREE POUR CONTINUER.");
    getchar();
    getchar();
  }//end else zone2 vide
}else{
	printf("\n Choix invalide entrer un nombre convanable !\nAPPUYER SUR ENTREE POUR CONTINUER.");
    getchar();
    getchar();
	
}
}//end de_Zone2_vers_Zone3
void de_Zone1_vers_Zone1(){
	int sourceZone1, destinationZone1;
	bool sourceColor, destinationColor;
	printf("entrer le nombre de ligne source (entre 1 et 8)  et le nombre de la ligne destination (entre 1 et 8) : Exemple: 1 1\n->");
	scanf("%d %d", &sourceZone1, &destinationZone1 );
	if((sourceZone1>=1 && sourceZone1<=8) && (destinationZone1>=1 && destinationZone1<=8))
	{
		if(zone1[sourceZone1-1]!=NULL)
		{
			tCarte *ptrSource = zone1[sourceZone1 - 1];
    		tCarte *penSource = NULL;
    		tCarte *ptr;
    		tCarte *ptrDestination = zone1[destinationZone1 - 1];
			tCarte *penDestination = NULL;
    		while (ptrSource->next != NULL) 
			{ 
      		penSource = ptrSource;
      		ptrSource = ptrSource->next;
    		}
    		ptr=ptrSource;
    		 if ((ptrSource->forme == 3) || (ptrSource->forme == 4)) 
        	{ 
				sourceColor = true;
			}
      		else
        	{
				sourceColor = false;
			}
        	if(zone1[destinationZone1-1]!=NULL)
			{
				
				while (ptrDestination->next != NULL) 
				{ 
        			penDestination = ptrDestination;
        			ptrDestination = ptrDestination->next;
      		    }
      		 if ((ptrDestination->forme == 3) || (ptrDestination->forme == 4))
          		 destinationColor = true;
        		else
          		destinationColor = false;
      		}else {
            destinationColor = !sourceColor;
            }
         if (sourceColor != destinationColor)
         {
		     if(zone1[destinationZone1-1]!=NULL)
        	 {
        		if ((ptrSource->numero == (ptrDestination->numero) - 1)) 
        		{
        		 	ptrDestination->next = ptr;
        		 	ptrSource = zone1[sourceZone1 - 1]; //réinitialisation des pointeurs
        		 	penSource = NULL;
        		 	while (ptrSource->next != NULL) 
					{ 
      					penSource = ptrSource;
      					ptrSource = ptrSource->next;
    				}
        		 	if (penSource == NULL) 
					{
                	zone1[sourceZone1 - 1] = NULL;
              		} else 
					{
                		penSource->next = NULL;
              		}
				}
				else
				{
					printf("\nLe numero de la source doit etre exactement un de moins que la destination !\nAPPUYER SUR ENTREE POUR CONTINUER.");
              		getchar();
              		getchar();
				}
				
			 }
			 else
			 {
			     zone1[destinationZone1 - 1] = ptrSource;
       		     ptrSource = zone1[sourceZone1 - 1];
                 penSource = NULL;
                 while (ptrSource->next != NULL) 
				  { 
                     penSource = ptrSource;
                     ptrSource = ptrSource->next;
                   }
			     if (penSource == NULL) {
                 zone1[sourceZone1 - 1] = NULL;
                 } 
				 else 
			      {
                     penSource->next = NULL;
                  }
			    }
		    }
		 else
		 {
		 	printf("\nLa couleur de la source doit etre differente de la couleur de la destination !\nAPPUYER SUR ENTREE POUR CONTINUER.");
          	getchar();
          	getchar();
		  }
		}
	  else
	  {
	  	 printf("\nLa source est vide !\nAPPUYER SUR ENTREE POUR CONTINUER.");
    	 getchar();
         getchar();
	   } 
	}
	else
	{
		printf("\n Choix invalide entrer un nombre convenable  !\nAPPUYER SUR ENTREE POUR CONTINUER.");
    	getchar();
    	getchar();
	}
}
bool verifieVictoire() {
  bool verifie = true;
  tCarte *ptrZone;
  int i;
  for (i = 0; i < 4; i++) { // vérifie les zones
    ptrZone = zone3[i];
    if (ptrZone != NULL) {
      while (ptrZone->next != NULL) {
        ptrZone = ptrZone->next;
      }
      if (ptrZone->numero != 13) { // vérifie si les zones sont complètes
        verifie = false;
      }
    } else {
      verifie = false; // vérifie s'il y a au moins un élément dans les zones
    }
  }

  if (verifie) { // écran de victoire si les zones sont complètes
    system("cls");
    printf("\n                       -============================================-\n");
    printf("                      :==-.    :============================:.   .-==:\n");
    printf("                      :==-      :==========================-      -==:\n");
    printf("                       -==:      -========================-      :==-\n");
    printf("                        .-=-:    .========================:    :-=-.\n");
    printf("                          .:-=-.  -=======================  .-==:.\n");
    printf("                             .:=-::======================-:-=:.\n");
    printf("                                :-========================-:\n");
    printf("                                  .=====================-.\n");
    printf("                                    -==================-\n");
    printf("                                     -================-\n");
    printf("                                      :==============:\n");
    printf("                                        .-========-:\n");
    printf("                                            -==-\n");
    printf("                                            -==-\n");
    printf("                                            -==-\n");
    printf("                                            ====\n");
    printf("                                           .====.\n");
    printf("                                          .======.\n");
    printf("                                       ..:========:..\n");
    printf("                                    .::==============::\n");
    printf("                              :-----+******************------:\n");
    printf("                              +*-----------VICTOIRE-----------*\n");
    printf("                              ++-----------FREECELL---------=*\n");
    printf("                              +-----------------------=*\n");
    printf("                              +*=============================*\n");
    printf("\n\n                                     MERCI D'AVOIR JOUE\n");
    quitter();
    return true;
  } else {
    return false;
  }
}
int is_zone2_full()
{
	int i,count=0;
	for(i=0;i<4;i++)
	{
		if(zone2[i]!=NULL)
		{
			count++;
		}
	}
	if(count==4)
		return 1;
	else
		return 0;
}
int is_zone1_full()
{
	int i,count=0;
	for(i=0;i<8;i++)
	{
		if(zone1[i]!=NULL)
		{
			count++;
		}
	}
	if(count==8)
		return 1;
	else
		return 0;
}


int is_blocked_1() { // si il y'a pas de mouvement entre zone 2 et zone 3 la fonction retourne 1
	int k,i,valide=0;
    if (is_zone2_full()) {
        for ( i = 0; i < 4; i++) {
            tCarte *ptr_zone2 = zone2[i];

            

            // Vérifier avec les numZone3
            for ( k = 0; k < 4; k++) {
                if (ptr_zone2->numero == numZone3[k] + 1 && ptr_zone2->forme == (k + 3)) {
                	valide =1;
                    return 0;  // Un mouvement est possible, donc on retourne 0
                }
            }
        }
        if(valide==0)
        return 1;
    }

    if(!is_zone2_full())
    {
    	return 0;
	}
}
int is_blocked_2() { //vérfie si il y'a un mouvement possible dans la zone 1
    tCarte *ptr1, *ptr2;
    bool sourceColor, destinationColor;
	int j,i;
	if (is_zone1_full()) 
	{	
     for ( i = 0; i < 8; i++) 
	  {
        
            ptr1 = zone1[i];
            while (ptr1->next != NULL) {
                ptr1 = ptr1->next;
            }

            if ((ptr1->forme == 3) || (ptr1->forme == 4)) {
                sourceColor = true;
            } else 
			{
                sourceColor = false;
            }
            for (j = i + 1; j < 8; j++) 
			{
            	ptr2 = zone1[j];
                while (ptr2->next != NULL) 
				{
                    ptr2 = ptr2->next;
                }

                if ((ptr2->forme == 3) || (ptr2->forme == 4)) 
				{
                    destinationColor = true;
                }
				else 
				{
                    destinationColor = false;
                }
                if (sourceColor != destinationColor) 
				{
                    if (ptr1->numero == ptr2->numero - 1) 
					{
                        return 0;  // Mouvement disponible
                    }
                }  
            }
        }
    }
    if (!is_zone1_full())
    {
    	return 0;
	}
    return 1;  // Pas de mouvement disponible
}
int is_blocked_3() { //vérfie si il y'a un mouvement possible dans la zone 1 mais dans l'ordre inverse
    tCarte *ptr1, *ptr2;
    bool sourceColor, destinationColor;
    int i, j;
    if(is_zone1_full())
    {
    	for (i = 7; i >= 0; i--) 
		{  // Commencer à partir de la fin du tableau
            ptr1 = zone1[i];
            while (ptr1->next != NULL) {
                ptr1 = ptr1->next;
            }

            if ((ptr1->forme == 3) || (ptr1->forme == 4)) {
                sourceColor = true;
            } else {
                sourceColor = false;
            }

            for (j = i - 1; j >= 0; j--) 
			{  // Commencer à partir de la fin du tableau
                ptr2 = zone1[j];
                while (ptr2->next != NULL) 
				{
                    ptr2 = ptr2->next;
                }
                if ((ptr2->forme == 3) || (ptr2->forme == 4)) 
				{
                    destinationColor = true;
                } 
				else 
				{
                    destinationColor = false;
                }
                if (sourceColor != destinationColor) 
				{
                	if (ptr1->numero == ptr2->numero - 1) 
					{
                        return 0;  // Mouvement disponible
                    }
                }    
            }
       }
    }
    if(!is_zone1_full())
    {
    	return 0;
	}
    return 1;  // Pas de mouvement disponible
}
int is_blocked_4() // si il y'a pas de mouvement entre zone 1 et zone 3 la fonction retourne 1
{
int k,i,valide=0;
tCarte *ptr;
    if (is_zone1_full()) {
        for ( i = 0; i < 8; i++) {
            tCarte *ptr_zone1 = zone1[i];
            while(ptr_zone1->next!=NULL)
            	ptr_zone1=ptr_zone1->next;
            for ( k = 0; k < 4; k++) {
                if (ptr_zone1->numero == numZone3[k] + 1 && ptr_zone1->forme == (k + 3)) {
                	valide =1;
                    return 0;  // Un mouvement est possible, donc on retourne 0
                }
            }
        }
        if(valide==0)
        	return 1;
    }
	if(!is_zone1_full())
	{
		return 0;
	}
    
}    
int is_blocked_5() // vérifie si il y'a un mouvement entre zone 2 et zone 1
{
	int i,j,valide=0;
	tCarte *ptr1,*ptr2;
	bool sourceColor, destinationColor;
	if(is_zone2_full())
	{
		for(i=0;i<4;i++)
		{
			ptr1=zone2[i];
			if ((ptr1->forme == 3) || (ptr1->forme == 4)) {
                sourceColor = true;
            } else {
                sourceColor = false;
            }
           if(is_zone1_full())
		   {
		   		for(j=0;j<8;j++)
		   		{
		   			ptr2=zone1[j];
		   			 while (ptr2->next != NULL) 
					{
                		ptr2 = ptr2->next;
            		}
					if ((ptr2->forme == 3) || (ptr2->forme == 4)) 
					{
                		destinationColor = true;
            		} else 
					{
                		destinationColor = false;
            		}
					if (sourceColor != destinationColor)
					{
						if (ptr1->numero == ptr2->numero - 1)
						{
							valide=1;
							return 0;
						}
					}	
				}
				if(valide==0)
				{
					return 1;
				}			
			}
		if(!is_zone1_full())
		{
			return 0;
		}	 
	}
		
	}else
		{
			return 0;
		}
}
int game_over()
{
	if(is_blocked_1() && is_blocked_2() && is_blocked_3() && is_blocked_4() && is_blocked_5() && is_zone2_full() )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void aide_1() //verifie si il y a un mouvement disponible dans la zone1
{
	tCarte *ptr1, *ptr2;
    bool sourceColor, destinationColor;
	int j,i,valide=0;

		for ( i = 0; i < 8; i++) 
	  {
         ptr1 = zone1[i];
          if (ptr1 == NULL)
            continue;
         while (ptr1->next != NULL) 
		 {
             ptr1 = ptr1->next;
         }
         if ((ptr1->forme == 3) || (ptr1->forme == 4)) 
		 {
            sourceColor = true;
         } 
		 else 
		 {
             sourceColor = false;
         }
         for (j = i + 1; j < 8; j++) 
		 {
             ptr2 = zone1[j];
             if (ptr2 == NULL)
                continue;
             while (ptr2->next != NULL) 
			 {
                 ptr2 = ptr2->next;
             }
             if ((ptr2->forme == 3) || (ptr2->forme == 4)) 
			 { 
                 destinationColor = true;
             } 
			 else 
			 {
            	 destinationColor = false;
             }
             if (sourceColor != destinationColor) 
			 {
                if (ptr1->numero == ptr2->numero - 1) 
				{
					valide=1;
                    printf("il y a un mouvement entre la ligne %d et la ligne %d \n", i+1,j+1);
                    printf("appuyer sur entrer pour continuer \n");
                    getchar();
                    return;
                }
            }    
          }
        }
       if(valide==0)
       {
       	 printf("malheureusement il n y a pas un mouvement pour le moment du haut en bas \n");
       	 getchar();
       	 return;
	   } 
	
}
void aide_2()
{
	tCarte *ptr1, *ptr2;
    bool sourceColor, destinationColor;
	int i,j,valide=0;
	
	 for (i = 7; i >= 0; i--) 
		{  // Commencer à partir de la fin du tableau
            ptr1 = zone1[i];
             if (ptr1 == NULL)
              continue;
            while (ptr1->next != NULL) {
                ptr1 = ptr1->next;
            }

            if ((ptr1->forme == 3) || (ptr1->forme == 4)) {
                sourceColor = true;
            } else {
                sourceColor = false;
            }

            for (j = i - 1; j >= 0; j--) 
			{  // Commencer à partir de la fin du tableau
                ptr2 = zone1[j];
                 if (ptr2 == NULL)
                 continue;
                while (ptr2->next != NULL) 
				{
                    ptr2 = ptr2->next;
                }
                if ((ptr2->forme == 3) || (ptr2->forme == 4)) 
				{
                    destinationColor = true;
                } 
				else 
				{
                    destinationColor = false;
                }
                if (sourceColor != destinationColor) 
				{
                	if (ptr1->numero == ptr2->numero - 1) 
					{
                       printf("il y a un mouvement entre la ligne %d et la ligne %d \n", i+1,j+1);
                       printf("appuyer sur entrer pour continuer\n");
                       getchar();
                       return;
                    }
                }    
            }
       }
       if(valide==0)
       {
       	 printf("malheureusement il n y a pas un mouvement pour le moment du bas en haut \n ");
       	  printf("appuyer sur entrer pour continuer\n");
       	 getchar();
       	 return;
	   }
   

}
void aide_3()
{
	int k,i,valide=0;
        for ( i = 0; i < 8; i++) {
            tCarte *ptr_zone1 = zone1[i];
             if (ptr_zone1 == NULL)
               continue;
            while(ptr_zone1->next!=NULL)
            	ptr_zone1=ptr_zone1->next;
            for ( k = 0; k < 4; k++) {
                if (ptr_zone1->numero == numZone3[k] + 1 && ptr_zone1->forme == (k + 3)) {
                	valide =1;
                    printf("il y'a un mouvement entre la ligne %d dans la zone1 et la cellule des %c \n",i+1,k+3);
                    printf("appuyer sur entrer pour continuer\n");
                    getchar();
                    return;
                }
            }
        }
        if(valide==0)
        {
        	printf("malheureusement il n y a pas un mouvement pour le moment de la zone1 vers la zone3 \n ");
        	 printf("appuyer sur entrer pour continuer\n");
        	getchar();
        	return;
		}
    }


void help()
{ 
	aide_1();
	aide_2();
	aide_3();
}



