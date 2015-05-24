#include "Source.h"

Edge::Edge(Node *next, Node *prev) {
	this->next = next;
	this->prev = prev;
	this->weight = 0;
}

Edge::Edge(Node *next, Node *prev, int weight) { 
	this->next = next;
	this->prev = prev;
	this->weight = weight;
}

void Edge::getBetweenOligos() {
	Oligo *prev = new Oligo();
}