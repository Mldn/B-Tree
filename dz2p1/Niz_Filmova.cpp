#include "Niz_Filmova.h"

using namespace std;

void Niz_Filmova :: operator ()(string str)
{
	moviedb = new Film[4719];  
	vel = 0;
	string pom1, pom2;
	ifstream dat;
	if (dat.is_open()) cout << "GRESKA , fajl je otvoren" << endl;
	dat.open(str);

	while (!dat.eof()) {
		Film *f = new Film;

		getline(dat, pom1, ',');
		f->jezik = pom1; pom1 = "";

		char c; 
		dat.get(c);
		if (c =='\"') {
			getline(dat, pom1, '\"');
			f->naslov = pom1 ; pom1 = "";
			dat.get(c);
		}
		else {
				getline(dat, pom1, ',');
				f->naslov = c + pom1; pom1 = "";
		}
		
		
		getline(dat, pom1, '-');
		f->datum = stoi(pom1) * 10000; pom1 = "";

		getline(dat, pom1, '-');
		f->datum += stoi(pom1) * 100; pom1 = "";

		getline(dat, pom1, ',');
		f->datum += stoi(pom1); pom1 = "";
		
		getline(dat, pom1, ',');
		f->zarada = stod(pom1) ;  pom1 = "";
		
		getline(dat, pom1, '\n');
		f->trajanje =stoi(pom1);  pom1 = "";
		f->valid = true;
		
		//moviedb[vel++] = f;
		*this += f;
		//delete f;
	}

}
void Niz_Filmova :: operator () (int n) {
	string pom1;
	moviedb = new Film[4719];
	vel = 0;
	for (int i = 0; i < n; i++) {
		Film *f = new Film;
		cout << " Unesite naslov filma:"; cin >> ws; getline(cin,f->naslov); cout << endl;
		cout << " Unesite datum filma:"; cin >> f->datum; cout << endl;
		cout << " Unesite jezik filma:"; cin >> f->jezik; cout << endl;
		cout << " Unesite trajanje filma:"; cin >> f->trajanje; cout << endl;
		cout << " Unesite zaradu filma:"; cin >> f->zarada; cout << endl;
		cout << endl;
		f->valid = true ;

		*this += f;
	}

}
Niz_Filmova& Niz_Filmova::brisi(const string& s) {
	int i = 0;
	while ((moviedb[i].naslov != s) || (i = vel)) i++;
	if (i == 4719) return *this;
	else moviedb[i].valid = false;
	return *this;
}

Niz_Filmova::~Niz_Filmova()
{
	delete[] moviedb;
	vel = 0;
}

