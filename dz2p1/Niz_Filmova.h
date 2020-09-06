#ifndef _NIZ_FILMOVA_H_
#define _NIZ_FILMOVA_H_

#include "Header.h"



class Niz_Filmova
{
	
public:
	Film * moviedb;
	int vel;
	Niz_Filmova() = default;
	void operator() (string str);
	void operator()(int n);
	~Niz_Filmova();
	Niz_Filmova& operator += (Film* f) {
		int i;
		for (i = 0; i < vel && f->datum > moviedb[i].datum; i++);
		vel++;
		for (int j = vel - 1; j > i;j--) moviedb[j] = moviedb[j - 1];
		moviedb[i] = *f;
		return *this;
	}
	Niz_Filmova& unisti() {
		delete[] moviedb;
		vel = 0;
		return *this;
	}
	Niz_Filmova& brisi(const string &s);

	friend ostream& operator << (ostream& ot , const Niz_Filmova &nf) {
		for (int i = 0 ; i < nf.vel ; i ++) 
			if (nf.moviedb[i].valid) {
				int y, m, d;
				y = nf.moviedb[i].datum / 10000;
				m = (nf.moviedb[i].datum / 100) % 100;
				d = nf.moviedb[i].datum % 100;
				ot << nf.moviedb[i].jezik << "," <<nf. moviedb[i].naslov << "," << y << "-" << m << "-" << d << "," <<nf. moviedb[i].zarada << "," << nf.moviedb[i].trajanje << "\n";
			}
		return ot;
	}

};
#endif // !_NIZ_FILMOVA_H_

