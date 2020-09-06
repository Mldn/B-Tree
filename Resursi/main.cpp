#include "Niz_Filmova.h"
#include "Node.h"
#include "Redak_Indeks.h"
#include "Header.h"


using namespace std;

int main() {
	
	int q = 1;
	Niz_Filmova nf;
	Redak_Indeks ri;
	int r = 0;
	
	cout << " Unesite nacin na koji zelite da unesete bazu(0 za standardni ulaz, ostalo za datoteku)\n";
	cin >> q;
	if (q) { nf("tmdb_movies.csv");  }
	else {
		int n;
		cout << "Unesite broj elemenata koje zelite da unesete u bazu "; cin >> n;
		nf(n);
	}
	q = 1;
	while (q) {
		cout << "IZABERITE OPCIJU MENIJA:\n";
		cout << endl;
		cout << "1.Ispis baze\n";
		cout << "2.Kreiranje B+ stabla\n ";
		cout << "3.Unos kljuceva u stablo\n";
		cout << "4.Ispisi stablo\n";
		cout << "5.Pretraga stabla\n";
		cout << "6.Pronalazenje svih filmova iz zadatog opsega\n";
		cout << "7.Pronalazenje statistike izdavanja za date godine\n";
	


		cin >> q;
		switch (q) {
		case 1:
		{
			cout << nf; break;
		}
		case 2:
		{
			cout << "Unesite red stabla:";
			cin >> r;
			Redak_Indeks ri;
			break;
		}
		case 3:
		{
			ri(r);
			for (int i = 0; i < nf.vel; i++) {
				Node::ins(nf.moviedb[i].datum / 100, ri, &(nf.moviedb[i]));
				//cout << ri.root;
				//cout << endl;
				//cout << endl;
				/*Node::traverse(ri.root);
				cout << endl;
				cout << endl;*/

			}
			//Node::traverse(ri.root);
			break;
		}
		case 4: cout << ri.root; break;
		case 5:
		{
			cout << "Unesite datum kljuca koji zelite da pronadjete:\n";
			int dat;
			cin >> dat;
			bool flag = Node::find(dat, ri); 
			if (flag ) cout << "Kljuc je uspesno pronadjen\n";
			else cout << "Kljuc nije pronadjen\n";
			break;

		}
		case 6:
		{
			int max, min;
			cout << "Unesite zadati opseg :";
			cin >> min >> max;
			if (!(Node::find(min, ri))||!(Node::find(max, ri))) {
				cout << "Unesen je nevalidan datum\n";
				break;
			}
			Node::between(min, max, ri); break;
		}
		case 7:
		{
			int br,i,s = 0,god;
			cout << "Unesite broj godina za koje zelite da odradite statistiku :";
			cin >> br;
			for (i = 0; i < br; i++) {
				cout << "Unesite godinu :"; cin >> god;
				s += Node::stat(god, ri);
			}
			s /= br;
			cout << "Statistika za date godine je:";
			cout << s << endl;
		}
		}
		
	}
}
	//system("pause");
