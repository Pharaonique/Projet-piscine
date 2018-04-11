#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "graph.h"


using namespace std;

void menu (BITMAP* ecran, BITMAP* Menu,BITMAP* Informations, BITMAP* Reseaux, BITMAP* Quitter, int v); // Sous programme d'affichage du menu

void choix (BITMAP* ecran,BITMAP* Choix, BITMAP* Choix1, BITMAP* Choix2, BITMAP* Choix3); // Sous programme d'affichage de la page de selection des graphes

void Selectiongraph(int choice); // Sous programme de selection des graphes linké avec le code de fercoq fourni



#endif // MENU_H_INCLUDED
