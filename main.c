#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "modele_quizz.h"


void main()
{

ModeleQuizz* quizz = creer_ModeleQuizz("test.txt");
detruire_ModeleQuizz (quizz);
}
