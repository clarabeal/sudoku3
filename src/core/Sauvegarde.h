#ifndef _SAUVEGARDE_H 
#define _SAUVEGARDE_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Jeu.h"


using namespace std;
/**
\brief Contient toutes les donnees relatives a une partie sauvegardee de jeu a l'exception des grilles
*/
struct InfoSauvegarde {
	unsigned int id = 0;/**<L'identifiant unique de la partie, un entier positif (l'unicite doit etre verifiee lors de la creation d'une nouvelle sauvegarde)*/
	string name;
	/**<
	Le nom donne par le joueur a la sauvegarde
	\warning Ne peut pas contenir d'espace!*/
	unsigned int modeJeu = 0;/**<Mode de jeu dans lequel la partie a ete lance, 1: Mode classique, 2: Mode Pas a Pas, 3: Mode 1vs1  */
	unsigned int tailleGrille = 0;/**< La taille de la grille */
	unsigned long int chrono = 0;/**< Le temps en milliseconde depuis le debut de la partie */
};

/**\brief Gestionnaire d'acces aux sauvegardes
*\details Apres avoir ete initialise dans un dossier dedie a la gestion de suavegarde, la classe cree un index
* des sauvegardes presentes dans celui-ci et permet de les manipuler, supprimer et/ou d'en rajouter de nouvelles. 
**/
class gestSauvegarde
{
public:
	/**
	\brief Constructeur de la classe, il prend necessairement en parametre le chemin d'acces au dossier contenant les sauvegardes
	\details Un deuxieme emplacement peut etre indique, dans le cas ou le premier emplacement soit inaccessible, le gestionnaire tentera d'acceder au deuxieme.
	\warning L'emplacement 2 ne peut pas etre vide (""), il ne sera pas teste si c'est le cas.
	*/
	gestSauvegarde(string emplacement, string emplacement2 = "");
	~gestSauvegarde();/**<Detruit la liste des sauvegardes stockees sur le tas.*/
	
	unsigned int nbSauvegarde;/**< Le nombre de sauvegardes presentes dans le dossier emplacement.*/
	unsigned int maxId;/**< L'id le plus haut des sauvegardes deja presentes (permet de gerer l'unicite de l'id).*/

	/**
	*\brief Un tableau d'InfoSauvegarde de taille nbSauvegarde.
	*\details Ce tableau est forcement initialise, potentiellement de taille 0 si il n'y a aucune sauvegarde.
	*Chaque element du tableau correspond a une des sauvegardes presentes dans le dossier.
	*/
	InfoSauvegarde* listeSauvegarde;
 	string cheminDossier; /**<chemin vers le dossier qui contient les sauvegardes.*/
	
	/**
	\brief Met a jour la liste des sauvegardes presentes dans le dossier cheminDossier.
	\return 0 si l'ouverture d'index a echoue, 1 sinon 
	\see listeSauvegarde
	*/
	bool updateListe();
	
	/**
	\brief Renvoie une reference sur l'element de listeSauvegarde dont l'id est id.
	\param[in] id l'id de la sauvegarde dont on veut recuperer les informations.
	\warning Il est imperatif de verifier que l'id est bien assigne a une sauvegarde presente dans le dossier avant d'appeler la fonction.
	\see valideId
	*/
	InfoSauvegarde& getInfoSauvegarde(unsigned char id) const;

	/**
	\brief Renvoie vrai (true) si l'id correspond a une sauvegarde presente, faux (false) sinon
	\param[in] id l'id de la sauvegarde dont on veut recuperer les informations.*/
	bool valideId(unsigned char id) const;

	/**
	\brief Permet de charger les grilles de jeux presentes dans une sauvegarde.
	\param[in] id l'id de la grille a charger.
 	\param[out] g_sol contiendra apres execution la grille solution qui etait sauvegardee dans le fichier.
	\param[out] g_orig contiendra apres execution la grille originale qui etait sauvegardee dans le fichier.
	\param[out] g_jeu contiendra apres execution la grille jeu qui etait sauvegardee dans le fichier.
	\warning Il est imperatif de verifier que l'id est bien assignee a une sauvegarde presente dans le dossier avant d'appeler la focntion.
	\see valideId

	*/
	void loadFromFile(unsigned int id, Grille& g_sol, Grille& g_orig, Grille& g_jeu);

	/**
	\brief Permet de sauvegarder une partie de jeu
	\details Sauvegarde toutes les informations de jeu dans le dossier cheminDossier, si id = 0 ou que id n'est pas indique, une nouvelle sauvegarde
	est cree. L'id assigne a la partie sera la valeur de retour de la fonction.
	Si l'id est !=0 l'ancienne sauvegarde dont l'id etait id est mise a jour. Les parametres nom et mode de jeu ne seront pas mis a jour, c'est ceux de l'ancienne sauvegarde qui seront conserves 
	
	\param[in] jeu La partie de jeu a sauvegarder
	\param[in] name Le nom que le joueur veut donner a la sauvegarde(ignorer si id != 0)
	\param[in] mode Le mode de jeu dans lequel la partie est lancee(ignorer si id != 0)
	\param[in] id id de la partie a mettre a jour Parametre facultatif
	\warning Retourne -1 si une erreur s'est produite lors de l'ouverture de l'index des sauvegardes ou de la creation du fichier de sauvegarde
	*/
	int sauvegarder(Jeu& jeu, string name, int mode, unsigned int id = 0);

	/**
	\brief Supprime la sauvegarde dont l'id est id
	\param[in] id l'id de la sauvegarde a supprimer
	*/
	void supprimerSauvegarde(unsigned char id);

	/**
	\brief renomme la sauvegarde dont l'id est id
	\param[in] id l'id de la sauvegarde a supprimer
	\param[in] nzme le nouveau nom de la sauvegarde
	*/
	void renommerSauvegarde(unsigned int id, string name);
private:
};

#endif

