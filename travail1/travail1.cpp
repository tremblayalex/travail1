#include "donnees.h"
#include "..\screen\screen.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

Donnees leJeu;

void InitialiserJoueurs();
void Jouer();
int demanderNombreDeCartesADistribuer();
bool isNumber(const string& s);
void melangerLesCartesDuJeu();
int generateRandomInt(const int& min, const int& max);
void distribuerLesCartesAuxJoueurs(const int& nombreDeCartesADistribuer);
void afficherLesCartesDesJoueurs(const int& nombreCarteParJoueur);
void afficherLeGrandGagnant();

int main() 
{
	char fini = 'n';
	srand((unsigned)time(NULL));
	InitialiserJoueurs();
	while (fini=='n' || fini=='N')
	{
		Jouer();
		cout << "\nTermine (n/o) ? ";
		cin >> fini;		
	}

	afficherLeGrandGagnant();
}

void InitialiserJoueurs()
{
	string nomJoueurUn, nomJoueurDeux;

	cout << "         Initialisation des joueurs          " << endl;
	cout << "---------------------------------------------" << endl << endl;
	cout << "Entrez le nom du premier joueur: ";
	cin >> nomJoueurUn;
	cout << "Entrez le nom du deuxieme joueur: ";
	cin >> nomJoueurDeux;

	ClrScr();

	leJeu.joueurUn.setNomJoueur(nomJoueurUn);
	leJeu.joueurDeux.setNomJoueur(nomJoueurDeux);
}

void Jouer() 
{
	ClrScr();

	int nombreDeCartesADistribuer = demanderNombreDeCartesADistribuer();

	melangerLesCartesDuJeu();
	distribuerLesCartesAuxJoueurs(nombreDeCartesADistribuer);

	afficherLesCartesDesJoueurs(nombreDeCartesADistribuer);
}

int demanderNombreDeCartesADistribuer()
{
	int nombreDeCartesADistribuer;

	cout << "            Configuration du jeu             " << endl;
	cout << "---------------------------------------------" << endl << endl;

	bool requierementsMet = false;
	while (!requierementsMet)
	{	
		string entree;

		cout << "Entrez le nombre de carte a distribuer [1, 26]: ";
		cin >> entree;

		if (isNumber(entree))
		{
			nombreDeCartesADistribuer = stoi(entree);

			if (nombreDeCartesADistribuer >= 1 && nombreDeCartesADistribuer <= 26)
			{
				requierementsMet = true;
			}
			else
			{
				cout << "[Erreur] Veuillez entrer une valeur entre 1 et 26!" << endl;
			}
		}
		else
		{
			cout << "[Erreur] Veuillez entrer un nombre valide" << endl;
		}		
	}

	return nombreDeCartesADistribuer;
}

bool isNumber(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void melangerLesCartesDuJeu()
{
	const int nombreDeMelangeAFaire = 100;

	for (int compteur = 1; compteur <= nombreDeMelangeAFaire; compteur++)
	{
		int indexPremiereCarteAEchanger = generateRandomInt(0, maxCartes - 1);
		int indexDeuxiemeCarteAEchanger = generateRandomInt(0, maxCartes - 1);

		Carte* adressePremiereCarte = &(leJeu.lesCartes[indexPremiereCarteAEchanger]);
		Carte* adresseDeuxiemeCarte = &(leJeu.lesCartes[indexDeuxiemeCarteAEchanger]);

		leJeu.lesCartes[indexPremiereCarteAEchanger] = *adresseDeuxiemeCarte;
		leJeu.lesCartes[indexDeuxiemeCarteAEchanger] = *adressePremiereCarte;
	}
}

int generateRandomInt(const int& min, const int& max)
{
	return rand() % (max - min + 1) + min;
}

void distribuerLesCartesAuxJoueurs(const int& nombreDeCartesADistribuer)
{
	leJeu.joueurUn.enleverToutesLesCartes();
	leJeu.joueurDeux.enleverToutesLesCartes();

	for (int index = 0; index < nombreDeCartesADistribuer; index++)
	{
		leJeu.joueurUn.ajouterUneCarte(&(leJeu.lesCartes[index]));
		leJeu.joueurDeux.ajouterUneCarte(&(leJeu.lesCartes[index + 26]));
	}
}

void afficherLesCartesDesJoueurs(const int& nombreCarteParJoueur)
{
	int totalJoueurUn = 0, totalJoueurDeux = 0;
	
	ClrScr();

	cout << "                 Voici le jeu                " << endl;
	cout << "---------------------------------------------" << endl;

	cout << endl << "-- Joueur " << leJeu.joueurUn.getNomJoueur() << " --" << endl;
	for (int i = 0; i < nombreCarteParJoueur; i++)
	{
		totalJoueurUn += leJeu.joueurUn.getCarte(i)->GetValeur();
		cout << "Carte #" << i << " : " << leJeu.joueurUn.getCarte(i)->GetValeur() << " " << leJeu.joueurUn.getCarte(i)->GetAtout() << endl;
	}
	cout << "-- Total: " << totalJoueurUn << " --" << endl;

	cout << endl << "-- Joueur " << leJeu.joueurDeux.getNomJoueur() << " --" << endl;
	for (int i = 0; i < nombreCarteParJoueur; i++)
	{
		totalJoueurDeux += leJeu.joueurDeux.getCarte(i)->GetValeur();
		cout << "Carte #" << i << " : " << leJeu.joueurDeux.getCarte(i)->GetValeur() << " " << leJeu.joueurDeux.getCarte(i)->GetAtout() << endl;
	}
	cout << "-- Total: " << totalJoueurDeux << " --" << endl << endl;

	if (totalJoueurUn > totalJoueurDeux)
	{
		cout << "---- Le joueur '" << leJeu.joueurUn.getNomJoueur() << "' est vainceur! ----" << endl;
		leJeu.joueurUn.ajouterUneVictoire();
		leJeu.joueurDeux.ajouterUneDefaite();
	}
	else
	{
		cout << "---- Le joueur '" << leJeu.joueurDeux.getNomJoueur() << "' est vainceur! ----" << endl;
		leJeu.joueurDeux.ajouterUneVictoire();
		leJeu.joueurUn.ajouterUneDefaite();
	}
}

void afficherLeGrandGagnant()
{
	ClrScr();

	if (leJeu.joueurUn.getNombreVictoires() == leJeu.joueurDeux.getNombreVictoires())
	{
		cout << "                  Match nul                  " << endl;
		cout << "---------------------------------------------" << endl << endl;
		cout << "La partie s'est terminee en match nul!" << endl;
		cout << "Les joeurs avaient tout deux " << leJeu.joueurUn.getNombreVictoires() << " victoire(s)." << endl;
	}
	else
	{
		string nomDuGrandGagnant;

		if (leJeu.joueurUn.getNombreVictoires() > leJeu.joueurDeux.getNombreVictoires())
		{
			nomDuGrandGagnant = leJeu.joueurUn.getNomJoueur();
		}
		else
		{
			nomDuGrandGagnant = leJeu.joueurDeux.getNomJoueur();
		}

		cout << "                 Grand gagnant               " << endl;
		cout << "---------------------------------------------" << endl << endl;
		cout << "Le grand gagnant est..." << endl;
		cout << nomDuGrandGagnant << endl;
	}

	

}