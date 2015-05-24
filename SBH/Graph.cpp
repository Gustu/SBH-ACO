#include "Source.h"

Graph::Graph(Sequence *seq) {
	this->origSeq = new Sequence(seq);
	this->first = new Node(seq->first);
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

void Graph::getPossibbleSequences(Node *node, vector<Oligo *> pSeq, map<string, int> &oligoMap) {
	if (node->color != Node::Red && abs(node->oligo->oligoClass->getOligoClass(oligoMap[node->oligo->val]) - node->oligo->oligoClass->oligoClass) < 2) {
		/*vector<Edge *> edges = getAdjacencyEdges(node);
		
		for (int i = 0; i < edges.size(); i++) {
			getPossibbleSequences(edges[i]->next, pSeq, oligoMap);
		}
		possibbleSequences.push_back(origSeq->oligos);*/
	}
	
}

void Graph::printPossibbleSequences() {
	for each (vector<Oligo *> seq in possibbleSequences)
	{
		for each (Oligo * oligo in seq)
		{
			cout << oligo->val << "."<< oligo->oligoClass->oligoClass  << "->";
		}
		cout << endl;
	}
}

void Graph::startSearching() {
	map<string, int> oligoMap;
	setOligoMap(oligoMap);
	vector<Oligo *> seq;
	getPossibbleSequences(first, seq, oligoMap);
}

void Graph::setOligoMap(map<string, int> &oligoMap) {
	for (Oligo*oligo : origSeq->oligos) {
		oligoMap[oligo->val] = 0;
	}
}