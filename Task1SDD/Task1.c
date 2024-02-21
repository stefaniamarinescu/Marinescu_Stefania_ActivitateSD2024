#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct Simigerie
{
	char* nume;
	int nrProduse;
	float* preturiProduse;

};


void citireSimigerie(struct Simigerie *simigerie)
{
	simigerie->nume = (char*)malloc(100 * sizeof(char));

	printf("Introduceti numele simigeriei: \n");

		scanf("%s", simigerie->nume);

	printf("Introduceti numarul de produse disponibile: \n");

		scanf("%d", &(simigerie->nrProduse));

	simigerie->preturiProduse = (float*)malloc(simigerie->nrProduse * sizeof(float));

	printf("Introduceti preturile produselor: \n");

		for (int i = 0; i < simigerie->nrProduse; i++)
		{
			scanf("%f", &(simigerie->preturiProduse[i]));
		}
	
	return simigerie;
}


void afisareSimigerie(struct Simigerie* s)
{
	if (s->nume != NULL)
	{

		printf("Nume: %s\n", s->nume);

	}
	printf("Numar produse: %d\n", s->nrProduse);

	if (s->preturiProduse != NULL)
	{
		for(int i=0;i<s->nrProduse;i++)

		printf("Pretul produsului %d: este %.2f\n", i+1, s->preturiProduse[i]);

	}

}


void dezalocareSimigerie(struct Simigerie* s)
{
	free(s->nume);
	s->nume = NULL;
	free(s->preturiProduse);
	s->preturiProduse = NULL;
}

float mediePreturi(struct Simigerie* s)
{
	int suma = 0;

	for (int i = 0; i < s->nrProduse; i++)
		suma += s->preturiProduse[i];

	return suma / s->nrProduse;
}

void main()
{
	struct Simigerie simigerie1;
	citireSimigerie(&simigerie1);
	afisareSimigerie(&simigerie1);

	printf("Media preturilor produselor este: %.2f", mediePreturi(&simigerie1));

	dezalocareSimigerie(&simigerie1);
}