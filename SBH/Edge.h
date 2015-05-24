#ifndef EDGE_H
#define EDGE_H

class Node;
class Oligo;

#include <vector>
#include "Oligo.h"

class Edge
{
public:
	Node *prev;
	Node *next;
	vector<Oligo *> oligos;
	double weight;

	Edge(Node *prev, Node *next);
	Edge(Node *prev, Node *next, int weight);

	void getBetweenOligos();

};

#endif