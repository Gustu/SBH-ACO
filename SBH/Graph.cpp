#include "Source.h"

Graph::Graph(Sequence *seq) {
	this->origSeq = new Sequence(seq);
	this->first = new Node(seq->first);
	this->first->adjacencyEdges = getAdjacencyEdges(this->first);
}

vector<Edge *> Graph::getAdjacencyEdges(Node *node) {
	vector<Edge *> edges;
	int j;
	for (j = 0; j < origSeq->oligos.size(); j++)
	{
		if (origSeq->oligos[j]->val == node->oligo->val)
			break;
	}

	for (int i = 0; i < origSeq->oligos.size(); i++)
	{
		if (origSeq->adjacencyMatrix[j][i] > 0 && origSeq->adjacencyMatrix[j][i] < origSeq->oligoLength){
			Node *prev = node;
			Node *next = new Node(origSeq->oligos[i]);
			edges.push_back(new Edge(prev, next, origSeq->adjacencyMatrix[j][i]));
		}

	}
	return edges;
}

void Graph::getPossibbleSequences() {
	possibbleSequences.push_back(origSeq->oligos);
}

void Graph::printPossibbleSequences() {
	for each (vector<Oligo *> seq in possibbleSequences)
	{
		for each (Oligo * oligo in seq)
		{
			cout << oligo->val << "->";
		}
		cout << endl;
	}
}