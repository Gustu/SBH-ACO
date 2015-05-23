#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include <vector>

using namespace std;

class Node
{
public:
	vector<Edge *> adjacencyEdges;

	Node();
	~Node();

private:

};

#endif