#include <stdio.h>
#include <stdlib.h>
#include <cassert>

typedef struct noeud {
	int n_donnee;
	struct noeud* fgauche;
	struct noeud* fdroite;
}noeud;

typedef struct arbre_binaire{

	noeud * racine;
	int taille;	//nb de noeuds
	
}arbre_binaire;

void initialisation(arbre_binaire* pArbre);

void parcoursPrefixe(noeud* racine, void (*pf)(noeud*));
void parcoursPostfixe(noeud* racine, void (*pf)(noeud*));
void parcoursInfixe(noeud* racine, void (*pf)(noeud*));
void afficher(noeud* n);

int nbNoeuds(noeud* racine);
int hauteurArbre(noeud* racine);

int inserArbreVide(arbre_binaire* pArbre, int n_val);
int ajoutNoeud(arbre_binaire* pArbre, int n_val);

noeud* supprNoeud(arbre_binaire* pArbre, noeud* courant, int n_val);
void supprNoeudArbre(arbre_binaire* pArbre, int val);
noeud* plusGrand(noeud* elem);

noeud* rechercheElem(arbre_binaire* pArbre, noeud* courant, int n_val, void (*pf)(int));
void elemPresent(int n_data);

void liberer(arbre_binaire* pArbre, noeud** p_racine);

int main() {

	arbre_binaire* pArbre=nullptr;
	pArbre = (arbre_binaire*)malloc(sizeof(arbre_binaire));
	initialisation(pArbre);

    inserArbreVide(pArbre, 10);	printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 20);		printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 8);		printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 5);		printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 6);		printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 4);		printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 3);		printf("taille : %d\n", pArbre->taille);

	printf("taille 2 : %d\n", nbNoeuds(pArbre->racine));
	printf("hauteur : %d\n", hauteurArbre(pArbre->racine));

	//parcoursPrefixe(pArbre->racine, &afficher);
	parcoursInfixe(pArbre->racine, &afficher);
	//parcoursPostfixe(pArbre->racine, &afficher);

	noeud *elem=supprNoeud(pArbre, pArbre->racine, 1);	printf("taille : %d\n", pArbre->taille);

	printf("\n");

	supprNoeudArbre(pArbre,6);
	parcoursInfixe(pArbre->racine, &afficher);		printf("taille : %d\n", pArbre->taille);

	supprNoeudArbre(pArbre,5);
	parcoursInfixe(pArbre->racine, &afficher);		printf("taille : %d\n", pArbre->taille);

	supprNoeudArbre(pArbre,1);
	parcoursInfixe(pArbre->racine, &afficher);		printf("taille : %d\n", pArbre->taille);

	supprNoeudArbre(pArbre,8);
	parcoursInfixe(pArbre->racine, &afficher);		printf("taille : %d\n", pArbre->taille);

	supprNoeudArbre(pArbre,3);
	parcoursInfixe(pArbre->racine, &afficher);		printf("taille : %d\n", pArbre->taille);

	rechercheElem(pArbre, pArbre->racine, 2, &elemPresent);
	rechercheElem(pArbre, pArbre->racine, 10, &elemPresent);
	
	if(pArbre!=nullptr)
		liberer(pArbre, &pArbre->racine);

	free(pArbre);

	return 0;
}




//PARCOURIR
//dans l'appel des fonction, remplacer (pfs) par le traitement � effectuer (&fonction) -> void + param�tre noeud*
void parcoursPrefixe(noeud* racine, void (*pf)(noeud*)) {
	if (racine != NULL) {
		(*pf)(racine);
		parcoursPrefixe(racine->fgauche,(*pf));
		parcoursPrefixe(racine->fdroite,(*pf));
	}
}

void parcoursPostfixe(noeud* racine, void (*pf)(noeud*)) {
	if (racine != NULL) {
		parcoursPostfixe(racine->fgauche, (*pf));
		parcoursPostfixe(racine->fdroite, (*pf));
		(*pf)(racine);
	}
}

void parcoursInfixe(noeud* racine, void (*pf)(noeud*)) {
	if (racine != NULL) {
		parcoursInfixe(racine->fgauche, (*pf));
		(*pf)(racine);
		parcoursInfixe(racine->fdroite, (*pf));
	}
}

void afficher(noeud* n) {

	printf("%d, ", n->n_donnee);
}


void initialisation(arbre_binaire* pArbre)
{
	pArbre->racine = NULL;
	pArbre->taille = 0;
}


int nbNoeuds(noeud* racine) {
	int n_noeud = 0;

	if (racine == nullptr)
		n_noeud = 0;
	else {
		n_noeud = 1 + nbNoeuds(racine->fgauche) + nbNoeuds(racine->fdroite);
	}

	return n_noeud;
}

int hauteurArbre(noeud* racine) {
	int hauteur = 0;

	if (racine == nullptr)
		hauteur = 0;
	else {
		int n_fg = nbNoeuds(racine->fgauche);
		int n_fd = nbNoeuds(racine->fdroite);

		if (n_fg > n_fd)
			hauteur = 1 + n_fg;
		else
			hauteur = 1 + n_fd;
	}
	return hauteur;
}


int inserArbreVide(arbre_binaire* pArbre, int n_val) {

	noeud* elem = NULL;
	elem = (noeud*)malloc(sizeof(noeud));

	if (elem == NULL) {
		return 0;
	}
	else {
		elem->n_donnee = n_val;

		elem->fgauche = nullptr;
		elem->fdroite = nullptr;

		pArbre->racine = elem;
		pArbre->taille ++;
		
		return 1;
	}
}

int ajoutNoeud(arbre_binaire* pArbre, int n_val)
{
	noeud* elem = NULL;
	elem = (noeud*)malloc(sizeof(noeud));
	
	noeud* courant = pArbre->racine;
	noeud* precedent = NULL;
	
	elem->fdroite = NULL;
	elem->fgauche = NULL;
	elem->n_donnee = n_val;

	// On avance jusqu'� trouver une place
	while (courant)
	{
		precedent = courant;
		if (elem->n_donnee < courant->n_donnee)
			courant = courant->fgauche;
		else
			courant = courant->fdroite;
	}

	// on a trouv� une place libre, et
    // precedent pointe vers le parent de notre
    // noeud � replacer.
	if (elem->n_donnee < precedent->n_donnee)
		precedent->fgauche = elem;
	else
		precedent->fdroite = elem;

	pArbre->taille++;
	return 1;
}

void liberer(arbre_binaire* pArbre, noeud** p_racine) {

	noeud* racine = *p_racine;

	if (racine != nullptr) {
		liberer(pArbre, &racine->fgauche);
		liberer(pArbre, &racine->fdroite);
		free(racine);
		pArbre->taille--;
	}
	*p_racine = nullptr;
}

noeud* supprNoeud(arbre_binaire *pArbre, noeud *courant, int n_val)
{
	if (courant == nullptr) { //Si arbre vide

		return courant;
	}
	else if (n_val < courant->n_donnee) {//Si val � suppr < donn�e du noeud courant => sous arbre gauche
		courant->fgauche= supprNoeud(pArbre,courant->fgauche, n_val);
	}
	else if (n_val > courant->n_donnee) {//Si val � suppr > donn�e du noeud courant => sous arbre droit
		courant->fdroite = supprNoeud(pArbre,courant->fdroite, n_val);
	}
	else
	{	//on a la valeur
		if (courant->fgauche == nullptr) { //si fils gauche est nullptr 
			pArbre->taille--;							// on retourne fils droit
			return courant->fdroite;
		}
		else if (courant->fdroite == nullptr) { //si fils droit est nullptr
			pArbre->taille--;								//on retourne fils gauche
			return courant->fgauche;
		}
		else { // dans le cas fils gauche et fils droit diff de nullptr
			noeud* succ = plusGrand(courant->fgauche);//on cherche le plus grand de fils gauche
				if (courant != nullptr) {
					courant->n_donnee = succ->n_donnee; //on remplace la valeur � supprimer par le successeur
					supprNoeud(pArbre, courant->fgauche,succ->n_donnee);//on supprime par r�cursivit� la valeur doublon du successeur.
				}
		}
	}
	return courant;
}

noeud* plusGrand(noeud* elem)
{
	noeud* courant = elem;
	if (elem->fdroite == nullptr) {
		return courant;
	}
	return plusGrand(courant->fdroite);
}

void supprNoeudArbre(arbre_binaire* pArbre, int val) {
	assert(pArbre);
	if (pArbre->racine)
		supprNoeud(pArbre,pArbre->racine,val);
}

noeud* rechercheElem(arbre_binaire* pArbre, noeud* courant, int n_val, void (*pf)(int)) {
	if (courant == nullptr) { //Si arbre vide

		return courant;
	}
	else if (n_val < courant->n_donnee) {//Si val � suppr < donn�e du noeud courant => sous arbre gauche
		courant->fgauche = supprNoeud(pArbre, courant->fgauche, n_val);
	}
	else if (n_val > courant->n_donnee) {//Si val � suppr > donn�e du noeud courant => sous arbre droit
		courant->fdroite = supprNoeud(pArbre, courant->fdroite, n_val);
	}
	else {	//on a la valeur
		(*pf)(n_val);
	}
	return courant;
}

void elemPresent(int n_data) {
	printf("la valeur %d est presente dans l'arbre", n_data);
}