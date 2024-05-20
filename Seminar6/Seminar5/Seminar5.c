#include<stdio.h>
#include<malloc.h>

//liste simplu inlantuite,sturct de date ca fiecare nod retine adresa urmatorului nod si sunt contigue

typedef struct CafeneaMea Cafenea;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct CafeneaMea {
	char* nume;
	int nrLocuri;
	float suprafata;
};
//info utila si adresa urmatorului nod
struct Nod {
	Cafenea cafenea;
	Nod* anterior;
	Nod* ulterior;
};
struct ListaDubla {
	Nod* cap;
	Nod* coada;
};

void inserareInceput(ListaDubla* lista, Cafenea cafenea) {
	Nod* nou = malloc(sizeof(Nod));
	nou->anterior = NULL;
	nou->cafenea = cafenea;
	nou->ulterior = lista->cap;
	if (lista->cap != NULL)
	{
		lista->cap->anterior = nou;
	}
	else
	{
		lista->coada = nou;
	}
	lista->cap = nou;


}

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
	Cafenea cafenea;
	cafenea.nrLocuri = nrLocuri;
	cafenea.suprafata = suprafata;
	cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(cafenea.nume, nume);

	return cafenea;
}

void afisareCafenea(Cafenea c) {
	printf("Numele Cafenelei: %s\n", c.nume);
	printf("Numar de locuri ale Cafenelei: %d\n", c.nrLocuri);
	printf("Suprafata Cafenelei: %2.2f\n", c.suprafata);
}

void afisareListaCafenele(ListaDubla lista) {
	Nod* nod = lista.cap;
	while (nod)
	{

		afisareCafenea(nod->cafenea);
		nod = nod->ulterior;
	}
	printf("\n\n");
}


//stergere lista

ListaDubla stergeCafeneaDupaNume(ListaDubla lista, const char* nume) {
	if (nume == NULL)
	{
		return lista;
	}
	Nod* nod = lista.cap;
	while (nod && strcmp(nod->cafenea.nume, nume) != 0)
	{
		nod = nod->ulterior;
	}
	if (nod != NULL)
	{
		if (nod->ulterior == NULL && nod->anterior == NULL)
		{
			lista.cap = NULL;
			lista.coada == NULL;
		}
		else
		{
			if (nod->anterior == NULL)
			{
				lista.cap = nod->ulterior;
				lista.cap->anterior = NULL;
			}
			else if (nod->ulterior == NULL)
			{
				lista.coada = nod->anterior;
				lista.coada->ulterior = NULL;
			}
			else {
				nod->anterior->ulterior = nod->ulterior;
				nod->ulterior->anterior = nod->anterior;
			}
		}

		free(nod->cafenea.nume);
		free(nod);
	}
	return(lista);
}


ListaDubla stergereLista(ListaDubla listaDubla)
{

	while (listaDubla.cap != NULL)
	{
		free(listaDubla.cap->cafenea.nume);
		Nod* temp = listaDubla.cap;
		listaDubla.cap = listaDubla.cap->ulterior;
		free(temp);
	}
	listaDubla.cap = NULL;
	listaDubla.coada = NULL;
	return(listaDubla);
}

//parcurgere inversa
int NrTotalLocuri(ListaDubla lista)
{
	if (lista.cap == NULL)
	{
		return 0;
	}

	int nrLocuri = 0;
	Nod* nod = lista.coada;

	while (nod != NULL)
	{
		nrLocuri += nod->cafenea.nrLocuri;
		nod = nod->anterior;
	}

	return nrLocuri;

}

void main() {
	Nod* cap = NULL;
	Cafenea cafenea = initializareCafenea("Tucano", 12, 20);
	Cafenea cafenea1 = initializareCafenea("Teds", 17, 17.3);
	Cafenea cafenea2 = initializareCafenea("Starbucks", 19, 33);
	Cafenea cafenea3 = initializareCafenea("Urban", 20, 33);

	ListaDubla listaDubla;
	listaDubla.coada = NULL;
	listaDubla.cap = NULL;
	inserareInceput(&listaDubla, cafenea);
	inserareInceput(&listaDubla, cafenea1);
	inserareInceput(&listaDubla, cafenea2);
	inserareInceput(&listaDubla, cafenea3);

	afisareListaCafenele(listaDubla);

	//printf("STERGERE\n");
	//listaDubla = stergeCafeneaDupaNume(listaDubla, "Teds");
	//afisareListaCafenele(listaDubla);
	//printf("STERGERE\n");

	//listaDubla = stergeCafeneaDupaNume(listaDubla, "Urban");
	//afisareListaCafenele(listaDubla);
	//printf("STERGERE\n");

	//listaDubla = stergeCafeneaDupaNume(listaDubla, "Tucano");
	//afisareListaCafenele(listaDubla);
	//printf("STERGERE\n");

	//listaDubla = stergeCafeneaDupaNume(listaDubla, "Ceva");
	//afisareListaCafenele(listaDubla);

	//listaDubla = stergereLista(listaDubla);
	printf("\nNr locuri total: %d ",NrTotalLocuri(listaDubla));

	//afisareListaCafenele(listaDubla);





}