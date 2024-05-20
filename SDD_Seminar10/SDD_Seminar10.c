#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;
struct Cinema {
	int id;
	int nrFilme;
	char** listaFilme;
};

struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina, Cinema c)
{
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else {
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		*radacina = nod;
	}
}

Cinema citireCinema(FILE* file) {
	Cinema c;
	fscanf(file, "%d", &c.id);
	fscanf(file, "%d", &c.nrFilme);
	if (c.nrFilme != 0)
	{
		c.listaFilme = (char**)malloc(sizeof(char*) * c.nrFilme);
		for (int i = 0; i < c.nrFilme; i++)
		{
			char buffer[100];
			fscanf(file, "%s", buffer);
			c.listaFilme[i] = malloc((sizeof(char) * (1 + strlen(buffer))));
			strcpy(c.listaFilme[i], buffer);
		}
	}
	else {
		c.listaFilme = NULL;
	}

	return c;

}

Nod* citireDinFisier(const char* numeFisier) {
	Nod* radacina = NULL;
	if (numeFisier != NULL && strlen(numeFisier) > 0)
	{
		FILE* file = fopen(numeFisier, "r");
		if (file != NULL) {
			int dim = 0;
			fscanf(file, "%d", &dim);
			for (int i = 0; i < dim; i++) {
				Cinema c;
				c = citireCinema(file);
				inserareInArbore(&radacina, c);
			}
		}
	}
	return radacina;
}

void afisareCinema(Cinema c) {
	printf("Cinematograful cu id-ul %d are in derulare %d filmele: ", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++) {
		printf("%s ", c.listaFilme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* rad) {
	if (rad) {
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInordine(Nod* rad) {
	if (rad) {
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

int calculNrFilmeRedate(Nod* rad) {
	if (rad) {
		int suma = rad->info.nrFilme;
		suma += calculNrFilmeRedate(rad->st);
		suma += calculNrFilmeRedate(rad->dr);
		return suma;
	}
	else {
		return 0;
	}
}


void main()
{
	Nod* arbore = NULL;
	arbore = citireDinFisier("cinema.txt");
	//inordine-SRD
	//preordine-RSD (daca radacina e in fata inseamna ca e pre) r->procesez informatia din nod, s->procesez infromatia din subarborele stang,
	//postordine-SDR
	afisareArborePreordine(arbore);
	printf("\n\n");
	afisareArboreInordine(arbore);
	printf("\n\n");
	printf("\n\nNumar filme: %d", calculNrFilmeRedate(arbore));


}