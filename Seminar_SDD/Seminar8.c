#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//heap ul spune unde se afla valoarea maxima sau valoarea minima. Nu va sorta toate elementele
//doua tipuri: min heap (aduce minimul pe prima pozitie) si max heap (analog)
//S -> 2*i + 1
//D -> 2*i + 2
//heapsort = 

typedef struct Mesaj Mesaj;
typedef struct Heap Heap;

struct Mesaj
{
	char* text;
	int prioritate;
};

struct Heap
{
	Mesaj* vector;
	int dimensiune;
	int dimensiuneTotala;
};

Mesaj init(const char* text, int prioritate)
{
	Mesaj m;
	m.text = malloc(sizeof(char) * (1 + strlen(text)));
	strcpy(m.text, text);
	m.prioritate = prioritate;
	return m;
}

Heap initHeap(int dimensiune)
{
	Heap h;
	h.vector = malloc(sizeof(Mesaj) * dimensiune);
	h.dimensiune = 0;
	h.dimensiuneTotala = dimensiune;
	return h;
}

void afisareMesaj(Mesaj m)
{
	printf("Mesajul cu textul %s si prioritatea %d\n", m.text, m.prioritate);
}

void afisareHeap(Heap h)
{
	for (int i = 0; i < h.dimensiune; i++)
	{
		afisareMesaj(h.vector[i]);
	}
}

void filtrareHeap(Heap h, int poz)
{
	int poz_s = poz * 2 + 1;
	int poz_d = poz * 2 + 2;
	int poz_m = poz;

	if (poz_s<h.dimensiune && h.vector[poz_s].prioritate>h.vector[poz_m].prioritate)
	{
		poz_m = poz_s;
	}

	if (poz_d<h.dimensiune && h.vector[poz_d].prioritate>h.vector[poz_m].prioritate)
	{
		poz_m = poz_d;
	}

	if (poz_m != poz)
	{
		Mesaj aux = h.vector[poz];
		h.vector[poz] = h.vector[poz_m];
		h.vector[poz_m] = aux;
		if (poz_m * 2 + 1 < h.dimensiune)
		{
			filtrareHeap(h, poz_m);
		}
	}

}

Mesaj extragereHeap(Heap* h)
{
	if (h->dimensiune > 0) //daca am elemente
	{
		Mesaj aux = h->vector[0];
		h->vector[0] = h->vector[h->dimensiune];
		h->vector[h->dimensiune] = aux;
		h->dimensiune--;
		
		for (int i = h->dimensiune / 2; i >= 0; i--)
		{
			filtrareHeap(*h, i);
		}

		return aux;
	}
}

void afisareHeapTotala(Heap h)
{
	for (int i = 0; i < h.dimensiuneTotala; i++)
	{
		afisareMesaj(h.vector[i]);
	}
}

void dezalocareHeap(Heap* h)
{
	if (h->vector != NULL)
	{
		while(h->dimensiuneTotala >= 0)
		{
			free(h->vector[h->dimensiuneTotala].text);
			h->dimensiuneTotala--;
		}

		free(h->vector);
		h->vector = NULL;
		h->dimensiune = 0;
	}
}

void main()
{
	Heap h;
	h = initHeap(6);
	h.vector[0] = init("Salut", 3);
	h.vector[1] = init("Salut, ce faci", 8);
	h.vector[2] = init("Buna", 6);
	h.vector[3] = init("Noroc", 2);
	h.vector[4] = init("Ce mai faci", 9);
	h.vector[5] = init("Pa-pa", 4);
	h.dimensiune = 6;

	afisareHeap(h);
	printf("Dupa filtrare\n");

	for (int i = (h.dimensiune / 2)-1; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}

	printf("Dupa extragere\n");

	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));

	printf("Heap total\n");
	afisareHeapTotala(h);
	dezalocareHeap(&h);

}