#include "Oligo.h"

Oligo::Oligo() {
	val = "";
}

Oligo::Oligo(string val) {
	this->val = val;
	setOligoClass(0);
}

Oligo::Oligo(string val, int quantity) {
	this->val = val;
	setOligoClass(quantity);
}

void Oligo::setOligoClass(int quantity) {
	if (quantity == 0) {
		oligoClass = First;
	}
	else if (quantity > 0 && quantity < 3) {
		oligoClass = Second;
	}
	else if (quantity > 2 && quantity < 5) {
		oligoClass = Third;
	}
	else {
		oligoClass = Fourth;
	}
}