#include "donnees.h"

const string atoutsCarte[] =
{
	"pique", "coeur", "trefle", "carreau"
};

const int nombreValeurParAtout = 13;

Donnees::Donnees()
{
	int index = 0;

	for (string atout : atoutsCarte)
	{
		for (int valeur = 1; valeur <= nombreValeurParAtout; valeur++)
		{
			lesCartes[index].InitialiserCarte(valeur, atout);

			index++;
		}
	}
}

