#include "Node.h"



Node::Node(int rd)
{
	int b;
	parent = nullptr;
	keys = new int[rd - 1]; 
	pointN = new Node*[rd];
	pointA = new Film*[rd];
	br = 0;
	list = true;
	for (b = 0; b < rd; b++) {
		pointN[b] = nullptr;
		pointA[b] = nullptr;
	}
}


Node::~Node()
{
	delete[] keys;
	delete[] pointN;
	delete[] pointA;
	parent = nullptr;
	br = 0;
}

void Node::traverse(Node *p) {
	cout << endl;
	int i;
	for (i = 0; i < p->br; i++) {
		if (p->list == false) {
			traverse(p->pointN[i]);
		}
		cout << " " << p->keys[i];
	}
	if (p->list == false) {
		traverse(p->pointN[i]);
	}
	cout << endl;
}

bool Node::ins(int d, Redak_Indeks & bptree, Film* indeks) {
	int i; int temp;
	Film *ind;
	Node *x = bptree.root;
	if (x == nullptr) {
		bptree.root = new Node(bptree.red);
		x = bptree.root;
	}
	else {
		if (x->list == true && x->br == bptree.red - 1) {
			for (i = 0; i < x->br; i++) {
				if (d == x->keys[i]) return false;
			}
			temp = Node::podeli(x, -1, bptree, ind);
			x = bptree.root;
			for (i = 0; i < (x->br); i++) {
				if (d == x->keys[i]) return false;

				if ((d > x->keys[i]) && (d < x->keys[i + 1])) {
					i++;
					break;
				}
				else if (d < x->keys[0]) {
					break;
				}
				else {
					continue;
				}
			}
			x = x->pointN[i];
		}
		else {
			while (x->list == false) {
				for (i = 0; i < (x->br); i++)
				{
					if ((d > x->keys[i]) && (d < x->keys[i + 1])) {
						i++;
						break;
					}
					else if (d < x->keys[0]) {
						break;
					}
					else 
						if (d == x->keys[i]) return false;
					
					else {
						continue;
					}
				}
				if (((x->pointN[i])->br == bptree.red - 1) &&((x->pointN[i])->list == true)) {
					temp = Node::podeli(x, i, bptree, ind);
					x->keys[x->br] = temp;
					x->pointA[x->br] = ind;
					x->br++;
					continue;
				}
				else {
					x = x->pointN[i];
				}
			}
		}
	}
	for (i = 0; i < x->br; i++) {
		if (d == x->keys[i]) return false;
	}
	x->keys[x->br] = d;
	x->pointA[x->br] = indeks;
	sort(x->keys, x->pointA, x->br);
	x->br++;
	//cout << bptree.root << endl << endl;
	while (x != NULL) {
		if (x->br == bptree.red )
			if (x == bptree.root) podeliU(x, -1, bptree);
			else podeliU(x, 1, bptree);
		x = x->parent;
	}

	return true;
}



void Node::sort(int * niz, Film **pointA, int n)
{
	int i, j, pom;
	Film *pomf;
	for (i = 0; i < n; i++)
	{
		for (j = i; j <= n; j++)
		{
			if (niz[i] > niz[j])
			{
				pom = niz[i];	pomf = pointA[i];
				niz[i] = niz[j];	pointA[i] = pointA[j];
				niz[j] = pom;	pointA[j] = pomf;
			}
		}
	}
}


int Node::podeli(Node *x, int i, Redak_Indeks & bptree, Film *&indeks) {
	int j;
	int mid;
	Node *np1, *np3, *y;
	np3 = new Node(bptree.red);
	np3->list = true;
	int c = (bptree.red) / 2; //(order+1)/2
	if (i == -1) { //kada se izdize novi koren
		mid = x->keys[c];
		indeks = x->pointA[c];		
		//x->br--;
		np1 = new Node(bptree.red);
		np1->list = false;
		x->list = true;
		for (j = c + 1; j < bptree.red - 1; j++)			{
			np3->keys[j - (c + 1)] = x->keys[j];
			np3->pointA[j - (c + 1)] = x->pointA[j];
			np3->pointN[j - (c + 1)] = x->pointN[j];
			np3->br++;
			x->br--;
		}
		for (j = 0; j < bptree.red; j++)	{
			x->pointN[j] = nullptr;
		}
		np1->keys[0] = mid;
		np1->pointA[0] = indeks;
		np1->pointN[np1->br] = x;
		np1->pointN[np1->br + 1] = np3;
		np1->br++;
		bptree.root = np1;
		x->parent = np1;
		np3->parent = np1;
		x->pointN[x->br] = np3;
	}
	else {
		y = x->pointN[i];
		mid = y->keys[c];
		indeks = y->pointA[c];
		//y->br--;
		for (j = c + 1; j < bptree.red - 1; j++) {
			np3->keys[j - (c+1)] = y->keys[j];
			np3->pointA[j - (c + 1)] = y->pointA[j];
			np3->br++;			
			y->br--;
		}
		//x->keys[x->br] = mid;
		//x->br++;
		x->pointN[i] = y;
		x->pointN[i + 1] = np3;
		y->pointN[y->br + 1] = np3;
		y->parent = x;
		np3->parent = x;
	}
	return mid;
}


ostream& operator << (ostream &ot, Node *p) {
	Node * next = p, *gran = new Node(10);
	int i;
	queue <Node*> q;
	q.push(next);
	q.push(gran);
	while (!q.empty()) {
		next = q.front();
		q.pop();
		//q.push(gran);
		while (next != gran) {
			cout << "[";
			for (i = 0; i < next->br; i++) {
				ot << "(" << next->keys[i] << ")" << "  ";
			}
			cout << "]" << "   ";
			if (!next->list) {
				for (i = 0; i < next->br + 1; i++) {
					if (next->pointN[i] != nullptr) q.push(next->pointN[i]);
				}
			}
			else {
				for (i = 0; i < next->br; i++) {
					if (next->pointN[i] != nullptr) q.push(next->pointN[i]);
				}
			}
			next = q.front();
			q.pop();
		}
		if (!q.empty()) q.push(gran);
		ot << endl;
	}
	return ot;
}
void Node::podeliU(Node *x, int i, Redak_Indeks & bptree) {
	int j;
	int mid;
	Node *np1, *np3, *y;
	np3 = new Node(bptree.red);
	np3->list = false;
	int c = (bptree.red) / 2; //(order+1)/2
	if (i == -1) { //kada se izdize novi koren
		mid = x->keys[c];
		//indeks = x->pointA[c];		
		x->keys[c] = 0;
		x->br--;
		np1 = new Node(bptree.red);
		np1->list = false;
		x->list = false;
		for (j = c + 1; j <= bptree.red - 1; j++) {
			np3->keys[j - (c + 1)] = x->keys[j];
			//np3->pointA[j - (c + 1)] = x->pointA[j];
			np3->pointN[j - (c + 1)] = x->pointN[j]; x->pointN[j] = nullptr;
			np3->br++;
			x->br--;
		}
		np3->pointN[j - (c + 1)] = x->pointN[j]; x->pointN[j] = nullptr;
		/*for (j = 0; j < bptree.red; j++)	{
			x->pointN[j] = nullptr;
		}*/
		np1->keys[0] = mid;
		//np1->pointA[0] = indeks;
		np1->pointN[np1->br] = x;
		np1->pointN[np1->br + 1] = np3;
		np1->br++;
		bptree.root = np1;
		x->parent = np1;
		np3->parent = np1;
		np3->list = false;
	}
	else {
		y = x;
		x = x -> parent;
		mid = y->keys[c];
		//indeks = y->pointA[c];
		y->br--;
		for (j = c + 1; j <= bptree.red - 1; j++) {
			np3->keys[j - (c + 1)] = y->keys[j];
			np3->pointN[j - (c + 1)] = y->pointN[j]; y->pointN[j] = nullptr;
			//np3->pointA[j - (c + 1)] = y->pointA[j];
			np3->br++;
			y->br--;
		}
		np3->pointN[j - (c + 1)] = y->pointN[j]; y->pointN[j] = nullptr;
		x->keys[x->br] = mid;
		x->br++;
		//x->pointN[x->br] = y;
		x->pointN[x->br] = np3;
		//y->pointN[y->br + 1] = np3;
		y->parent = x;
		np3->parent = x;
		np3->list = false;
	}
}

bool Node::find(int d, Redak_Indeks & bptree)
{
	int i;
	Node* x = bptree.root;
	while (x != NULL) {
		for (i = 0; i < (x->br); i++)
		{
			if ((d > x->keys[i]) && (d < x->keys[i + 1])) {
				i++;
				break;
			}
			else if (d < x->keys[0]) {
				break;
			}
			else
				if (d == x->keys[i]) return true;

				else {
					continue;
				}
		}
		x = x->pointN[i];
	}
	return false;
}

void Node::between(int min, int max, Redak_Indeks & bptree)
{
	int i; 
	bool found = false;
	Node* x = bptree.root;
	while (!(x ->list)) {
		for (i = 0; i < (x->br); i++)
		{
			if ((min >= x->keys[i]) && (min < x->keys[i + 1])) {
				i++;
				break;
			}
			else if (min < x->keys[0]) {
				break;
			}
			else
				if (min == x->keys[i]) { found = true; break; }

				else {
					continue;
				}
		}
		if ((found) && (x->list))  break;
		else found = false;
		x = x->pointN[i];
	}
	for (i = 0; !(min > x->keys[i]) && (min < x->keys[i + 1]); i++);
	Film *  p1 = x->pointA[i];
	found = false;
	x = bptree.root;
	while (!(x->list)) {
		for (i = 0; i < (x->br); i++)
		{
			if ((max >= x->keys[i]) && (max < x->keys[i + 1])) {
				i++;
				break;
			}
			else if (max < x->keys[0]) {
				break;
			}
			else
				if (max == x->keys[i]) { found = true; break; }

				else {
					continue;
				}
		}
		if ((found) && (x->list))  break;
		else found = false;
		x = x->pointN[i];
	}
	for (i = 0; (!(max > x->keys[i]) && (max < x->keys[i + 1])); i++);
	Film *  p2 = x->pointA[i];
	while (p1 != p2) {
		if (p1->valid) {
			int y, m, d;
			y = p1->datum / 10000;
			m = (p1->datum / 100) % 100;
			d = p1->datum % 100;
			cout << p1->jezik << "," << p1->naslov << "," << y << "-" << m << "-" << d << "," << p1->zarada << "," << p1->trajanje << "\n";
		}
		p1++;
	}
	int y, m, d;
	y = p1->datum / 10000;
	m = (p1->datum / 100) % 100;
	d = p1->datum % 100;
	cout << p1->jezik << "," << p1->naslov << "," << y << "-" << m << "-" << d << "," << p1->zarada << "," << p1->trajanje << "\n";
}

int Node::stat(int g, Redak_Indeks & bptree)
{
	int i, s = 0;
	bool found = false;
	Node* x = bptree.root;
	while (!(x->list)) {
		if ((found) && (x->list))  break;
		else found = false;
		for (i = 0; i < (x->br); i++)
		{
			if ((g > x->keys[i]/100) && (g < x->keys[i + 1] /100)) {
				i++;
				break;
			}
			else if (g < x->keys[0]/100) {
				break;
			}
			else
				if (g == x->keys[i]/100) { found = true; break; }

				else {
					continue;
				}
		}
		x = x->pointN[i];
	}
	for (i = 0; (g > x->keys[i]/100); i++);
	Film *  p1 = x->pointA[i];
	//g = g / 100;
	while (g == (p1->datum / 10000)) {
		s++;
	}
	return s;
}
