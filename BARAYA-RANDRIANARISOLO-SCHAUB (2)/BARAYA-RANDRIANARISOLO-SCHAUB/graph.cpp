#include "graph.h"
#include <fstream>
#include "Menu.h"
/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_tool_box.add_child(m_quitter_box);
    m_quitter_box.set_dim(81,90);
    m_quitter_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_quitter_box.set_bg_color(BLEU);

    m_tool_box.add_child(m_sommet);
    m_sommet.set_dim(80,30);
    m_sommet.set_pos(0,0);

    m_sommet.set_bg_color(ROSE);
    m_sommet.add_child(m_sommet_text);
    m_sommet_text.set_message("ajouter sommet");
    m_sommet_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_tool_box.add_child(m_edge);
    m_edge.set_dim(80,30);
    m_edge.set_pos(0,50);

    m_edge.set_bg_color(ROSE);
    m_edge.add_child(m_edge_text);
    m_edge_text.set_message("ajouter arcs");
    m_edge_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);


}


void Graph::charger(std::string graphe)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    std::ifstream fichier(graphe.c_str()); // Lecture d'un fichier texte
    int pX, pY, vIn, vOut; // Variable de support pour une arete
    double pEdge,pVertex; // Variables de support pour une arete et un sommet
    std::string getname; // Variable de support pour l'animal

    if (fichier){ // Lecture et récupération des valeurs du fichier texte

        fichier >> Graph::rang;

        fichier >> Graph::nEdge;
        std::cout<< nEdge;
        for(int i=0 ; i < rang ; i++){ // Boucle selon le nombre de sommets

        fichier >> pVertex;
        fichier >> pX;
        fichier >> pY;
        fichier >> getname;

        add_interfaced_vertex(i,pVertex,pX,pY,getname); // Ajout de chaque sommet sur l'interface graphique
        }
        for(int j=0 ; j < nEdge ; j++){ // Boucle selon le nombre d'aretes

            fichier >> vIn;
            fichier >> vOut;
            fichier >> pEdge;
            add_interfaced_edge(j,vIn,vOut,pEdge); // Ajout de chaque arete sur l'interface graphique


        }


    fichier.close();

}}

void Graph::sauvgarder(std::string graphe){

    std::ofstream fichier(graphe.c_str(),std::ios::out | std::ios::trunc); // Ecriture sur le fichier texte

    std::string picName; // Nom de l'image à sauvegarder
        if(fichier){
            fichier << Graph::rang <<std::endl; // Nombre de sommets
            fichier << Graph::nEdge<<std::endl; // Nombre d'aretes

            for(auto &elt : m_vertices){ // Récupération de l'ensemble des données d'un animal
         fichier << elt.second.m_value<<" ";
         fichier <<elt.second.m_interface->m_top_box.get_frame_pos().x<<" ";
         fichier <<elt.second.m_interface->m_top_box.get_frame_pos().y<<" ";
        picName=elt.second.m_interface->m_img.get_pic_name();
        picName.erase(picName.size()-4,4);
         fichier <<picName + ".png"<<std::endl;
    }
        for(auto &elt : m_edges){ // Connexion entre les arrêtes

            fichier << elt.second.m_from<<" ";
            fichier << elt.second.m_to<<" ";
            fichier << elt.second.m_weight<<std::endl;

        }
        fichier.close();
        }

}


void Graph::ajoutSommet()
{
    std::string photo; // Créature souhaité
    int s; // Indice du sommet
    std::cout << "Quel sommet souhaitez-vous ajouter ? " << std::endl;
    std::cin >> photo;
    s = m_vertices.size();
    add_interfaced_vertex(s,0,0,0,photo+".png",s);
    rang++; // Incrémentation du nombre de sommet selon le nombre d'ajour souhaité
}

void Graph::ajoutArete()
{
    int depart; // Arete de départ
    int arrive; // Arete d'arrivée
    int p; // Poids de l'arete
    std::cout << "Veuillez entrer l'indice du sommet de depart : " << std::endl;
    std::cin >> depart;
    std::cout << "Veuillez entrer l'indice du sommet d'arrive : " << std::endl;
    std::cin >> arrive;
    p = m_edges.size(); // Attribution du poids à la nouvelle arete
    add_interfaced_edge(p,depart,arrive,50); // Ajout de l'arete sur l'interface
    nEdge++; // Incrémentation du nombre d'arete selon le nombre d'ajour souhaité
}


/// eidx index of edge to remove

void Graph::test_remove_edge(int eidx)

{

    /// référence vers le Edge à enlever

    Edge &remed=m_edges.at(eidx);



    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;



    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2

    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;

    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;

    std::cout << m_edges.size() << std::endl;



    /// test : on a bien des éléments interfacés

    if (m_interface && remed.m_interface)

    {

        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr

        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)

        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe

        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );

    }



    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !

    /// References sur les listes de edges des sommets from et to

    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;

    std::vector<int> &veto = m_vertices[remed.m_to].m_in;

    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );

    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );



    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)

    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface

    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !

    m_edges.erase( eidx );





    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2

    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;

    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;

    std::cout << m_edges.size() << std::endl;



}


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    if(grman::mouse_click && m_interface->m_sommet.is_mouse_over())
    {
       ajoutSommet();
    }
        if(grman::mouse_click && m_interface->m_edge.is_mouse_over())
    {
       ajoutArete();
    }

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from = id_vert1;

    m_edges[idx].m_to = id_vert2;



    m_vertices[id_vert1].m_out.push_back(idx);

    m_vertices[id_vert2].m_in.push_back(idx);
}

