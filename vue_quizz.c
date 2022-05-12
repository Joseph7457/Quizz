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
#include <string.h>

#include "modele_quizz.h"


// Le controleur doit s'occuper de connecter les signaux.


/***
 *     ██████  ██    ██ ██ ███████ ███████ 
 *    ██    ██ ██    ██ ██    ███     ███  
 *    ██    ██ ██    ██ ██   ███     ███   
 *    ██ ▄▄ ██ ██    ██ ██  ███     ███    
 *     ██████   ██████  ██ ███████ ███████ 
 *       ▀▀
 *       ██████████████████████████████████████                                                                 
 */

VueQuizz* creer_vue_quizz(ModeleQuizz* mq)
{ 
  assert(mq);

  VueQuizz* vq = malloc(sizeof(VueQuizz));
  if(vq == NULL)
    return NULL;
    
  vq->mq = mq;

  vq->nombre_colonnes   = 2;  
  vq->nombre_reponses   = mq->nombre_reponses;  

  creer_question(vq);
  creer_table(vq);
  creer_choix(vq);

  return vq;
}



/***
 *     ██████ ██████  ███████  █████  ████████ ██  ██████  ███    ██ 
 *    ██      ██   ██ ██      ██   ██    ██    ██ ██    ██ ████   ██ 
 *    ██      ██████  █████   ███████    ██    ██ ██    ██ ██ ██  ██ 
 *    ██      ██   ██ ██      ██   ██    ██    ██ ██    ██ ██  ██ ██ 
 *     ██████ ██   ██ ███████ ██   ██    ██    ██  ██████  ██   ████ 
 *                                                                   
 *      ███████████████████████████████████████████████████████████████████                                                             
 */



void creer_table(VueQuizz* vq)
{  
  int nombre_questions =   vq->nombre_questions;
  int nombre_colonnes  =   vq->nombre_colonnes;
  int nombre_lignes    = ( nombre_questions / nombre_colonnes);
  int modulo           =   nombre_questions % nombre_colonnes;

  if( modulo > 0)
    nombre_lignes++;

  vq->table = gtk_table_new (nombre_colonnes, nombre_lignes+1, TRUE);
}

void creer_question(VueQuizz* vq)
{
  assert(vq && vq->mq);
  vq->question = gtk_button_new_with_label(vq->mp->question);
}

void creer_choix(VueQuizz* vq)
{ 
  assert(vq && vq->mq);
  vq->choix = malloc( sizeof(char*) * vq->nombre_questions);

  for (int i = 0; i < vq->NOMBRE_MAX_CHOIX; i++)
  {
    vq[i] = gtk_button_new_with_label(vq->mp->choix);
  }
  
}

/***
 *     █████   ██████ ████████ ██    ██  █████  ██      ██ ███████  █████  ████████ ██  ██████  ███    ██ 
 *    ██   ██ ██         ██    ██    ██ ██   ██ ██      ██ ██      ██   ██    ██    ██ ██    ██ ████   ██ 
 *    ███████ ██         ██    ██    ██ ███████ ██      ██ ███████ ███████    ██    ██ ██    ██ ██ ██  ██ 
 *    ██   ██ ██         ██    ██    ██ ██   ██ ██      ██      ██ ██   ██    ██    ██ ██    ██ ██  ██ ██ 
 *    ██   ██  ██████    ██     ██████  ██   ██ ███████ ██ ███████ ██   ██    ██    ██  ██████  ██   ████ 
 *                                                                                                        
 *    ██████████████████████████████████████████████████████████████████████████████████████████████████████                                                                                                    
 */



void actualiser(VueQuizz* vq)
{ 
  // Enlever les Widgets associés avant de modifier la table
  for(int i = 0; i < vq->nombre_reponses; i++ )
    gtk_container_remove(vq->table, vq->choix[i]);

  // Vérifier si la table doit être redimensionnées.
  if((vq->mq->nombre_reponses != mq->nombre_reponses) ||
     (vq->mq->nombre_colonnes != mq->nombre_colonnes) )
  { 
    vq->mq->nombre_reponses = mq->nombre_reponses;
    vq->mq->nombre_colonnes = mq->nombre_colonnes;
    actualiser_table(vq);
  }

  actualiser_question(vq);
  actualiser_choix(vq);

  /* Attacher les widgets à la table*/
  int colonne = 0; int ligne = 0;
  for (int i = 0; i < vq->nombre_reponses; i++)
  {
    gtk_table_attach(vq->tables, vq->choix[i], ligne+1, ligne+2, colonne, colonne+1, TRUE, TRUE, 0, 0);
    ligne++;
    if( (ligne != 0) && (ligne % vq->nombre_reponses == 0))
    {
      colonne++;
      ligne = 0;
    }
    
  }

  gtk_table_attach(vq->tables, vq->choix[i], ligne, ligne+1, 0, mq->nombre_colonnes +1, TRUE, TRUE, 0, 0);


}


void actualiser_table(VueQuizz* vq)
{
  int nombre_reponses  =   vq->nombre_reponses;
  int nombre_colonnes  =   vq->nombre_colonnes;
  int nombre_lignes    = ( nombre_reponses / nombre_colonnes);
  int modulo           =   nombre_reponses % nombre_colonnes;

  if( modulo > 0)
    nombre_lignes++;

  gtk_table_resize (nombre_lignes+1, nombre_colonnes);
}

void actualiser_question(VueQuizz* vq)
{
  vq->reponse = gtk_button_new_with_label(vq->mp->reponse);
}

void actualiser_choix(VueQuizz* vq)
{
  for( int i = 0; i < vq->mp->choix; i++ )
    gtk_label_set_text(vq->choix[i], vq->mp->choix[i]);
}


/***
 *    ███    ███  ██████  ██████  ██ ███████ ██  ██████ ██  █████  ████████ ██  ██████  ███    ██ 
 *    ████  ████ ██    ██ ██   ██ ██ ██      ██ ██      ██ ██   ██    ██    ██ ██    ██ ████   ██ 
 *    ██ ████ ██ ██    ██ ██   ██ ██ █████   ██ ██      ██ ███████    ██    ██ ██    ██ ██ ██  ██ 
 *    ██  ██  ██ ██    ██ ██   ██ ██ ██      ██ ██      ██ ██   ██    ██    ██ ██    ██ ██  ██ ██ 
 *    ██      ██  ██████  ██████  ██ ██      ██  ██████ ██ ██   ██    ██    ██  ██████  ██   ████ 
 *                                                                                                
 *                                                                                                
 */

void modifier_nombre_colonnes(VueQuizz* vq, int nombre_de_colonnes)
{
  vq->nombre_de_colonnes = nombre_de_colonnes;
}

/***
 *    ███    ██ ███████ ████████ ████████  ██████  ██    ██  █████   ██████  ███████ 
 *    ████   ██ ██         ██       ██    ██    ██  ██  ██  ██   ██ ██       ██      
 *    ██ ██  ██ █████      ██       ██    ██    ██   ████   ███████ ██   ███ █████   
 *    ██  ██ ██ ██         ██       ██    ██    ██    ██    ██   ██ ██    ██ ██      
 *    ██   ████ ███████    ██       ██     ██████     ██    ██   ██  ██████  ███████ 
 *                                                                                   
 *  ████████████████████████████████████████████████████████████████████████████████████                                                                            
 */

/* Retire les widgets et nettoye la table*/
void nettoyer_table(VueQuizz* vq)
{

}

