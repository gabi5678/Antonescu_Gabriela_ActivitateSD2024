#include<stdio.h>
#include<malloc.h>

struct Avion {
	int nrPasageri;
	char* companie;
	float pretBilet;
};

struct Avion initializareAvion(int nrPasageri, const char* companie, float pretBilet) {
	struct Avion avion;
	avion.nrPasageri = nrPasageri;
	avion.companie = (char*)malloc(sizeof(char) * (strlen(companie) + 1));
	strcpy(avion.companie, companie);
	avion.pretBilet = pretBilet;

	return avion;
}
//vector structura de date omogena liniara 

void afisareAvion(struct Avion avion)
{
	printf("%s are un avion de %d locuri cu pretul de %5.2f RON pe loc\n", avion.companie, avion.nrPasageri, avion.pretBilet);
}

void afisareVectorAvioane(struct Avion* vector, int nrAvioane) {
	if (vector != NULL) {
		for (int i = 0; i < nrAvioane; i++)
		{
			afisareAvion(vector[i]);
		}
	}
}

//facem o fucntie care copiaza primele n avioane din vector
struct Avion* copiazaPrimeleAvioane(struct Avion* avioane, int nrAvioane, int nrAvioaneCopiate)
{
	if (nrAvioaneCopiate < nrAvioane && nrAvioaneCopiate>0)
	{
		struct Avion* avioaneCopiate = (struct Avion*)malloc(sizeof(struct Avion)*nrAvioaneCopiate);
		for (int i = 0; i < nrAvioaneCopiate; i++)
		{
			avioaneCopiate[i] = initializareAvion(avioane[i].nrPasageri, avioane[i].companie, avioane[i].pretBilet); //mi se va crea un deep copy pentru ca daca faceam doar avion[i] era shallow copy
		}

		return avioaneCopiate;
	}
	else
	{
		return NULL;
	}
}

void dezalocare(struct Avion** avione, int* nrAvione)
{
	if ((*avione) != NULL) {
		for (int i = 0; i < *nrAvione; i++)
		{
			free((*avione)[i].companie);
		}
		free(*avione);
		*nrAvione = 0;
		*avione = NULL;
	}
}

void copiazaAvioaneCuBileteReduse(struct Avion* avioane, int nrAvioane, float pragPret, struct Avion** avioaneNou, int* dimensiune) //transmitem un vector prin adresa la Avion** avioaneNou
{
	*dimensiune = 0;
	for (int i = 0; i < nrAvioane; i++)
	{
		if (avioane[i].pretBilet < pragPret)
		{
			(*dimensiune)++;

		}
		if (*avioaneNou != NULL)
		{
			dezalocare(avioaneNou, dimensiune);
		}
		else {
			*dimensiune = 0;
		}

		for (int i = 0; i < nrAvioane; i++)
		{
			if (avioane[i].pretBilet < pragPret)
			{
				(*dimensiune)++;
				
			}
		}


	}

	*avioaneNou = (struct Avion*)malloc(sizeof(struct Avion) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrAvioane; i++)
	{
		if (avioane[i].pretBilet < pragPret)
		{
			(*avioaneNou)[k++] = initializareAvion(avioane[i].nrPasageri, avioane[i].companie, avioane[i].pretBilet);
		}
	}

}


struct Avion getPrimulAvionDupaCompanie(struct Avion* avioane, int nrAvioane, const char* companie)
{
	if (avioane != NULL && companie != NULL) {
		for (int i = 0; i < nrAvioane; i++) {
			if (avioane[i].companie != NULL) {
				if (strcmp(avioane[i].companie, companie) == 0)
				{
					//return avioane[i]; //shallow copy
					return initializareAvion(avioane[i].nrPasageri, avioane[i].companie, avioane[i].pretBilet);
				}
			}

		}

	}
		return initializareAvion(-1, "N/A", -1);
}

void main()
{
	//int v[10]; //este alocata in stack, 40 bytes (Si daca aveam v[20] tot 40 bytes aloca) si de aia e bine sa facem alocare dinamica
	int nrAvioane = 5;
	struct Avion* avioane = (struct Avion*)malloc(sizeof(struct Avion) * nrAvioane);
	for (int i = 0; i < nrAvioane; i++)
	{
		avioane[i] = initializareAvion(i + 50, "Tarom", 10 * i + 40);
	}

	afisareVectorAvioane(avioane, nrAvioane);

	int nrAvioaneCopiate = 4;
	struct Avion* avioaneCopiate = copiazaPrimeleAvioane(avioane, nrAvioane, nrAvioaneCopiate);

	printf("\n\n");

	afisareVectorAvioane(avioaneCopiate, nrAvioaneCopiate);

	struct Avion* avioaneCuBileteReduse = NULL;
	int nrAvioaneCuBileteReduse = 0;

	avioane[4].pretBilet = 30;
	copiazaAvioaneCuBileteReduse(avioane, nrAvioane, 60, &avioaneCuBileteReduse, &nrAvioaneCuBileteReduse);


	printf("\n\n");

	afisareVectorAvioane(avioaneCuBileteReduse, nrAvioaneCuBileteReduse);

	struct Avion avion = getPrimulAvionDupaCompanie(avioane, nrAvioane, "Tarom");
	printf("\n\nAvion cautat: ");
	afisareAvion(avion);

	//cream probleme ca sa intelegem
	dezalocare(&avioane, &nrAvioane); //imi sterge
	dezalocare(&avioaneCopiate, &nrAvioaneCopiate); //imi sterge
	dezalocare(&avioaneCuBileteReduse, &nrAvioaneCuBileteReduse); //imi sterge
	free(avion.companie); //aici crapa

	//am facut la getPrimulAvionDupaCompanie shallow copy prin return deci a trebui sa facem deep copy

}