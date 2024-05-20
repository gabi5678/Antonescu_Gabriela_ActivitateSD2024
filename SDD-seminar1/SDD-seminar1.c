//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Haina { //struct->datele unor obiecte omogene (despre un anumit tip), toate elementele sunt publice, si nu contin metode, constuctori
	int marime;
	char* marca;
	float pret;
	//bool gender; nu exista tip-ul bool
	char gender;
};

struct Haina initializareHaina(int marime, const char* marca, float pret, char gender)
{
	struct Haina h;
	h.marime = marime;
	if (marca != NULL && strlen(marca) > 0) {
		h.marca = malloc(strlen(marca) + 1); //face cast-ul implicit
		strcpy(h.marca, marca);
	}
	else {
		h.marca = NULL;
	}

	h.pret = pret;
	h.gender = gender;

	return h;
}

void afiseazaHaina(struct Haina h)
{
	if (h.marca != NULL) {
		printf("Marca: %s\n", h.marca);
	}
	printf("Marime: %d\n", h.marime);
	printf("Pret: %5.2f\n", h.pret);
	printf("Gen: %c\n\n", h.gender);
}

void dezalocareHaina(struct Haina *h)
{
	free(h->marca);
	h->marca = NULL;
}

void main()
{
	struct Haina haina1;
	haina1.marime = 33;
	haina1.marca = (char*)malloc(sizeof(char) * (strlen("Nike") + 1));
	strcpy(haina1.marca, "Nike");
	haina1.pret = 45;
	haina1.gender = 'M';

	afiseazaHaina(haina1);

	//free(haina1.marca);
	//haina1.marca = NULL;
	dezalocareHaina(&haina1);

	struct Haina haina2 = initializareHaina(27, "Adidas", 23.6, 'F');
	afiseazaHaina(haina2);

	//free(haina2.marca);
	//haina2.marca = NULL;
	//fiind doua free-uri, incalcam principiul dry (don t repet yourself), deci vom lua codul si imi vom face intr-o functie
	//dangling pointer-> pointeaza spre un obiect sters
	
	dezalocareHaina(&haina2);
	afiseazaHaina(haina2);


}




