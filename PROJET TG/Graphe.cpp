#include "Graphe.h"
#include <fstream>
#include <iostream>
#include <vector>

Graphe::Graphe()
    :order(0),matrice(NULL)
{

}
Graphe::~Graphe()
{
  //  cout<<"Dstor"<<endl;
}

bool** Graphe::allouer(int order)
{
    bool ** matrice;
    matrice = new bool* [order];
    for(int i=0; i<order; i++)
    {
        matrice[i]= new bool [order];


    }

    return matrice;

}
bool** Graphe::recup(bool **matrice)
{


    int order;
    ifstream fichier("Sommets.txt",ios::in);
    if(fichier)
    {

        fichier>>order;
        bool chiffre;
        matrice=allouer(order);
        int i,j;
        for( i=0; i<12; i++)
        {
            for(j=0; j<12; j++)
            {

                fichier>>chiffre;
                matrice[i][j]=chiffre;
            }
        }
        cout<<"\n"<<endl;
        fichier.close();
    }
    else
        cout<<"Erreur lors de l'ouverture du fichier"<<endl;

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            cout<<matrice[i][j];

        }
        cout<<"\n"<<endl;
    }

    ifstream fic("NomSommets.txt",ios::in);
    string nom;
    if(fic)
    {
        for(int i=0; i<12; i++)
        {
            fic>>nom;
            sommets.push_back(nom);
        }
    }
    else
    {
        cout<<"Erreur lors de l'ouverture du fichier"<<endl;
    }
    affichage(sommets, matrice);
    return matrice;


}

void Graphe::affichage(vector <string> sommets,bool **matrice)
{

    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            if(matrice[i][j]==1)
            {
                cout<<sommets[i]<<" influence "<<sommets[j]<<"\n"<<endl;
            }
        }
    }

}








