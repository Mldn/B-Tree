#ifndef _FILM_H_
#define _FILM_H_

#include <string> 
#include <iostream>
#include <fstream>
#include <istream>


using namespace std;

class Film {
public:
	Film() {}

	string naslov;
	long int  datum;
	string jezik;
	int trajanje;
	double zarada;
	bool valid;

};

#endif
