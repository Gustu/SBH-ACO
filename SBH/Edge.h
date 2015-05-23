#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge
{
public:
	Node *prev;
	Node *next;

	Edge(Node *prev, Node *next);
	~Edge();

private:

};

#endif