#include "functii.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
	FILE* fisiercerinte;
	fisiercerinte = fopen(argv[1], "r");
	int vectorcerinte[5];
	for (int i = 0; i < 5; i++)
		fscanf(fisiercerinte, "%d", &vectorcerinte[i]);
	fclose(fisiercerinte);
	int nrechipe;
	FILE* fisier;
	Node* echipe = NULL;
	fisier = fopen(argv[2], "r");
	fscanf(fisier, "%d", &nrechipe);
	fgetc(fisier);
	FILE* fisierafisare = fopen(argv[3], "wt");
	int sumacerinte = 0;
	for (int i = 0; i < 5; i++)
		sumacerinte = sumacerinte + vectorcerinte[i];
	// citire lista echipelor
	for (int i = 0; i < nrechipe; i++) {
		Node* echipa_noua = malloc(sizeof(Node));
		echipa_noua->next = NULL;
		fscanf(fisier, "%d", &echipa_noua->nrjucatori);
		fgetc(fisier);
		echipa_noua->nume_echipa = malloc(60 * sizeof(char));
		fgets(echipa_noua->nume_echipa, 60, fisier);
		echipa_noua->nume_echipa[strcspn(echipa_noua->nume_echipa, "\n")] = '\0';
		if (echipa_noua->nume_echipa[strlen(echipa_noua->nume_echipa) - 2] == ' ')
			echipa_noua->nume_echipa[strlen(echipa_noua->nume_echipa) - 2] = '\0';
		else
			echipa_noua->nume_echipa[strlen(echipa_noua->nume_echipa) - 1] = '\0';
		echipa_noua->jucator = malloc(echipa_noua->nrjucatori * sizeof(Player));
		for (int j = 0; j < echipa_noua->nrjucatori; j++) {
			echipa_noua->jucator[j].firstName = malloc(60 * sizeof(char));
			echipa_noua->jucator[j].secondName = malloc(60 * sizeof(char));
			fscanf(fisier, "%s %s %d", echipa_noua->jucator[j].firstName,
						 echipa_noua->jucator[j].secondName,
						 &echipa_noua->jucator[j].points);
		}
		if (echipe == NULL) {
			echipe = echipa_noua;
		} else {
			addAtStart(&echipe, echipa_noua);
		}
	}
	fclose(fisier);
	if (vectorcerinte[0] == 1 && sumacerinte == 1) {
		Node* current = echipe;
		while (current != NULL) {
			fprintf(fisierafisare, "%s\n", current->nume_echipa);
			current = current->next;
		}
	}
	// task 2
	float* vectorpuncte = malloc(sizeof(float) * nrechipe);
	if (vectorcerinte[1] == 1) {
		int n = 1;
		while (pow(2, n + 1) <= nrechipe)
			n++;
		int N = pow(2, n);
		Node* current_echipa = echipe;
		for (int i = 0; i < nrechipe; i++) {
			vectorpuncte[i] = calculpunctajechipa(current_echipa);
			current_echipa = current_echipa->next;
		}
		while (nrechipe != N) {
			int indiceMin = calculpunctajminim(vectorpuncte, nrechipe);
			stergerenod(&echipe, indiceMin);
			stergereelementvector(vectorpuncte, nrechipe, indiceMin);
			nrechipe--;
		}
		Node* current = echipe;
		while (current != NULL) {
			fprintf(fisierafisare, "%s\n", current->nume_echipa);
			current = current->next;
		}
	}
	// task 3
	if (vectorcerinte[2] == 1) {
		Node* current = echipe;
		coada* q;
		q = (coada*)malloc(sizeof(coada));
		q->front = NULL;
		q->rear = NULL;
		for (int i = 0; i < nrechipe; i++) {
			enQueue(q, current->nume_echipa);
			current = current->next;
		}
		int nrechipe2 = nrechipe;
		stiva* invinsi = NULL;
		stiva* castigatori = NULL;
		int nr = 0;
		while (nrechipe2 != 1) {
			nr++;
			float* vectorpuncte2 = malloc(sizeof(float) * nrechipe2);
			for (int i = 0; i < nrechipe2; i++) {
				vectorpuncte2[i] = vectorpuncte[i];
			}
			current = q->front;
			fprintf(fisierafisare, "\n--- ROUND NO:%d\n", nr);
			Node* current2 = q->front;
			while (current2 != NULL) {
				fprintf(fisierafisare, "%-33s-%33s\n", current2->nume_echipa, current2->next->nume_echipa);
				current2 = current2->next->next;
			}
			int i = 0, j = 0;
			// verific care echipa a pierdut
			for (int i = 0; i < nrechipe2; i += 2) {
				if (vectorpuncte2[i] > vectorpuncte2[i + 1]) { // adaug echipa castigatoare in stiva de castigatori si pe cea care a pierdut in cea de invinsi
					push(&castigatori, current->nume_echipa);
					current = current->next;
					push(&invinsi, current->nume_echipa);
					current = current->next;
					vectorpuncte[j]++;
					stergereelementvector(vectorpuncte, nrechipe2, j + 1);
				} else {
					push(&invinsi, current->nume_echipa);
					current = current->next;
					push(&castigatori, current->nume_echipa);
					current = current->next;
					vectorpuncte[j + 1]++;
					stergereelementvector(vectorpuncte, nrechipe2, j);
				}
				j++;
			}
			nrechipe2 = nrechipe2 / 2;
			for (int i = 0; i < nrechipe2 / 2; i++) {
				float temp = vectorpuncte[i];
				vectorpuncte[i] = vectorpuncte[nrechipe2 - i - 1];
				vectorpuncte[nrechipe2 - i - 1] = temp;
			}
			free(vectorpuncte2);
			deleteQueue(q);
			q = (coada*)malloc(sizeof(coada));
			q->front = NULL;
			q->rear = NULL;
			// adaug in coada castigatorii
			fprintf(fisierafisare, "\nWINNERS OF ROUND NO:%d\n", nr);
			stiva* current_castigatori = castigatori;
			for (int i = 0; i < nrechipe2; i++) {
				enQueue(q, current_castigatori->echipa);
				fprintf(fisierafisare, "%-33s -  %.2f\n", current_castigatori->echipa, vectorpuncte[i]);
				current_castigatori = current_castigatori->next;
			}
			// golesc stivele
			deleteStack(&castigatori);
			deleteStack(&invinsi);
		}
	}

	// eliberare memorie
	Node* current_echipa = echipe;
	while (current_echipa != NULL) {
		Node* next_echipa = current_echipa->next;
		free(current_echipa->nume_echipa);
		for (int j = 0; j < current_echipa->nrjucatori; j++) {
			free(current_echipa->jucator[j].firstName);
			free(current_echipa->jucator[j].secondName);
		}
		free(current_echipa->jucator);
		free(current_echipa);
		current_echipa = next_echipa;
	}

	return 0;
}