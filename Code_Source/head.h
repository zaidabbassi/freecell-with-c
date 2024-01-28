#ifndef HEAD_HEADER
#define HEAD_HEADER
#include <stdbool.h>
typedef struct cartes { /*structure utilisé pour représenter une carte et la pile des carte*/
  int numero;			//numero représente le numéro de la carte
  char forme;			//forme pour coeur,diamond,trèfel,pique
  struct cartes *next;
} tCarte;
extern tCarte *zone1[8]; //les variables sont déclarés globalement pour eviter la répétition dans les paramètres des fonctions
extern tCarte *zone3[4];
extern tCarte *zone2[4];
extern tCarte *head;
extern int total;
extern int numZone3[4];
extern int totalZone1[8];

void initialiserVariables(void);
void Creer_Carte(int pos, int numero, char forme);
void genererJeuDeCartes(void);
void distribuerZone1(void);
void afficher(void);
void de_Zone1_vers_Zone3(void);
void de_Zone1_vers_Zone2(void);
void de_Zone2_vers_Zone1(void);
void de_Zone2_vers_Zone3(void);
void de_Zone1_vers_Zone1(void);
bool verifieVictoire(void);
int is_zone2_full(void);
int is_zone1_full(void);
int is_blocked_1(void);
int is_blocked_2(void);
int is_blocked_3(void);
int is_blocked_4(void);
int is_blocked_5(void);
int game_over(void); 
void aide_1(void);
void aide_2(void);
void aide_3(void);
void help(void);
#endif 
