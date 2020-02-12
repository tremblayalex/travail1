#pragma once
#include "carte.h"
#include "joueur.h"

const int maxCartes = 52;

class Donnees
{
public:
	Carte lesCartes[maxCartes];
	Joueur joueurUn;
	Joueur joueurDeux;

	Donnees();
};

