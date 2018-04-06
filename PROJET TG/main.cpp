#include "grman/grman.h"
#include <iostream>
#include <fstream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;

int choix;

    std::cout << "Quel reseau voulez-vous afficher ?" << std::endl;
    std::cout << "Choix 1 : Petit reseau foret. " << std::endl << "Choix 2 : Grand reseau foret. " << std::endl;
    std::cout << "Choix 3 : Reseau marin. " << std::endl;
    std::cin >> choix;

    std::string b;
    //int b;
    //int c;

    if(choix==1)
    {
        b = "Fish.txt";
        //b = 13;
        //c = 7;
    }

    else if(choix==2)
    {
        b = "fichgrand.txt";
        //b = 30;
        //c = 12;
    }

    else if(choix==3)
    {
        b = "fichmarin.txt";
        //b = 16;
        //c = 8;
    }

    else
    {
        std::cout << std::endl << "Votre saisie est erronee. " << std::endl;
    }


    g.make_example(b);

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
    /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
     //g.ajouter();
       g.sauvgarder(b);
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


