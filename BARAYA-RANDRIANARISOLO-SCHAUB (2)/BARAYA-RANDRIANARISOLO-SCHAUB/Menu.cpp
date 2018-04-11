#include "Menu.h"
#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "graph.h"

void menu (BITMAP* ecran, BITMAP* Menu, BITMAP* Graphe, BITMAP* Reseau, BITMAP* Quitter, int fin)
{

    fin = 0; // Variable de boucle de jeu, tant que fin = 0, on continue
    int temp = 0 ; // Variable de temporisation, en fonction des actions effectuées dans le menu
    while (!fin && temp==0)
    {
        blit(Menu,ecran,0,0,0,0,1024,768); // Affichage sur écran vide

        if (mouse_x>=50 && mouse_x<=415 && mouse_y>=40 && mouse_y<=200) // Zone de selection
        {
            blit(Graphe,ecran,0,0,0,0,1024,768);
            if(mouse_b&1) // Accès au menu de sélection de graphes
            {

            ///Chargement de chaque bitmap
            BITMAP* Choix = load_bitmap("Choix.bmp", NULL);
            BITMAP* Choix1 = load_bitmap("Choix1.bmp", NULL);
            BITMAP* Choix2 = load_bitmap("Choix2.bmp", NULL);
            BITMAP* Choix3 = load_bitmap("Choix3.bmp", NULL);
            choix(ecran,Choix,Choix1,Choix2,Choix3);
                temp = 1 ;
            }
        }

        if (mouse_x>=50 && mouse_x<=415 && mouse_y>=220 && mouse_y<=380)
        {
            blit(Reseau,ecran,0,0,0,0,1024,768);
            if (mouse_b&1) // Accès aux règles et définitions du jeu
            {
                BITMAP* Reseau2=load_bitmap("Reseau2.bmp",NULL);
                blit(Reseau2,ecran,0,0,0,0,1024,728);
                temp = 2;
            }
        }

        if (mouse_x>=50 && mouse_x<=415 && mouse_y>=400 && mouse_y<=560)
        {
            blit(Quitter,ecran,0,0,0,0,1024,768);
            if(mouse_b&1) // Quitter le jeu
            {
                BITMAP* Quitter12=load_bitmap("Quitter12.bmp",NULL);
                blit(Quitter12,ecran,0,0,0,0,1024,768);
                temp = 3;
            }
        }

        blit(ecran,screen,0,0,0,0,1024,768);


        if(temp==2) // Condition pour rester dans la boucle de jeu selon la sélection faite
        {
            rest(3000);
            temp=0;
        }

        if (temp==3) // Condition pour rester dans la boucle de jeu selon la sélection faite
        {
            rest(1000);
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        if (mouse_b&2) // Quitter directement le jeu
            fin = 1 ;
    }
}

void choix (BITMAP* ecran, BITMAP* Choix, BITMAP* Choix1, BITMAP* Choix2, BITMAP* Choix3) // Sous programme des choix des graphes
{
    int choice; // Variable de choix défini en fonction de temp et de la zone de selection
    int temp = 0; // Variable de temporisation pour revenir dans la boucle de jeu
    bool fin =true ; // Variable pour rester dans la boucle de jeu
    while (fin)
    {
        blit(Choix,ecran,0,0,0,0,1024,768);

        if (mouse_x>=0 && mouse_x<=341 && mouse_y>=0 && mouse_y<=768)
            {
                blit(Choix1,ecran,0,0,0,0,1024,768);
                if(mouse_b&1)
                {
                    temp=1;
                    choice=1;
                }
            }

        if (mouse_x>=342 && mouse_x<=682 && mouse_y>=0 && mouse_y<=768)
            {
                blit(Choix2,ecran,0,0,0,0,1024,768);
                if(mouse_b&1)
                {
                    temp=1;
                    choice=2;
                }
            }

         if (mouse_x>=683 && mouse_x<=1024 && mouse_y>=0 && mouse_y<=768)
            {
                blit(Choix3,ecran,0,0,0,0,1024,768);
                if(mouse_b&1)
                {
                    temp=1;
                    choice=3;
                }
            }

        if(key[KEY_SPACE])
        {
            temp=2;
        }

        blit(ecran,screen,0,0,0,0,1024,768);

        if (temp==1)
        {
            Selectiongraph(choice);
            temp=0;
        }

        if(temp==2)
        {
            BITMAP* ecran=create_bitmap(1600,1200);
            BITMAP* Menu=load_bitmap("Nemo.bmp",NULL);
            BITMAP* Graphe=load_bitmap("Graphe.bmp",NULL);
            BITMAP* Reseau=load_bitmap("Reseau.bmp",NULL);
            BITMAP* Quitter=load_bitmap("Quitter1.bmp",NULL);
            menu(ecran,Menu,Graphe,Reseau,Quitter,fin);

        }

    }
}

void Selectiongraph(int choice) // Sous programe de chargement des fichiers texte selon le choix
{
    std::string milieu;
    Graph g;

    if(choice==1)
    {
        milieu = "Fish.txt";
    }

    if(choice==2)
    {
        milieu = "Mer.txt";
    }

    if(choice==3)
    {
        milieu = "poisson.txt";
    }

    g.charger(milieu);

    while ( !key[KEY_ESC] ) // Boucle du jeu
    {
        g.update();
        grman::mettre_a_jour();
        g.sauvgarder(milieu);
    }
}
