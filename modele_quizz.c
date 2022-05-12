/***
 *        ██      ██ ██████  ██████   █████  ██ ██████  ██ ███████ ███████
 *       ██      ██ ██   ██ ██   ██ ██   ██ ██ ██   ██ ██ ██      ██
 *      ██      ██ ██████  ██████  ███████ ██ ██████  ██ █████   ███████
 *     ██      ██ ██   ██ ██   ██ ██   ██ ██ ██   ██ ██ ██           ██
 *    ███████ ██ ██████  ██   ██ ██   ██ ██ ██   ██ ██ ███████ ███████
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <math.h>
#include <string.h>

#include "modele_quizz.h"

/***
 *     ██████ ██████  ███████  █████  ████████ ██  ██████  ███    ██     ██████  ██    ██     ███    ███  ██████  ██████  ███████ ██      ███████
 *    ██      ██   ██ ██      ██   ██    ██    ██ ██    ██ ████   ██     ██   ██ ██    ██     ████  ████ ██    ██ ██   ██ ██      ██      ██
 *    ██      ██████  █████   ███████    ██    ██ ██    ██ ██ ██  ██     ██   ██ ██    ██     ██ ████ ██ ██    ██ ██   ██ █████   ██      █████
 *    ██      ██   ██ ██      ██   ██    ██    ██ ██    ██ ██  ██ ██     ██   ██ ██    ██     ██  ██  ██ ██    ██ ██   ██ ██      ██      ██
 *     ██████ ██   ██ ███████ ██   ██    ██    ██  ██████  ██   ████     ██████   ██████      ██      ██  ██████  ██████  ███████ ███████ ███████
 *
 *
 */

ModeleQuizz* creer_ModeleQuizz(char* fichier)
{
  if(DEBUG)
    printf("Log de création du modèle\n-------------------------------------------\n");

  ModeleQuizz* mq = malloc(sizeof(ModeleQuizz));

  mq->question = malloc(sizeof(char) * TAMPON);
  mq->reponse  = malloc(sizeof(char) * TAMPON);
  mq->choix    = malloc(sizeof(char*) * NOMBRE_MAX_CHOIX);

  assert(mq->question && mq->choix && mq->reponse);

  for (int c = 0; c < NOMBRE_MAX_CHOIX; c++)
    {
      mq->choix[c] = malloc(sizeof(char) * TAMPON);
      strcpy(mq->choix[c], "Espace Alloué\0");
      assert(mq->choix[c]);
    }

  printf("%s\n", mq->choix[0]);

  if (DEBUG)
    printf("L'espace des pointeurs a été alloué\n");

  mq->nombre_reponses = extraire_nombre_reponses("test.txt");
  if (DEBUG)
    printf("Le nombre de choix est de : %d\n", mq->nombre_reponses);

  charger_quizz(mq, fichier);
  if (DEBUG)
  {
    printf("Question: \n   %s\n", mq->question);
    printf("Reponse : \n   %s\n", mq->reponse);
    for (int i = 0; i < mq->nombre_reponses; i++)
      printf("Choix: \n   %s\n", mq->choix[i]);
  }


  return mq;
}

/***
 *    ██████  ███████ ███████ ████████ ██████  ██    ██  ██████ ████████ ██  ██████  ███    ██     ██████  ██    ██     ███    ███  ██████  ██████  ███████ ██      ███████
 *    ██   ██ ██      ██         ██    ██   ██ ██    ██ ██         ██    ██ ██    ██ ████   ██     ██   ██ ██    ██     ████  ████ ██    ██ ██   ██ ██      ██      ██
 *    ██   ██ █████   ███████    ██    ██████  ██    ██ ██         ██    ██ ██    ██ ██ ██  ██     ██   ██ ██    ██     ██ ████ ██ ██    ██ ██   ██ █████   ██      █████
 *    ██   ██ ██           ██    ██    ██   ██ ██    ██ ██         ██    ██ ██    ██ ██  ██ ██     ██   ██ ██    ██     ██  ██  ██ ██    ██ ██   ██ ██      ██      ██
 *    ██████  ███████ ███████    ██    ██   ██  ██████   ██████    ██    ██  ██████  ██   ████     ██████   ██████      ██      ██  ██████  ██████  ███████ ███████ ███████
 *
 *
 */

void detruire_ModeleQuizz(ModeleQuizz* mq)
{
  for(int i = NOMBRE_MAX_CHOIX; i < NOMBRE_MAX_CHOIX; i--)
  {
    free(mq->choix[i]);
  }
  free(mq->choix);
  free(mq->reponse);
  free(mq->question);
  free(mq);
}

/***
 *    ███████ ██   ██ ████████ ██████   █████  ██ ██████  ███████     ███    ██  ██████  ███    ███ ██████  ██████  ███████
 *    ██       ██ ██     ██    ██   ██ ██   ██ ██ ██   ██ ██          ████   ██ ██    ██ ████  ████ ██   ██ ██   ██ ██
 *    █████     ███      ██    ██████  ███████ ██ ██████  █████       ██ ██  ██ ██    ██ ██ ████ ██ ██████  ██████  █████
 *    ██       ██ ██     ██    ██   ██ ██   ██ ██ ██   ██ ██          ██  ██ ██ ██    ██ ██  ██  ██ ██   ██ ██   ██ ██
 *    ███████ ██   ██    ██    ██   ██ ██   ██ ██ ██   ██ ███████     ██   ████  ██████  ██      ██ ██████  ██   ██ ███████
 *
 *
 */

int extraire_nombre_reponses(char* fichier)
{
  FILE* squelette = fopen(fichier, "r");

  if (squelette == NULL)
    return 0;

  int nombre = 0;
  char ligne[TAMPON];

  while (fgets(ligne, TAMPON, squelette))
  {
    nombre++;
  }

  if (DEBUG)
      printf("Le fichier contient %d lignes\n", nombre);
  fclose(squelette);

  return
    (nombre-1);
}


/***
 *     ██████ ██   ██  █████  ██████   ██████  ███████ ███    ███ ███████ ███    ██ ████████     ██████  ██    ██      ██████  ██    ██ ██ ███████ ███████
 *    ██      ██   ██ ██   ██ ██   ██ ██       ██      ████  ████ ██      ████   ██    ██        ██   ██ ██    ██     ██    ██ ██    ██ ██    ███     ███
 *    ██      ███████ ███████ ██████  ██   ███ █████   ██ ████ ██ █████   ██ ██  ██    ██        ██   ██ ██    ██     ██    ██ ██    ██ ██   ███     ███
 *    ██      ██   ██ ██   ██ ██   ██ ██    ██ ██      ██  ██  ██ ██      ██  ██ ██    ██        ██   ██ ██    ██     ██ ▄▄ ██ ██    ██ ██  ███     ███
 *     ██████ ██   ██ ██   ██ ██   ██  ██████  ███████ ██      ██ ███████ ██   ████    ██        ██████   ██████       ██████   ██████  ██ ███████ ███████
 *                                                                                                                        ▀▀
 *
 */

void charger_quizz(ModeleQuizz* mq, char* fichier)
{
  printf("le fichier est %s\n", fichier);
  int nombre_lignes = extraire_nombre_reponses(fichier);
  mq->nombre_reponses = nombre_lignes - 1;

  if(nombre_lignes < 4 || nombre_lignes > NOMBRE_MAX_CHOIX+1)
  {
    printf("Le fichier en entrée ne comporte pas assez de lignes, ou trop\n");
    return;
  }

  FILE* squelette = fopen(fichier, "r");
  if (squelette == NULL)
    return;

  int nombre = 0;
  char ligne[TAMPON];

  while (fgets(ligne, TAMPON, squelette))
  {
    if(DEBUG)
      printf("%d %s\n", nombre, ligne);

    if(nombre == 0)
      strcpy(mq->question, ligne);

    else if(nombre == 1)
    {
      strcpy(mq->reponse, ligne);
      strcpy(mq->choix[nombre-1], ligne);
    }

    else
      strcpy(mq->choix[nombre-1], ligne);

    nombre++;
  }

fclose(squelette);
}
