#include "Source.h"

Graph::Graph(Sequence *seq) {
	this->origSeq = new Sequence(seq);
	this->first = new Node(seq->first);
	setOligoMap();
	oligoMap[this->first->oligo->val]++;
	pSeq.push_back(this->first->oligo);
	seqLength = 1;

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

void Graph::getPossibbleSequences(Node *node) {
	if (node->color != Node::Red && checkLengthCondition()) {
		vector<Edge *> edges = getAdjacencyEdges(node);

		for (int i = 0; i < edges.size(); i++) {
			if (!addOligosBetweenTwoOligoMap(edges[i])) {
				node->color = Node::Red;
				continue;
			}
			/*if (checkClassCondition() == -1) {
				node->color = Node::Red;
				oligoMap[pSeq[pSeq.size() - 1]->val]--;
 				pSeq.pop_back();
			}*/
			else {
				//if (oligoMap[edges[i]->next->oligo->val] <= seqLength){
					pSeq.push_back(edges[i]->next->oligo);
					oligoMap[edges[i]->next->oligo->val]++;
					getPossibbleSequences(edges[i]->next);
				//}
			}
		}
		oligoMap[pSeq[pSeq.size() - 1]->val]--;
		pSeq.pop_back();
	}
	else {
		node->color = Node::Red;
		oligoMap[pSeq[pSeq.size() - 1]->val]--;
		pSeq.pop_back();
		possibbleSequences.push_back(pSeq);
	}

}

void Graph::printPossibbleSequences() {
	for each (vector<Oligo *> seq in possibbleSequences)
	{
		for each (Oligo * oligo in seq)
		{
			cout << oligo->val << "." << oligo->oligoClass->oligoClass << "->";
		}
		cout << endl;
	}
}

void Graph::startSearching() {
	getPossibbleSequences(first);
}

void Graph::setOligoMap() {
	for (Oligo*oligo : origSeq->oligos) {
		oligoMap[oligo->val] = 0;
	}
}

bool Graph::checkLengthCondition() {
	if (pSeq.size() <= (origSeq->seq.length() - origSeq->oligoLength + 1)) {
		return true;
	}
	else {
		return false;
	}
}

/*
* -1 - skok o 2 klasy
* 0 - zgodnosc klas +- 1
* 1 - klasy zgodne w 100%
*/
int Graph::checkClassCondition() {
	int ret = 1;
	for (Oligo*oligo : pSeq) {
		int differenceBetweenBaseClassAndActualClass = abs(oligo->oligoClass->getOligoClass(oligoMap[oligo->val]) - oligo->oligoClass->oligoClass);
		if (differenceBetweenBaseClassAndActualClass >= 2) {
			ret = -1;
			return ret;
		}
		else if (differenceBetweenBaseClassAndActualClass == 1) {
			ret = 0;
		}
	}
	return ret;
}

bool Graph::addOligosBetweenTwoOligoMap(Edge *edge) {
	edge->getBetweenOligos(origSeq->oligoLength);
	for (Oligo*oligo : edge->oligos) {
		int differenceBetweenBaseClassAndActualClass = abs(oligo->oligoClass->getOligoClass(oligoMap[oligo->val]+1) - oligo->oligoClass->oligoClass);
		if (differenceBetweenBaseClassAndActualClass >= 2) {
			return false;
		}
	}
	for (Oligo*oligo : edge->oligos) {
		oligoMap[oligo->val]++;
	}
	return true;
}