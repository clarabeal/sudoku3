#ifndef _SAUVEGARDE_H 
#define _SAUVEGARDE_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Jeu.h"


using namespace std;
/**
\brief Contient toutes les donnees relatives a une partie sauvegardee de jeu a l'excpetion des grilles
*/
struct InfoSauvegarde {
	unsigned int id;/**<L'identifiant unique de la partie, un entier positif (l'unicite doit etre verifie lors de la creation d'une nouvelle sauvegarde)*/
	string name;
	/**<
	Le nom donne par le joueur a la sauvegarde
	\warning Ne peut pas contenir d'espace!*/
	unsigned int modeJeu;/**<Mode de jeu dans le quel la partie a ete lance, 1: Mode classique, 2: Mode Pas a Pas, 3: Mode 1vs1  */
	unsigned int tailleGrille;/**< La taille de la grille */
	unsigned long int chrono;/**< Le temps en milliseconde depuis le debut de la partie */
};

/**\brief Gestionnaire d'acces au sauvegarde
*\details Apres avoir ete init dans un dossier dedie a la gestion de suavegarde, la classe cree un index
* des sauvegardes presentes dans celui-ci et permet de les manipuler, supprimer et/ou d'en rajouter de nouvelles. 
**/
class gestSauvegarde
{
public:
	/**
	\brief Constructeur de la classe, il prend nescessairement en parametre le chemin d'acces au dossier contenant les sauvegardes
	\details Un deuxieme emplacement peut etre indique, dans le cas ou le premiere emplacement soit inaccessible, le gestionnaire tenteras d'acceder au deuxieme.
	\warning L'emplacement 2 ne peut pas etre vide (""), il ne sera pas teste si c'est le cas.
	*/
	gestSauvegarde(string emplacement, string emplacement2 = "");
	~gestSauvegarde();/**<Detruit la liste des sauvegardes stocker sur le tas.*/
	
	unsigned int nbSauvegarde;/**< Le nombre de sauvegarde presente dans le dossier emplacement.*/
	unsigned int maxId;/**< L'id le plus haut des sauvegarde deja presente(permet de gerer l'unicite de l'id).*/

	/**
	*\brief Un tableau d'InfoSauvegarde de taille nbSauvegarde.
	*\details Ce tableau est forcement initialise, potentiellement de taille 0 si il n'y a aucuen sauvegarde.
	*Chaque element du tableau correspond a une des sauvegardes presente dans le dossier.
	*/
	InfoSauvegarde* listeSauvegarde;
 	string cheminDossier; /**<chemin vers le dossier qui contient les sauvegardes.*/
	
	/**
	\brief Mets a jour la liste des sauvegardes presentes dans le dossier cheminDossier.
	\return 0 si louverture de index a echoue 1 sinon 
	\see listeSauvegarde
	*/
	bool updateListe();
	
	/**
	\brief Renvoie une reference sur l'element de listeSauvegarde dont l'id est id.
	\param[in] id l'id de la sauvegarde dont on veut recuperer les informations.
	\warning Il est imperatif de verifier que l'id est bien assigne a une sauvegarde presente dans le dossier avant d'appeler la focntion.
	\see valideId
	*/
	InfoSauvegarde& getInfoSauvegarde(unsigned char id) const;

	/**
	\brief Renvoie vraie (true) si l'id correspond a une sauvegarde presente faux (false) sinon
	\param[in] id l'id de la sauvegarde dont on veut recuperer les informations.*/
	bool valideId(unsigned char id) const;

	/**
	\biref permet de charger les grilles de jeux presentes dans une sauvegarde.
	\param[in] id l'id de la grille a chargee.
 	\param[out] g_sol contiendras apres execution la grille solution qui ete sauvegardee dans le fichier.
	\param[out] g_orig contiendras apres execution la grille original qui ete sauvegardee dans le fichier.
	\param[out] g_jeu contiendras apres execution la grille jeu qui ete sauvegardee dans le fichier.
	\warning Il est imperatif de verifier que l'id est bien assigne a une sauvegarde presente dans le dossier avant d'appeler la focntion.
	\see valideId

	*/
	void loadFromFile(int id, Grille& g_sol, Grille& g_orig, Grille& g_jeu);

	/**
	\brief Permet de sauvegarder une partie de jeu
	\details Sauvegarde toutes les informations de jeu dans le dossier cheminDossier, si id = 0 ou que id n'est pas indique, une nouvelle sauvegarde
	est cree. l'id assigne a la partie serat la valeur de retour de la fonction.
	Si l'id est !=0 l'ancienne sauvegarde dont l'id etait id est mise a jour. Les parametre nom et mode de jeu ne seront pas mise a jour, c'est ceux de l'ancienne sauvegarde qui seront conserves 
	
	\param[in] jeu La partie de jeu a sauvegarder
	\param[in] name Le nom que le joeur veut donner a la sauvegarde(ignorer si id != 0)
	\param[in] mode Le mode de jeu dans le quel la partie est lancee(ignorer si id != 0)
	\param[in] id id de la partie a mettre a jour Parametre facultatif
	\warning Retourne -1 si une erreur c'est produit lors de l'ouverture de l'index des sauvegardes ou de la creationd du fichier de sauvegarde
	*/
	int sauvegarder(Jeu& jeu, string name, int mode, int id = 0);

	/**
	\brief supprime la sauvegarde dont l'id est id
	\param[in] id l'id a de la sauvegarde a supprimer
	*/
	void supprimerSauvegarde(unsigned char id);

private:

};

#endif

