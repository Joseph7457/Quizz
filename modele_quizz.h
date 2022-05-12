
#ifndef  __QUIZZ_MODELE__
#define  __QUIZZ_MODELE__

#define TAMPON 300
#define NOMBRE_MAX_CHOIX 10

#define DEBUG 1

typedef struct quizz_m
{
  char*  question;
  char*  reponse;
  char** choix;

  int nombre_reponses;


}ModeleQuizz;

ModeleQuizz* creer_ModeleQuizz(char* fichier);
void detruire_ModeleQuizz(ModeleQuizz* mq);
void charger_quizz(ModeleQuizz* mq, char* fichier);
int extraire_nombre_reponses(char* fichier);

#endif
