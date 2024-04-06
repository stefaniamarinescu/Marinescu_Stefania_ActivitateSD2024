#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Galerie Galerie;

struct Galerie
{
	int cod;
	char* nume;
	float pretIntrare;
};

typedef struct nod nod;

struct nod
{
	Galerie info;
	nod* next;
};

typedef struct hashTable HashTable;

struct hashTable
{
	nod** vector;
	int dim;
};

HashTable initializareHashTable(int dimensiune)
{
	HashTable hash;
	hash.dim = dimensiune;
	hash.vector = (nod**)malloc(sizeof(nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++)
	{
		hash.vector[i] = NULL;
	}

	return hash;
}

Galerie initGalerie(int cod, const char* nume, float pret)
{
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(g.nume, nume);
	g.pretIntrare = pret;
	return g;
}

int calculHash(int cod, const char* nume, int dimensiune)
{
	// hashtable unic - sa fie diferit fata de ceilalti parametri
		
	if (dimensiune > 0)
	{
		int rez = cod * strlen(nume);
		/*
			6*8 = 54
			interval HashTable [0,n)
			modulo dimensiune -> [0,4]
		*/
		return rez % dimensiune;
	}
	return -1;
}

void inserareLaFinal(nod** cap, Galerie galerie)
{
	nod* temp = (nod*)malloc(sizeof(nod));
	temp->info = galerie;
	temp->next = NULL;

	if (*cap)
	{
		nod* aux = *cap;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = temp;
	}

	else
	{
		*cap = temp;
	}
}

//inserarea unei galerii

void inserareGalerieInTabela(HashTable hash, Galerie galerie)
{
	if (hash.dim > 0)
	{
		int pozitie = calculHash(galerie.cod, galerie.nume, hash.dim);
		if (hash.vector[pozitie]!=NULL)
		{
			//situatia de confliziune

			inserareLaFinal(&(hash.vector[pozitie]), galerie);
		}

		else
		{
			inserareLaFinal(&(hash.vector[pozitie]), galerie);
		}
	}
}


void main()
{
	Galerie g1 = initGalerie(1, "Orizont", 10);
	Galerie g2 = initGalerie(2, "Cercul armatei", 6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 20);
	Galerie g5 = initGalerie(5, "Istorie", 15);
	Galerie g6 = initGalerie(6, "Geologie", 17);

	int c1 = calculHash(1, "Orizont", 10);
	printf("%d", c1);

	HashTable tabela = initializareHashTable(5);

}