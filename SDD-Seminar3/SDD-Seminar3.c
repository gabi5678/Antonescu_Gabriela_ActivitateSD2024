#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <stdlib.h>
#include <string>

struct Locuinta {
	int id;
	char* strada;
	int nr;
};

void inserareLocuinta(struct Locuinta** vector, int* dim, struct Locuinta l)
{
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++)
	{
		copie[i] = (*vector)[i];
	}
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL)
	{
		free((*vector));
	}

	(*vector) = copie;
}

void citesteFisier(const char* nume_fisier, struct Locuinta** vector, int* dim)
{
	if (nume_fisier != NULL && strlen(nume_fisier) > 0)
	{
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL)
		{
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL)
			{
				char* token;
				token=strtok(buffer, delimitator);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.nr = atoi(token); //pt float atof
				inserareLocuinta(vector, dim, locuinta);

			}
		}
	}
}


void main()
{
	struct Locuinta* locuinte = NULL;
	int dim = 3;
	citesteFisier("locuinte.txt", &locuinte, &dim);



}