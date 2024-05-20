#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//min-heap
typedef struct Quiz Quiz;
typedef struct Heap Heap;
struct Quiz {
	char* materie;
	int grileGresite;
};

struct Heap {
	Quiz* vector;
	int dimensiune;
	//pentru sortare vom avea 2 dim (pt elementele ascunse)
	int dimensiuneTotala;
};

Heap initializareHeap(int nr)
{
	Heap heap;
	heap.vector = malloc(nr * sizeof(Quiz));
	heap.dimensiuneTotala = nr;
	heap.dimensiune = 0;
	return heap;
}

Quiz initializareQuiz(const char* materie, int grileGresite)
{
	Quiz quiz;
	quiz.materie = (char*)malloc(strlen(materie) + 1);
	strcpy(quiz.materie, materie);
	quiz.grileGresite = grileGresite;

	return quiz;
}


Heap adaugareQuizInHeap(Quiz quiz,Heap heap)
{
	if (heap.dimensiune < heap.dimensiuneTotala)
	{
		heap.vector[heap.dimensiune] = quiz;
		heap.dimensiune++;
		//TO DO filtrare
	}
	return heap;
}

void afisareQuiz(Quiz quiz)
{
	printf("Materie:%s", quiz.materie);
	printf(" Grile Gresite:%d\n\n", quiz.grileGresite);
}

void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.dimensiune; i++)
	{
		afisareQuiz(heap.vector[i]);
	}
}

void filtreazaHeap(Heap heap, int pozRadacina)
{
	int nodSt = pozRadacina * 2 + 1;
	int nodDr = pozRadacina * 2 + 1;
	int pozMin = pozRadacina;
	if ((nodSt < heap.dimensiune) && (heap.vector[nodSt].grileGresite < heap.vector[pozMin].grileGresite)) {
		//exista nodul si este mai mic decat radacina
		pozMin = nodSt;

	}

	if ((nodDr < heap.dimensiune) && (heap.vector[nodDr].grileGresite < heap.vector[pozMin].grileGresite)) {
		pozMin = nodDr;
	}

	if (pozMin != pozRadacina)
	{
		Quiz aux;
		aux = heap.vector[pozRadacina];
		heap.vector[pozMin] = heap.vector[pozRadacina];
		heap.vector[pozMin] = aux;
		if (pozMin * 2 + 1 < heap.dimensiune - 1)
			filtreazaHeap(heap, pozMin);
	}

}

Quiz extragereRadacinaMinima(Heap* heap) {
	if (heap->dimensiune > 0)
	{
		Quiz aux;
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dimensiune - 1];
		heap->vector[heap->dimensiune - 1] = aux;
		heap->dimensiune--;
		for (int i = (heap->dimensiune) / 2 - 1; i >= 0; i--)
		{
			filtreazaHeap(*heap, i);
		}
		return aux;
	}
	else {
		return initializareQuiz("N\A", -1);
	}


}

void dezalocareTotHeap(Heap* heap)
{
	for (int i = 0; i < (*heap).dimensiune; i++)
	{
		free(heap->vector[i].materie);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->dimensiune = 0;
	heap->dimensiuneTotala = 0;
}

void main()
{
	Heap heap;
	heap = initializareHeap(6);
	heap.dimensiune = 6;
	heap.vector[0] = initializareQuiz("Structuri de date", 3);
	heap.vector[1] = initializareQuiz("Java", 7);
	heap.vector[2] = initializareQuiz("PEAG", 5);
	heap.vector[3] = initializareQuiz("PAW", 2);
	heap.vector[4] = initializareQuiz("Macroeconomie", 9);
	heap.vector[5] = initializareQuiz("POO", 4);
	afisareHeap(heap);

	//facem pt toti parintii si apelam de jos in sus
	for (int i= (heap.dimensiune)/2-1; i>=0;i--)
	{
		filtreazaHeap(heap, i);
	}

	afisareHeap(heap);

	afisareQuiz((extragereRadacinaMinima(&heap)));
	afisareQuiz((extragereRadacinaMinima(&heap)));
	printf("\n\n\n");
	afisareHeap(heap);

}
