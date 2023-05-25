#include "functii.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addAtStart(Node** head, Node* new_node) {
	new_node->next = *head;
	*head = new_node;
}

float calculpunctajechipa(Node* head) {
	float puncte = 0;
	for (int j = 0; j < head->nrjucatori; j++)
		puncte = puncte + head->jucator[j].points;
	puncte = puncte / head->nrjucatori;
	return puncte;
}

int calculpunctajminim(float* vectorpuncte, int nrechipe) {
	float Min = vectorpuncte[0];
	int indiceMin = 0;
	for (int i = 1; i < nrechipe; i++)
		if (vectorpuncte[i] < Min) {
			Min = vectorpuncte[i];
			indiceMin = i;
		}
	return indiceMin;
}

void stergerenod(Node** head, int indice) {
	Node* current = *head;
	Node* prev = NULL;
	if (indice == 0) {
		*head = (*head)->next;
		free(current);
		return;
	}
	for (int i = 0; current != NULL && i < indice; i++) {
		prev = current;
		current = current->next;
	}
	if (current != NULL) {
		if (prev != NULL)
			prev->next = current->next;
		else
			*head = current->next;
		free(current);
	}
}

void stergereelementvector(float* vector, int size, int indice) {
	for (int i = indice; i < size - 1; i++)
		vector[i] = vector[i + 1];
}

void enQueue(coada* q, char* v) {
	Node* newNode = malloc(sizeof(Node));
	newNode->nume_echipa = malloc((strlen(v) + 1) * sizeof(char));
	strcpy(newNode->nume_echipa, v);
	newNode->next = NULL;

	if (q->rear == NULL)
		q->front = q->rear = newNode;
	else {
		q->rear->next = newNode;
		q->rear = newNode;
	}
}

void push(stiva** top, char* v) {
	stiva* newNode = (stiva*)malloc(sizeof(stiva));
	newNode->echipa = malloc((strlen(v) + 1) * sizeof(char));
	strcpy(newNode->echipa, v);
	newNode->next = *top;
	*top = newNode;
}

int isEmpty(stiva* top) {
	return top == NULL;
}

void deleteStack(stiva** top) {
	stiva* temp;
	while (!isEmpty(*top)) {
		temp = *top;
		*top = (*top)->next;
	}
	free(temp);
}

int isEmptyq(coada* q) {
	return (q->front == NULL);
}

void deleteQueue(coada* q) {
	Node* aux;
	while (!isEmptyq(q)) {
		aux = q->front;
		q->front = q->front->next;
		free(aux);
	}
	free(q);
}