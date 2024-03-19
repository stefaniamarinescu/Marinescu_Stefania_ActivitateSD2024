#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca
{
	char* nume;
	int nrCarti;
	int nrCititori;
};

struct Nod
{
	Biblioteca info;
	Nod* next;
};

Biblioteca initializare(char* nume, int nrCarti, int nrCititori)
{
	Biblioteca b;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrCititori = nrCititori;
	return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	nou->next = cap;
	return nou;
}

void afisareLista(Nod* cap)
{
	while (cap!= NULL)
	{
		printf("Biblioteca %s are %d carti si %d cititori.\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
		//procesare
		cap = cap->next;
	}
}

char* getBibliotecaNrCartiPerCititor(Nod* cap)
{
	float max = 0;
	char* nume_aux = NULL;

	while (cap)
	{
		if (cap->info.nrCarti / cap->info.nrCititori > max)
		{
			max = cap->info.nrCarti / cap->info.nrCititori;
			nume_aux = cap->info.nume;
		}

		cap = cap->next;
	}

	char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
	strcpy(nume, nume_aux);

		return nume;
}

void inserareLaSfarsit(Nod** cap, Biblioteca b)
{
	Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
	sfarsit->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	sfarsit->next = NULL;

	if ((*cap) != NULL)
	{
		Nod* capA = (*cap);
		while (capA->next!=NULL)
		{
			capA = capA->next;
		}
		capA->next = sfarsit;
	}

	else
	{
		*cap = sfarsit;
	}
}

void stergeLista(Nod** cap)
{
	while (*cap!=NULL)
	{
		free((*cap)->info.nume);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void main()
{
	//lista se identifica dupa adresa primului nod

	Nod* cap = NULL;
	Biblioteca b1 = initializare("Ion Creanga", 200, 30);
	cap = inserareInceput(cap, b1);

	Biblioteca b2 = initializare("Tudor Arghezi", 300, 57);
	cap = inserareInceput(cap, b2);

	Biblioteca b3 = initializare("Ioan Slavici", 355, 100);
	cap = inserareInceput(cap, b3);


	afisareLista(cap);

	printf("Biblioteca cu media maxima: %s.\n", getBibliotecaNrCartiPerCititor(cap));
	Biblioteca b4 = initializare("Stefania Marinescu", 189, 10);

	inserareLaSfarsit(&cap, b4);
	afisareLista(cap);

	stergeLista(&cap);
	afisareLista(cap);
}