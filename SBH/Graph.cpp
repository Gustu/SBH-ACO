#include "Source.h"

Graph::Graph(Sequence *seq) {
	this->origSeq = new Sequence(seq);
	this->first = new Node(seq->first);
	setOligoMap();
	oligoMap[this->first->oligo->val]++;
	pSeq.push_back(this->first->oligo);
	seqLength = origSeq->seq.size();

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
		if (origSeq->adjacencyMatrix[j][i] > origSeq->oligoLength - 3 && origSeq->adjacencyMatrix[j][i] < origSeq->oligoLength){
			Node *prev = node;
			Node *next = new Node(origSeq->oligos[i]);
			edges.push_back(new Edge(prev, next, origSeq->adjacencyMatrix[j][i]));
		}

	}
	return edges;
}

void Graph::getPossibbleSequences(Node *node, int errors, int weigth) {
	if (node->color != Node::Red && checkLengthCondition(weigth)) {
		vector<Edge *> edges = getAdjacencyEdges(node);

		for (int i = 0; i < edges.size(); i++) {
			weigth += (origSeq->oligoLength - edges[i]->weight);
			if (!addOligosBetweenTwoOligoMap(edges[i])) {
				node->color = Node::Red;
				weigth -= (origSeq->oligoLength - edges[i]->weight);
				continue;
			}
			//else
			//if (checkClassCondition() == -1) {
				//node->color = Node::Red;
				//oligoMap[pSeq[pSeq.size() - 1]->val]--;
				//pSeq.pop_back();
				//continue;
			//}
			else
			{
				if (oligoMap[edges[i]->next->oligo->val] <= seqLength){ // Stack Overflow barrier
					pSeq.push_back(edges[i]->next->oligo);
					oligoMap[edges[i]->next->oligo->val]++;
					if (checkClassCondition() == 0) errors++;
					stack++;
					getPossibbleSequences(edges[i]->next, errors, weigth);
				}
			}
			weigth -= (origSeq->oligoLength - edges[i]->weight);
		}
		if (weigth == origSeq->seq.size()){
			cout << test++ << ":" << errors << "=" << weigth << endl;
			possibbleSequences.push_back(pSeq);
		}
		oligoMap[pSeq[pSeq.size() - 1]->val]--;
		pSeq.pop_back();
	}
	else {
		node->color = Node::Red;
		oligoMap[pSeq[pSeq.size() - 1]->val]--;
		pSeq.pop_back();
		if (weigth == origSeq->seq.size()){
			possibbleSequences.push_back(pSeq);
			cout << test++ << ":" << errors << "=" << weigth << endl;
		}
	}

}

void Graph::printPossibbleSequences() {
	cout << "Stack::" << stack << endl;
	for each (vector<Oligo *> seq in possibbleSequences)
	{
		string sSeq = seq[0]->val; // Clean sequence from *seq ex. ACGTTTTT
		for each (Oligo * oligo in seq)
		{
			int i = 0;
			while (sSeq.substr(sSeq.size() - oligo->val.size() + i, sSeq.size()) != oligo->val.substr(0, oligo->val.size() - i) && i<oligo->val.size()) {
				i++;
			}
			if (i > 0 && i < oligo->val.size()) {
				sSeq += oligo->val.substr(oligo->val.size() - i, oligo->val.size());
				//cout << oligo->val << "." << oligo->oligoClass->oligoClass << "->";
			}
		}
		//cout << endl << sSeq << endl;
		result.push_back(sSeq);
	}
	result.unique();
	int num = 0;
	for (string r : result) {
		int same = 0;
		if (origSeq->seq.size() == r.size()){
			for (int i = 0; i < r.size(); i++){
				if (r[i] == origSeq->seq[i]){
					same++;
				}
			}
			cout << num++ << ":" << same << "/" << r.size() << "[" << (int)((same * 100) / r.size()) << "%]\t" << r << endl;
		}
	}
}

void Graph::startSearching() {
	getPossibbleSequences(first, 0, origSeq->oligoLength);
}

void Graph::setOligoMap() {
	for (Oligo*oligo : origSeq->oligos) {
		oligoMap[oligo->val] = 0;
	}
}

bool Graph::checkLengthCondition(int weigth) {
	if (weigth <= origSeq->seq.size()){
		return true;
	}
	else{
		return false;
	}
	/*if (pSeq.size() <= (origSeq->seq.length() - origSeq->oligoLength + 1)) {
		return true;
		}
		else {
		return false;
		}*/
}

/*
* -1 - skok o 2 klasy
* 0 - skok o jedna klase do góry
* 1 - skok o jedna klase w dó³
* 2 - zgodnoœæ
*/
int Graph::checkClassCondition() {
	int ret = 2;
	for (Oligo*oligo : pSeq) {
		int differenceBetweenBaseClassAndActualClass = oligo->oligoClass->getOligoClass(oligoMap[oligo->val]) - oligo->oligoClass->oligoClass;
		if (differenceBetweenBaseClassAndActualClass >= 2 || differenceBetweenBaseClassAndActualClass <= -2) {
			ret = -1;
			return ret;
		}
		else if (differenceBetweenBaseClassAndActualClass == 1) {
			ret = 0;
		}
		else if (differenceBetweenBaseClassAndActualClass == -1){
			ret = 1;
		}
	}
	return ret;
}

bool Graph::addOligosBetweenTwoOligoMap(Edge *edge) {
	edge->getBetweenOligos(origSeq->oligoLength);
	for (Oligo*oligo : edge->oligos) {
		int differenceBetweenBaseClassAndActualClass = abs(oligo->oligoClass->getOligoClass(oligoMap[oligo->val] + 1) - oligo->oligoClass->oligoClass);
		if (differenceBetweenBaseClassAndActualClass >= 2) {
			return false;
		}
	}
	for (Oligo*oligo : edge->oligos) {
		oligoMap[oligo->val]++;
	}
	return true;
}