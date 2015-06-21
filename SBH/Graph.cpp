#include "Source.h"

Graph::Graph(Sequence *seq) {
	this->origSeq = new Sequence(seq);
	this->first = new Node(seq->first);
	setOligoMap();
	oligoMap[this->first->oligo->val]++;
	pSeq.push_back(this->first->oligo);
	seqLength = origSeq->seq.size();
	overlap = 0;
}

int Graph::nucleotidesLeft() {
	int left = 0;
	map<string, int> temp;
	typedef map<string, int>::iterator it_type;
	
	for (Oligo * oligo : origSeq->oligos) {
		temp[oligo->val]++;
	}
	for (it_type iterator = temp.begin(); iterator != temp.end(); ++iterator) {
		int val = iterator->second;
		if (val > 0 && val < 3 && (1 - oligoMap[iterator->first]) > 0) {
			left++;
		}
		else if (val > 2 && val < 5 && (3 - oligoMap[iterator->first]) > 0) {
			left += 3 - oligoMap[iterator->first];
		}
		else if (val >= 5 && (3 - oligoMap[iterator->first]) > 0){
			left += 5 - oligoMap[iterator->first];
		}
	}
	return left;
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
	if (node->color != Node::Red && checkLengthCondition(weigth) && (errors <= bestErrorResult || bestErrorResult == -1)) {
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
					errors += edges[i]->errors;
					stack++;
					
					overlap += edges[i]->weight;
					getPossibbleSequences(edges[i]->next, errors, weigth);
					overlap -= edges[i]->weight;
				}
			}
			weigth -= (origSeq->oligoLength - edges[i]->weight);
		}
		if (pSeq.size()*origSeq->oligoLength - overlap == origSeq->seq.size()){
			if (bestErrorResult == -1) {
				bestErrorResult = errors;
			}
			else {
				if (errors <= bestErrorResult) {
					//cout << test++ << ":" << errors << "=" << weigth << endl;
					bestErrorResult = errors;
					possibbleSequences.push_back(pSeq);
					errorsList.push_back(errors);
				}
			}
			
		}
		oligoMap[pSeq[pSeq.size() - 1]->val]--;
		pSeq.pop_back();
	}
	else {
		node->color = Node::Red;
		oligoMap[pSeq[pSeq.size() - 1]->val]--;
		pSeq.pop_back();
		if (pSeq.size()*origSeq->oligoLength - overlap == origSeq->seq.size()){
			possibbleSequences.push_back(pSeq);
			errorsList.push_back(errors);
			//cout << test++ << ":" << errors << "=" << pSeq.size()*origSeq->oligoLength - overlap  << endl;
		}
	}

}

void Graph::printPossibbleSequences() {
	cout << "Stack::" << stack << endl;
	int c = 0;
	for each (vector<Oligo *> seq in possibbleSequences)
	{
		if (errorsList[c] == errorsList[errorsList.size() - 1]) {
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
		c++;
		
	}
	result.unique();
	cout << result.size();
	int num = 0;
	for (string r : result) {
		int same = 0;
		if (origSeq->seq.size() == r.size()){
			for (int i = 0; i < r.size(); i++){
				if (r[i] == origSeq->seq[i]){
					same++;
				}
			}
			cout << "#####" << endl;
			cout << num++ << ":" << same << "/" << r.size() << "[" << (int)((same * 100) / r.size()) << "%]\t" << endl;
			cout << r << endl;
			cout << "#####" << endl;
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
	if (weigth <= origSeq->seq.size() && origSeq->seq.size() >= pSeq.size()*origSeq->oligoLength - overlap){
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
	int temp = 0;
	for (Oligo*oligo : edge->oligos) {
		int differenceBetweenBaseClassAndActualClass = oligo->oligoClass->getOligoClass(oligoMap[oligo->val] + 1) - oligo->oligoClass->oligoClass;
		if (differenceBetweenBaseClassAndActualClass > 0) {
			temp++;
		}
		if (abs(differenceBetweenBaseClassAndActualClass) >= 2) {
			return false;
		}
	}
	for (Oligo*oligo : edge->oligos) {
		oligoMap[oligo->val]++;
	}
	edge->errors = temp;
	return true;
}
