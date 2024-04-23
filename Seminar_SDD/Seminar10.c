#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Elev Elev;
typedef struct Nod Nod;

// arbore binar = graf conex aciclic cu maxim doi descendenti
// arbore binar de cautare = folositi pentru cautari mult mai rapide. In stanga trebuie sa fie mai mic decat in dreapta
//stanga mai mic decat radacina, dreapta mai mare decat radacina

struct Elev
{
	int id;
	int nrMedii;
	float* medii;

};

struct Nod
{
	Elev info;
	Nod* stanga;
	Nod* dreapta;
};

void inserareArbore(Nod** radacina, Elev e)
{
	if ((*radacina) != NULL)
	{
		if ((*radacina)->info.id > e.id)
		{
			inserareArbore(&((*radacina)->stanga), e);
		}
		else
		{
			inserareArbore(&((*radacina)->dreapta), e);
		}
	}

	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->stanga = NULL;
		nod->dreapta = NULL; //nod frunza
		*radacina = nod;
	}
}

Elev citireElev(FILE* fp)
{
	Elev e;
	fscanf(fp, "%d", &e.id);
	fscanf(fp, "%d", &e.nrMedii);
	e.medii = malloc(sizeof(float) * e.nrMedii);
	
	for (int i = 0; i < e.nrMedii; i++)
	{
		fscanf(fp, "%f", &(e.medii[i]));
	}
	return e;
}

Nod* citireFisier(char *numeFisier)
{
	Nod* arbore = NULL;

	if (!numeFisier)
	{
		return NULL;
	}

	else
	{
		FILE* fp = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(fp, "%d", &nrElevi);

		for (int i = 0; i < nrElevi; i++)
		{
			Elev e = citireElev(fp);
			inserareArbore(&(*arbore), e);
		}

		fclose(fp);
	}

	return arbore;
}

/*
	SRD = in ordine;
	RSD = in preordine;
	SDR = in postordine;
*/

void afisareElev(Elev e)
{
	printf("Elevul cu id-ul %i are %i medii, acestea fiind %.2f .\n", e.id, e.nrMedii, e.medii);
}

void afisareInOrder(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareInOrder(arbore->stanga);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dreapta);
	}
}

float calculeazaMedieElev(Elev e)
{
	float suma = 0;
	if (e.nrMedii != 0)
	{
		;
		for (int i = 0; i < e.nrMedii; i++)
		{
			suma += e.medii[i];
		}
	}

	return suma / e.nrMedii;
}

float calculeazaSumaNote(Nod* arbore, int* nrNote)
{
	if (arbore != NULL)
	{
		float suma = 0;
		for (int i = 0; i < arbore->info.nrMedii; i++)
		{
			suma += arbore->info.medii[i];
		}

		float sumaStanga = calculeazaSumaNote(arbore->stanga, nrNote);
		float sumaDreapta = calculeazaSumaNote(arbore->dreapta, nrNote);

		(*nrNote) += arbore->info.nrMedii;

		return suma + sumaStanga + sumaDreapta;
	}

	else
		return 0;
}

float calculeazaMedieGenerala(Nod* arbore, int* nrNote)
{
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	printf("\n\n%d", nrNote);

	if (nrNote > 0)
		return suma / nrNote;

	else return 0;
}

void main()
{
	Nod* arbore = citireFisier("elevi.txt");

	afisareInOrder(arbore);

	printf("Media este: %.2f", calculeazaMedieGenerala(arbore));
}