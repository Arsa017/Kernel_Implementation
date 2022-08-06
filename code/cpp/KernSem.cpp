#include "KernSem.h"
#include "iostream.h"



Lista* KernelSem::semList = new Lista();

KernelSem::KernelSem(Semaphore* sem_, int init) {
	lock
	this->sem = sem_;
	value = init;
//	blockList->isprazniListu();
	blockList = new Lista();
	blockList->isprazniListu();

//	timeoutList->isprazniListu();
	timeoutList = new Lista();
	timeoutList->isprazniListu();
	//timeoutList = new Lista();
	semList->dodajNaKraj((void*)this); // ili samo dodajNaKraj(this)
	unlock
}

KernelSem::~KernelSem() {
	lock
	this->blockList->isprazniListu();
//	delete blockList;
	blockList=0;
	this->timeoutList->isprazniListu();
//	delete timeoutList;
	timeoutList=0;
	for(semList->tekuciNaPocetaK(); semList->postojiTekuci(); /*semList->sledeci()*/) {
		if ((Semaphore*)semList->dohvTekuci() == (Semaphore*) this->sem) {
			semList->obrisiTekuci();
		} else {
			semList->sledeci();
		}
	}
	unlock
}


int KernelSem::wait(Time maxTimeToWait) {
	lock
	this->value--; // umanjujemo vrednost semafora

	if(this->value < 0) {	// treba da se blokiramo na semaforu
		PCB::running->state = PCB::BLOCKED;	// oznacimo da je nit blokirana


		if(maxTimeToWait == 0) {	// smestimo running nit u odgovarajucu listu blokiranih niti
			if(PCB::running != 0)
				blockList->dodajNaKraj((void*)PCB::running);
			//	blockList->dodajNaPocetak((void*)PCB::running);
		//		cout << "======== Dodato u block listu =========== " << PCB::running->getID() << endl;
		//		asm cli

		} else {
		//	cout << "======= Nit dodata u timeoutListu ======  " << PCB::running->getID() << "========" <<endl;
			TimeoutElem* pom = new TimeoutElem(PCB::running, maxTimeToWait);
			if(pom == 0) {
				printf("======== CRUSH ===========\n");
				asm cli
			}
			if (pom!= 0) {
				timeoutList->dodajNaKraj((void*) pom);
			//	timeoutList->dodajNaPocetak((void*)pom);
	//			cout << "======== Dodato u timeOut listu =========== " << PCB::running->getID() << endl;
			}

		}

		//cout << "==== Zavrsio wait === " << PCB::running->blockFlag << endl;

		dispatch();	// zahtevamo promenu konteksta ----> nit je ovde stala
		//timerWait();

		if(PCB::running->blockFlag == 0) { // promenjen blockFlag na 0 znaci da se nit deblokirala zbog isteka vremena
			unlock;		// koje joj je dodeljeno
//			lock
//			cout << "====== vracaj nulu  ======  " << PCB::running->getID() << endl;
//			unlock
			return 0;
		}
	}

//	cout << "=========Ulazi i vraca 1==========" << PCB::running->getID()  << endl;
//	asm cli
	unlock
	return 1;
}


int KernelSem::signal(int n) {
	lock

	if(n<0) {  // npr signal(-3)
		unlock
		return n;
	}

	if((n==0) && (this->value >=0)) {
		this->value++;
		unlock
		return 0;
	}

	if((n>0) && (this->value >=0)) {
		this->value = this->value + n;
		unlock
		return 0;
	}

	//signal(0) -> treba da odblokiramo samo 1 nit, povratna vrednost je 0
	if(n == 0) {
		if(this->value < 0) {	// ako je vrednost semafora manja od nula, znaci da na njemu ima blokiranih niti
			int brojac1 = blockList->brojElemenataListe();
			if(brojac1 != 0) {	// da li je blockLista prazna ?
				PCB* tmp1 = (PCB*) this->blockList->uzmiPrvi();
				tmp1->state = PCB::READY;
				Scheduler::put((PCB*) tmp1);
				this->value++;
				unlock
				return 0;
			};
			int brojac2 = timeoutList->brojElemenataListe();
			if(brojac2 != 0 ) { // da li je timeoutLista prazna ?
				TimeoutElem* elem = (TimeoutElem*) this->timeoutList->uzmiPrvi();
				PCB* tmp2 = (PCB*) elem->blokiranaNit;
				tmp2->state = PCB::READY;
				Scheduler::put((PCB*) tmp2);
				this->value++;
				unlock
				return 0;
			}
		}
	}

	// da li imamo trazeni broj niti da odblokiramo, apsolutna (negativna) vrednost semafora oznacava broj blokiranih niti na njemu
	// signal(5)
	if(n>0) {

		if(this->value <= 0) {

			// 1. situacija da je signal(5) i sem->value = -8 ----> treba da odblokiramo 5 niti od 8 koje su blokirane
			if ((-(this->value)) >= n) { // 8>5
				int temp1 = this->blockList->brojElemenataListe();
				// 1) blockList.size() = 6 tj. blockList.size() >= n
				if(temp1 >= n) {
					for(int i=0; i<n; i++) {
						PCB* pom = (PCB*)blockList->uzmiPrvi(); // uzima prvi element iz liste i prevezuje pokazivace
						pom->state = PCB::READY;
						Scheduler::put((PCB*) pom);
						this->value++;
					}
					unlock
					return n;
				} else {
				// 2) blockList.size() = 3, a timeoutList.size() = 5 ----> treba da oblokiramo sve niti u blockListi i 2 niti u timeoutListi
					if (temp1 != 0) {	//  za slucaj da je blockLista prazna
						for(int j=0; j<temp1; j++) {
							PCB* pom = (PCB*)blockList->uzmiPrvi();
							pom->state = PCB::READY;
							Scheduler::put((PCB*)pom);
							this->value++;
							}
					}

					int k = n - temp1;	// ako je blockLista prazna onda treba da oblokiramo n niti u TimeoutListi

					for(int m = 0; m<k; m++) {
						TimeoutElem* elem = (TimeoutElem*) timeoutList->uzmiPrvi();
						PCB* pom = (PCB*) elem->blokiranaNit;
						pom->state = PCB::READY;
						Scheduler::put((PCB*) pom);
						this->value++;
					}

					unlock
					return n;
				}
			} else {     // 2. situacija signal(5) i sem->value = -3 ----> treba da odblokiramo 3 niti i da bude sem->value = 2
				// update 2. situacije, treba da odblokiramo sve niti u svim listama, da uvecamo vrednost semafora (val+n) i da vratimo broj odblokiranih niti
				int tmpBlockList = (int)blockList->brojElemenataListe();
				int tmpTimeoutList = (int)timeoutList->brojElemenataListe();

				if(tmpBlockList != 0) {
					while(blockList !=0) {
						PCB* pom = (PCB*) blockList->uzmiPrvi();
						pom->state = PCB::READY;
						Scheduler::put((PCB*) pom);
					}
				}

				if(tmpTimeoutList != 0) {
					while(timeoutList != 0) {
						TimeoutElem* elem = (TimeoutElem*) timeoutList->uzmiPrvi();
						PCB* pom = (PCB*) elem->blokiranaNit;
						pom->state = PCB::READY;
						Scheduler::put((PCB*) pom);
					}
				}

				this->value = this->value + n;
				int broj = (int)(tmpBlockList + tmpTimeoutList);
				unlock
				return broj;
/*
				int temp2 = (int) blockList->brojElemenataListe();
				if(temp2 == (-(this->value))) { // 3) blockLista ima 3 niti
					for(int i=0; i<temp2; i++) {
						PCB* pom = (PCB*) blockList->uzmiPrvi();
						pom->state = PCB::READY;
						Scheduler::put((PCB*) pom);
						//this->value++;
					}
					this->value = this->value + n;	// vrednost semafora = -3+5 = 2
					unlock
					return temp2;
				} else {  // 4) blockLista ima 2 niti, a timeoutLista ima 1 nit
					int brojac = 1;
					if (temp2 != 0) { // provera da li je blockLista prazna, tj. blockLista ima 0 niti, a timeoutLista ima 3 niti
						for(int i=0; i<temp2; i++) {
							PCB* pom = (PCB*) blockList->uzmiPrvi();
							pom->state = PCB::READY;
							Scheduler::put((PCB*) pom);
							brojac++;
						}
					}
					int k = (-(this->value)) - temp2;
					for(int m = 0; m<k; m++) {
						TimeoutElem* elem = (TimeoutElem*) timeoutList->uzmiPrvi();
						PCB* pom = (PCB*) elem->blokiranaNit;
						pom->state = PCB::READY;
						Scheduler::put((PCB*) pom);
						brojac++;
					}

					this->value = this->value + n;
					unlock
					return brojac;
*/
				}
			}
		}

		//dispatch();
	unlock
	return(-1);
	//return 0;
}


	//return 0; // proveriti koju vrednost treba da vrati f-ja signal !




int KernelSem::val() const {
	return this->value;
}

void KernelSem::azurirajTimeoutListu() {
	// prolazimo kroz celu timeoutListu za svaki od semafora na svaki prekid od hardverskog casovnika i umanjujemo vreme blokiranja svake niti
	// ako neko vreme bude 0, promenimo block flag na 0
	lock

	//cout << " F-ja pozvana! \n" << endl;// =============>> puca projekat

	for(KernelSem::semList->tekuciNaPocetaK(); KernelSem::semList->postojiTekuci(); KernelSem::semList->sledeci()) { // proveri prolazak kroz listu svih semafora

		KernelSem* tmpSem = (KernelSem*) KernelSem::semList->dohvTekuci();	// dohvadamo 1 semafor iz liste semafora

		if(tmpSem->timeoutList != 0) {

		/*==	cout << "timeoutList-a nije prazna" << endl; // KAKO se ovo desava dok jos nije pozvan wait(10) za tekucu nit ?!?

			TimeoutElem* pomTMP = (TimeoutElem*) tmpSem->timeoutList->dohvTekuci();

			cout << "Nit u timeoutListi je == Aleksandar " << pomTMP->blokiranaNit->getID() << "  ===  " << pomTMP->blokiranaNit << endl;*/

			for(tmpSem->timeoutList->tekuciNaPocetaK(); tmpSem->timeoutList->postojiTekuci();/* tmpSem->timeoutList->sledeci()*/) {

				TimeoutElem* pom = (TimeoutElem*) tmpSem->timeoutList->dohvTekuci();	// dohvatamo objekat klase TimeoutElem

				if(pom !=0) {

					pom->vremeBlokiranja--;			// umanjujemo vreme blokiranja niti

				//	cout << "==== Vreme blokiranja === " << pom->vremeBlokiranja << "  ===  "<< pom->blokiranaNit->getID() << endl;


					if(pom->vremeBlokiranja != 0) {		// vremeBlokiranja tekuce niti nije isteklo pa treba da je vratimo na njegovu poziciju u listi i da predjemo na sledeci element liste
						lock
						tmpSem->timeoutList->azurirajTekuci((void*) pom);
						tmpSem->timeoutList->sledeci();
					//	cout << "----- umanji vreme blokiranja! ----" << endl;
						//continue;
						unlock
					} else { // vreme blokiranja niti je isteklo, pa treba da promenimo njen blockFlag, da je smestimo u Scheduler i da je izbacimo iz timeoutListe
					//	lock
					//	if()
					//	cout << "----- odblokira! ----" << endl;
						pom->blokiranaNit->blockFlag = 0;
					//	cout << " == blockFlag ==  " << pom->blokiranaNit->blockFlag << endl;
						pom->blokiranaNit->state = PCB::READY;
					//	cout << "Stanje ->  " << pom->blokiranaNit->state << endl;
					//	PCB* nit = (PCB*) pom->blokiranaNit;
						Scheduler::put((PCB*)pom->blokiranaNit);
					//	cout << "Spremna nit " << pom->blokiranaNit->getID() << " je vracana u Scheduler "<< endl;
						tmpSem->timeoutList->obrisiTekuci(); // metoda obrisi tekuci ce nakon brisanja prebaciti pokazivac tek na sledeci element liste

					//	cout << "=== Nit je obrisana === " << endl;
						//TimeoutElem* tmp1 = (TimeoutElem*) tmpSem->timeoutList->dohvTekuci();
						//cout << "Tekuca nit u timeoutListi --->  " << tmp1->blokiranaNit->getID() << "  ====  " << tmp1->vremeBlokiranja << "== PUCA! ==" <<endl;
					//continue;

					//	unlock
					}
				}
			}
		}
	}

	unlock
}

