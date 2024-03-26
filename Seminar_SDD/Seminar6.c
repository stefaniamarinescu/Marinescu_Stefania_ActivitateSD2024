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
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;

struct ListaDubla
{
	Nod* head;
	Nod* tail;
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

void inserareLaInceput(ListaDubla* listaDubla, Biblioteca b)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = b;
	nod->next = listaDubla->head;
	nod->prev = NULL;
	if(listaDubla->head)
	{
		listaDubla->head->prev = nod;
	}
	else
	{
		listaDubla->head = nod;
		listaDubla->tail = nod;
	}
	listaDubla->head = nod;
}

void afisareListaInceput(ListaDubla listaDubla)
{
	while (listaDubla.head)
	{
		printf("Biblioteca: %s; \nNumar cititori: %d;\nNumar carti: %d.\n\n", listaDubla.head->info.nume,
			listaDubla.head->info.nrCititori, listaDubla.head->info.nrCarti);
		listaDubla.head = listaDubla.head->next;
	}
}

void stergereNodNume(ListaDubla* listaDubla, const char* nume)
{
	Nod* aux = listaDubla->head;
	while (aux && strcmp(nume, aux->info.nume)!=0)
	{
		aux = aux->next;
	}

	if (aux)
	{
		if (aux==listaDubla->head)
		{
			if (aux == listaDubla->tail)
			{
				listaDubla->head = NULL;
				listaDubla->tail = NULL;
			}
			else
			{
				listaDubla->head = listaDubla->head->next;
				listaDubla->head->prev = NULL;
			}
		}
		else
		{
			if (aux==listaDubla->tail)
			{
				aux->prev->next = NULL;
				listaDubla->tail = aux->prev;
			}
			else
			{
				aux->next->prev = aux->prev->next;
				aux->prev->next = aux->next;
			}
		}
		free(aux->info.nume);
		free(aux);
	}
}

void stergereLista(ListaDubla* listaDubla)
{
	while (listaDubla->head)
	{
		free(listaDubla->head->info.nume);
		Nod* aux = listaDubla->head;
		listaDubla->head = listaDubla->head->next;
		free(aux);
	}

	listaDubla->head = NULL;
	listaDubla->tail = NULL;
}

int nrCartiTotal(ListaDubla listaDubla)
{
	int rezultat = 0;
	while (listaDubla.tail)
	{
		rezultat += listaDubla.tail->info.nrCarti;
		listaDubla.tail = listaDubla.tail->prev;

	}

	return rezultat;
}

void main()
{
	//lista se identifica dupa adresa primului nod

	Biblioteca b1 = initializare("Ion Creanga", 200, 30);

	Biblioteca b2 = initializare("Tudor Arghezi", 300, 57);
	
	Biblioteca b3 = initializare("Ioan Slavici", 355, 100);

	ListaDubla listaDubla; //aici a fost creat un obiect

	listaDubla.head = NULL;
	listaDubla.tail = NULL;

	inserareLaInceput(&listaDubla, b1);
	inserareLaInceput(&listaDubla, b2);
	inserareLaInceput(&listaDubla, b3);

	afisareListaInceput(listaDubla);

	int rezultat = nrCartiTotal(listaDubla);

	printf("\nNumarul total de carti: %d\n\n\n", rezultat);

	stergereNodNume(&listaDubla, "Tudor Arghezi");

	afisareListaInceput(listaDubla);
	stergereNodNume(&listaDubla, "Ioan Slavici");

	afisareListaInceput(listaDubla);

	stergereLista(&listaDubla);
	afisareListaInceput(listaDubla);


}