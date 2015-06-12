#include "Source.h"

Edge::Edge(Node *prev, Node *next) {
	this->next = next;
	this->prev = prev;
	this->weight = 0;
	this->errors = 0;
}

Edge::Edge(Node *prev, Node *next, int weight) { 
	this->next = next;
	this->prev = prev;
	this->weight = weight;
	this->errors = 0;
}

void Edge::getBetweenOligos(int oligoLength) {
	Oligo *prev = this->prev->oligo;
	Oligo *next = this->next->oligo;

	string prevval = prev->val;

	string val = prevval.append(next->val.substr(weight, oligoLength - weight));

	for (int i = 1; i < val.length() - oligoLength; i++) {
		string temp = val.substr(i, oligoLength);
		oligos.push_back(new Oligo(temp));
	}
}