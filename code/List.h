#ifndef _Genericka_Lista_
#define _Genericka_Lista_

#include <stdio.h>

class Lista {
private:
	struct Elem {
		void* data;
		Elem* sled;
		Elem(void* data_) {
			this->data = data_;
			this->sled = 0;
		}
	};
	Elem* prvi, *posl, *tek;
public:
	Lista();
	~Lista();

	void dodajNaPocetak(void* data);
	void dodajNaKraj(void* data);
	void tekuciNaPocetaK();
	void sledeci();
	int postojiTekuci();
	void dodajPreTekuceg(void* data);
	void* dohvTekuci(); // dohvatanje podatka bez izbacivanja iz liste
	void obrisiTekuci();
	void* uzmiPrvi();
	void* uzmiTekuci(); // uz izbacivanje iz liste
	void* uzmiPosl();
	int daLiJePrazna();
	void isprazniListu();
	void ispisiListu();
	int brojElemenataListe();
	void azurirajTekuci(void* data);

};

#endif
