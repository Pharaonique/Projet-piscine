#include "grman/grman.h"
#include <iostream>
#include <fstream>
#include "Sous-p.h"
#include "graph.h"
#include "Menu.h"

///SOURCES:
/// CODE DE MONSIEUR FERCOQ
/// http://www.ece.fr/~fercoq/allegro/
/// https://openclassrooms.com/courses/programmez-avec-le-langage-c/lire-et-modifier-des-fichiers
/// http://codes-sources.commentcamarche.net/faq/1190-sauvegarde-binaire-d-un-objet-c

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");


    ///D�claration des bitmaps
    BITMAP* ecran=create_bitmap(1600,1200); //Cr�ation d'une bitmap sur laquelle on va s'appuyer pour afficher les images
    BITMAP* Menu=load_bitmap("Nemo.bmp",NULL); //Bitmaps du menu principal
    BITMAP* Graphe=load_bitmap("Graphe.bmp",NULL); //Bitmap d'acc�s au menu de selection des graphes � choisire
    BITMAP* Reseau=load_bitmap("Reseau.bmp",NULL); //Bitmap d'acc�s aux explications du jeu
    BITMAP* Quitter=load_bitmap("Quitter1.bmp",NULL); //Bitmap pour quitter

    int fin=0; // Variable de r�f�rence pour circuler dans la boucle de jeu
    menu(ecran,Menu,Graphe,Reseau,Quitter,fin); // Sous programme de l'ensemble des affichages et utilisations d'allegro

    return 0;
}
END_OF_MAIN();


