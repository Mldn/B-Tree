#ifndef _NODE_H_
#define _NODE_H_

#include "Niz_Filmova.h"
#include "Redak_Indeks.h"
#include "Header.h"
#include <queue>

class Node
{
	int * keys;
	Node** pointN;
	Film ** pointA;
	int br;
	bool list;
	Node* parent;
public:
	Node(int rd);
	~Node();
	static bool ins(int d, Redak_Indeks &bptree , Film* indeks);
	static void sort(int *niz, Film **pointA, int n);
	static int podeli(Node * x, int i, Redak_Indeks & bptree, Film *&indeks);
	static void traverse(Node *p);
	friend ostream& operator << (ostream &ot, Node* p);
	static void podeliU(Node * x, int i, Redak_Indeks & bptree);
	static bool find(int d, Redak_Indeks & bptree);
	static void between(int min, int max, Redak_Indeks &bptree);  
	static int stat(int g, Redak_Indeks &bptree);
};


#endif _NODE_H_