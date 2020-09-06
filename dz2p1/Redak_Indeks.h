#ifndef _REDAK_INDEKS_H_
#define _REDAK_INDEKS_H_

#include "Niz_Filmova.h"
class Node; 
class Redak_Indeks
{
public:
	int red;
	Node *root;
	Redak_Indeks() {
		root = nullptr;
		red = 0;
	}
	~Redak_Indeks() {
		root = nullptr;
		red = 0;
	}
	void operator() (int r) {
		root = nullptr;
		red = r;
	}
};
#endif // !_REDAK_INDEKS_H_

