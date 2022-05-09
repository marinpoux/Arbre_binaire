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

int isEquilibre(noeud* racine);
int diffEquilibre(noeud* fgauche, noeud* fdroite);
void equilibreArbre(arbre_binaire* pArbre);
void equilibrage(arbre_binaire* pArbre, noeud* racine, noeud* parent);
void rotationGauche(arbre_binaire* pArbre, noeud* parent, noeud* enfant);
void rotationDroite(arbre_binaire* pArbre, noeud* parent, noeud* enfant);

int main() {

	arbre_binaire* pArbre=nullptr;
	pArbre = (arbre_binaire*)malloc(sizeof(arbre_binaire));
	initialisation(pArbre);

    inserArbreVide(pArbre, 10);	//printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 20);		//printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 8);		//printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 5);		//printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 6);		//printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 4);		//printf("taille : %d\n", pArbre->taille);
	ajoutNoeud(pArbre, 3);		//printf("taille : %d\n", pArbre->taille);
	
	parcoursInfixe(pArbre->racine, &afficher);

	if (isEquilibre(pArbre->racine))
		printf("arbre equilibre\n");
	else
		printf("arbre desequilibre\n");

	equilibreArbre(pArbre);

	//if (isEquilibre(pArbre->racine))
	//	printf("arbre equilibre\n");
	//else
	//	printf("arbre desequilibre\n");

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
//dans l'appel des fonction, remplacer (pfs) par le traitement à effectuer (&fonction) -> void + paramètre noeud*
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
	if (racine == nullptr)
		return 0;
	else
		return (1 + nbNoeuds(racine->fgauche) + nbNoeuds(racine->fdroite));

}

int hauteurArbre(noeud* racine) {
	if (racine == nullptr)
		return 0;
	else {
		int n_fg = nbNoeuds(racine->fgauche);
		int n_fd = nbNoeuds(racine->fdroite);

		if (n_fg > n_fd)
			return (1 + n_fg);
		else
			return (1 + n_fd);
	}
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

	// On avance jusqu'à trouver une place
	while (courant)
	{
		precedent = courant;
		if (elem->n_donnee < courant->n_donnee)
			courant = courant->fgauche;
		else
			courant = courant->fdroite;
	}

	// on a trouvé une place libre, et
    // precedent pointe vers le parent de notre
    // noeud à replacer.
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
	if (n_val == pArbre->racine->n_donnee) {	//la fonctin a un probleme si on supprime, la racine, alors on contourne le probleme...
		return courant;
	}
	else if (courant == nullptr) { //Si arbre vide
		return courant;
	}
	else if (n_val < courant->n_donnee) {//Si val à suppr < donnée du noeud courant => sous arbre gauche
		courant->fgauche= supprNoeud(pArbre,courant->fgauche, n_val);
	}
	else if (n_val > courant->n_donnee) {//Si val à suppr > donnée du noeud courant => sous arbre droit
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
					courant->n_donnee = succ->n_donnee; //on remplace la valeur à supprimer par le successeur
					supprNoeud(pArbre, courant->fgauche,succ->n_donnee);//on supprime par récursivité la valeur doublon du successeur.
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
	else if (n_val < courant->n_donnee) {//Si val à suppr < donnée du noeud courant => sous arbre gauche
		courant->fgauche = supprNoeud(pArbre, courant->fgauche, n_val);
	}
	else if (n_val > courant->n_donnee) {//Si val à suppr > donnée du noeud courant => sous arbre droit
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

int isEquilibre(noeud* racine) {
	if (racine == nullptr)
		return 1;
	else {
		int n_fg, n_fd;
		n_fg = nbNoeuds(racine->fgauche);
		n_fd = nbNoeuds(racine->fdroite);
		//n_fg = hauteurArbre(racine->fgauche);
		//n_fd = hauteurArbre(racine->fdroite);

		if (abs(n_fg - n_fd) > 1)
			return 0;
		else {
			if (isEquilibre(racine->fgauche) && isEquilibre(racine->fdroite))
				return 1;
			else
				return 0;
		}
	}
}

int diffEquilibre(noeud* fgauche, noeud* fdroite) {
	//return nbNoeuds(fdroite) - nbNoeuds(fgauche);
	return hauteurArbre(fdroite) - hauteurArbre(fgauche);
}

void equilibreArbre(arbre_binaire* pArbre) {
	equilibrage(pArbre, pArbre->racine, nullptr);
}

void equilibrage(arbre_binaire* pArbre, noeud* racine, noeud* parent) {

	if (racine == nullptr) {
		return;
	}

	else {
		equilibrage(pArbre, racine->fgauche, racine);
		equilibrage(pArbre, racine->fdroite, racine);
	}

	int noeudBalance = diffEquilibre(racine->fgauche, racine->fdroite);
	if (noeudBalance == 2) {
		int balanceFd = diffEquilibre(racine->fdroite->fgauche, racine->fdroite->fdroite);
		if (balanceFd == -1)
			rotationDroite(pArbre, racine, racine->fdroite);
		rotationGauche(pArbre, parent, racine);
	}
	else if (noeudBalance == -2) {
		int balanceFg = diffEquilibre(racine->fgauche->fdroite, racine->fgauche->fgauche);
		if (balanceFg == 1)
			rotationGauche(pArbre, racine, racine->fgauche);
		rotationDroite(pArbre, parent, racine);
	}
}

void rotationGauche(arbre_binaire* pArbre, noeud* parent, noeud* enfant) {
	if (enfant == nullptr)
		return;
	if (parent != nullptr) {
		if (parent->fdroite == enfant)
			parent->fdroite = enfant->fdroite;
		else
			parent->fgauche = enfant->fdroite;
	}

	enfant->fdroite = enfant->fdroite->fdroite;

	parent = enfant->fdroite;
	enfant->fdroite->fgauche = enfant;
	if (enfant == pArbre->racine)
		pArbre->racine = enfant->fdroite;
}

void rotationDroite(arbre_binaire* pArbre, noeud* parent, noeud* enfant) {
	if (enfant == nullptr)
		return;
	if (parent != nullptr) {
		if (parent->fgauche == enfant)
			parent->fgauche = enfant->fgauche;
		else
			parent->fdroite = enfant->fgauche;
	}

	enfant->fgauche = enfant->fgauche->fdroite;

	parent = enfant->fgauche;
	enfant->fgauche->fdroite = enfant;
	if (enfant == pArbre->racine)
		pArbre->racine = enfant->fgauche;
}