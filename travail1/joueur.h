#include <string>
#include "carte.h"
using namespace std;

#ifndef JoueurH
#define JoueurH

const int maxCartesAJouer = 26;

class Joueur
{
private:
	string nom;
	int nombreVictoires;
	int nombreDefaites;

	int indexDerniereCarteAJouer;
	Carte* mainDuJoueur[maxCartesAJouer];

public:
	Joueur();

	void setNomJoueur(const string& inNom);
	void ajouterUneVictoire();
	void ajouterUneDefaite();
	void ajouterUneCarte(Carte* inCarte);
	void enleverToutesLesCartes();

	string getNomJoueur() const;
	int getNombreVictoires() const;
	int getNombreDefaites() const;
	Carte* getCarte(const int& inIndexCarte) const;
};
#endif