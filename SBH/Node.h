#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Oligo.h"

using namespace std;

class Node
{
public:
	enum Color { Green, Red }; // Green - non-visited, Red - visited

	Color color;

	Oligo *oligo;

	Node(Oligo *oligo);

private:

};

#endif