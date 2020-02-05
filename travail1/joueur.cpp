#include "joueur.h"

Joueur::Joueur() :
	nom(""),
	nombreVictoires(0),
	nombreDefaites(0),
	indexDerniereCarteAJouer(0),
	mainDuJoueur()
{}

void Joueur::setNomJoueur(const string& inNom)
{
	nom = inNom;
}

void Joueur::ajouterUneVictoire()
{
	nombreVictoires++;
}

void Joueur::ajouterUneDefaite()
{
	nombreDefaites++;
}

void Joueur::ajouterUneCarte(Carte* inCarte)
{
	if (indexDerniereCarteAJouer < maxCartesAJouer)
	{
		mainDuJoueur[indexDerniereCarteAJouer] = inCarte;

		indexDerniereCarteAJouer++;
	}
	else
	{
		cout << "[Erreur] Espace maximal excédé pour le tableau de carte 'manDuJoueur'" << endl;
		cout << "À la ligne" << __LINE__ << endl;
	}
	
}

void Joueur::enleverToutesLesCartes()
{
	indexDerniereCarteAJouer = 0;
}

string Joueur::getNomJoueur() const
{
	return nom;
}

int Joueur::getNombreVictoires() const
{
	return nombreVictoires;
}

int Joueur::getNombreDefaites() const
{
	return nombreDefaites;
}

Carte* Joueur::getCarte(const int& inIndexCarte) const
{
	return mainDuJoueur[inIndexCarte];
}
