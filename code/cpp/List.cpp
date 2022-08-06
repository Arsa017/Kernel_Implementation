#include "List.h"
#include <iostream.h>

Lista::Lista() {	// konsturktor klase
	prvi = posl = tek = 0;
	this->isprazniListu();
}

Lista::~Lista() {
	this->isprazniListu(); // brisanje liste
}

void Lista::dodajNaPocetak(void* data) {	// c++ knjiga strana 255
	Elem* pom = new Elem(data);
	if(pom !=0) {
		pom->sled = prvi;
		prvi = pom;
		if(posl == 0) posl = prvi;
	} else {
		printf("======== CRUSH dodajNaPocetak() ===========\n");
					asm cli
	}
	//dodatno
//	pom=0;
//	delete pom;

}

void Lista::dodajNaKraj(void* data) {
	Elem* pom = new Elem(data);
	if(pom != 0) {
		posl = (!prvi ? prvi : posl->sled) = (Elem*) pom /*new Elem(data)*/;
	} else {
		printf("======== CRUSH dodajNaKraj() ===========\n");
		asm cli
	}
	// dodatno
	//pom = 0;
	//delete pom;
}

void Lista::dodajPreTekuceg(void* data) {
	Elem* pom;
	if(tek) {
		pom = new Elem(data);
		pom->sled = tek->sled;
		pom->data = tek->data;
		tek->sled = pom;
		tek->data = data;
		if(posl == tek) posl = pom;
		tek = tek->sled;
	} else
		if(!prvi) prvi = posl = tek = new Elem(data); // u slucaju da je lista prazna
}

void Lista::tekuciNaPocetaK() {
	tek = prvi;
}

void Lista::sledeci() {
	if(tek) tek = tek->sled;
	//cout << "== Presao na sledeci == " << endl;
}

int Lista::postojiTekuci() {
	return tek != 0;
}

void* Lista::uzmiTekuci() {	// dohvatanje podatka sa izbacivanjem iz liste
	void* ret = 0;
	if(tek) {
		ret = tek->data;
		obrisiTekuci();
	}
	return ret;
}

void* Lista::dohvTekuci() {	// dohvatanje podatka bez izbacivanja iz liste
	return tek ? tek->data : 0 ;
}

void Lista::azurirajTekuci(void* data_) {
	tek->data = data_;
}

void* Lista::uzmiPrvi() {
	void* ret = 0;
	if(prvi) {
		Elem* tmp =(Elem*) prvi;
		prvi = prvi->sled;
		ret = tmp->data;
		if(tek == tmp) tek = prvi;
		if(!prvi) posl = 0;
		delete tmp;
	}
	return ret;
}

void* Lista::uzmiPosl() {
	Elem *tmp1 =(Elem*) tek, *tmp2 =(Elem*) posl;
	tek = posl;
	void* ret = uzmiTekuci();
	if(tmp1 != tmp2) tek = tmp1;
	return ret;
}

int Lista::daLiJePrazna() {
	return prvi==0;
}

void Lista::obrisiTekuci() {	// proveri metodu
	if(tek == 0) return;
	Elem* tmp;
	if(tek->sled) {
		tmp = tek->sled;
		tek->data =  tmp->data;
		tek->sled = tmp->sled;
		if(posl == tmp) posl = tek;
		delete tmp->data; // dodato
	    delete tmp->sled; // dodato
		delete tmp;
	} else {
		tmp = prvi;
		while(tmp->sled != posl) {
			tmp = tmp->sled;
			if(!tmp) break; // za slucaj da lista ima samo 1 element
		}
		if(tmp) {
			posl = tmp;
			tmp->sled = 0;
		} else prvi = posl = 0;
		delete tek->data; // dodato
		delete tek->sled; // dodato
		delete tek;
		tek = 0;
		// dodato
	//	delete tmp;
	//	tmp=0;
	}
}

void Lista::isprazniListu() {
	while(prvi) {
		posl = prvi;
		prvi = prvi->sled;
		delete posl->data; // dodatno
		delete posl->sled; // dodatno
		delete posl;
	}
	//dodato delete
	prvi = posl = tek = 0;
//	delete prvi;
//	delete tek;
//	tek=0;

}

/*
void Lista::ispisiListu() {	 // ispis liste ako su podaci tipa int
	tek = prvi;
	if(tek == 0) {
		printf("Lista je prazna\n");
		asm cli;
	}
	while(tek) {
		int* t = (int*) (tek->data);
		printf("%d ", t);
		asm cli;
		tek = tek->sled;
	}
}
*/

int Lista::brojElemenataListe() {
	int brojac = 0;
	Elem* tmp = prvi;
	while(tmp != 0) {
		brojac++;
		tmp = tmp->sled;
	}
	return brojac;
}



