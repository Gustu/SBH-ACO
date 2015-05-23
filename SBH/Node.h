#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include <vector>
#include "Oligo.h"

using namespace std;

class Node
{
public:
	enum Color { Green, Red }; // Green - non-visited, Red - visited

	Color color;

	vector<Edge *> adjacencyEdges;
	Oligo *oligo;

	Node(Oligo *oligo);
	~Node();

private:

};

#endif