#include <iostream>
#include <string.h>
#include "functii.h"

using namespace std;

void eroare(int n, int aux)
{
	switch (n)
	{
	case 1://ERR: DECK_INDEX_OUT_OF_BOUNDS/
		cout << "The provided index is out of the bounds of the deck list\n";
		break;
	case 2://ERR:CADR_INDEX_OUT_OF_BOUNDS
		cout << "The provided index is out of bounds for deck " << aux << endl;
		break;
	case 3://ERR: INVALID CARD
		cout << "The provided card is not a valid one.\n";
		break;
	case 4://ERR:INVALID_COMAND
		cout << "Invalid comand. Please try again\n";
		break;
	default:
		cout << "Eroare invalida\n";
	}

}


void menu(void)
{

	jucator om;
	initJucator(om);
	int ok = 1;
	while (ok)
	{
		int n;
		cout << "Introduceti:\n\t1\t Pentru ADD_DECK, urmat de numarul de carti\n\t2\t Pentru DEL_DECK, urmat de index\n\t3\t pentru DEL_CARD, urmat de index pachet si index carte\n\t4\t pentru ADD_CARDS, urmat de index pachet si numar carti\n\t5\t pentru DECK_NUMBER\n\t6\t pentru DECK_LEN, urmat de index pachet\n\t7\t pentru SHUFFLE_DECK, urmat de index pachet\n\t8\t pentru MERGE_DECKS, urmat de index pachet 1 si index pachet 2\n\t9\t pentru SPLIT_DECK, urmat de index pachet si index split\n\t10\t petnru REVERSE_DECK, urmat de index pachet\n\t11\t pentru SHOW_DECK, urmat de index pachet\n\t12\t pentru SHOW_ALL\n\t13\t pentru SORT_DECK\n\t14\t pentru EXIT\nOptiune: ";
		cin >> n;
		switch (n)
		{
		case 1: ADD_DECK(om);
			break;
		case 2:
			cout << "Index deck: ";
			int p;
			cin >> p;
			DEL_DECK(om, p, 1);
			break;

		case 3: DEL_CARD(om);
			break;
		case 4: ADD_CARDS(om);
			break;

		case 5:
			DECK_NUMBER(om);
			break;

		case 6:
			DECK_LEN(om);
			break;
		case 7:
			SHUFFLE_DECK(om);
			break;
		case 8:
			MERGE_DECKS(om);
			break;
		case 9: SPLIT_DECK(om);
			break;

		case 10:REVERSE_DECK(om);
			break;
		case 11:
			int x;
			cout << "Indexul pachetui\n";
			cin >> x;
			SHOW_DECK(om, x);
			break;
		case 12:
			SHOW_All(om);
			break;

		case 13:
			SORT_DECK(om);
			break;
		case 14:
			EXIT(om);
			ok = 0;
			break;

		default:
			n = NULL;
			eroare(4, -1);
			break;
		}
	}
}


void initCarte(carte*& cap)//initializeaza cartile dintr-un pachet
{
	cap = 0;
}

void initPachet(pachet*& cap)
{
	cap = 0;
}

void initJucator(jucator& om)
{
	initPachet(om.cap);
	initPachet(om.ultimul);
	om.nr_pachete = 0;
}

int isValid(info x)//valideaza datele de pe fiecare carte
{
	if (x.val < 1 || x.val>14)
		return 0;
	if (strcmp("TREFLA", x.simbol) * strcmp("PICA", x.simbol) * strcmp("CUPA", x.simbol) * strcmp("CARO", x.simbol))
		return 0;
	/*
		return 0;
		daca toate strcmp rerturneaza valori diferite de 0,
		atunci simbolul nu face parte din cele standard,
		adica nu l-am gasit printre cele standard
	*/
	return 1;
	///cartea este valida;
}


void afisareCarte(carte* cap)
{
	
	if (cap->next)
		while (cap->next)
		{
			cout << '\t' << cap->face.val << ' ' << cap->face.simbol << '\n';
			cap = cap->next;
		}
	cout << '\t' << cap->face.val << ' ' << cap->face.simbol << '\n';
}



void ADD_DECK(jucator& om) 
{
	int err = 1;
	int nr_carti;
	info carte_curenta;
	cout << "Introduceti numarul de carti din pachet: ";
	cin >> nr_carti;
	if (nr_carti == 0)
	{
		eroare(5, 3);
		return;
	}
	cout << "Introduceti valoarea cartii din pachet (numar de la 1 la 14), respectiv Simbolul: PICA, CUPA, CARO, TREFLA\n";
	pachet* pach_nou = new pachet;
	pach_nou->nr_carti = nr_carti;
	pach_nou->elemente = NULL;
	for (int i = 0; i < nr_carti; i++) {
		cout << "Introduceti carte " << i + 1 << ": ";
		if (err == 0)
		{
			cin.get();
			err = 1;
		}
		cin >> carte_curenta.val;
		cin >> carte_curenta.simbol;
		if (isValid(carte_curenta)) { // verificare validitate carte
			if (pach_nou->elemente == NULL) {
				// creeaza primul nod din lista dublu inlantuita de carti
				carte* nod_nou = new carte;
				nod_nou->face = carte_curenta;
				nod_nou->prev = NULL;
				nod_nou->next = NULL;
				pach_nou->elemente = nod_nou;
				pach_nou->ultima = nod_nou;
				
			}
			else {
				// adauga nodul la dreapta in lista dublu inlantuita de carti
				inserareDreapta(pach_nou->ultima, carte_curenta);
			}
		}
		else {

			eroare(3, -1);
			i--; // decrementare index pentru a reîncerca să adăugați aceeași carte
			err = 0;
		}
	}
	// adauga pachetul la dreapta in lista dublu inlantuita de pachete
	pach_nou->prev = om.ultimul;
	pach_nou->next = NULL;
	if (om.ultimul != NULL) {
		om.ultimul->next = pach_nou;
	}
	else {
		om.cap = pach_nou;
	}
	om.ultimul = pach_nou;
	om.nr_pachete++;
	cout << "The deck was successfully created with " << nr_carti << " cards\n";
}

void SHOW_All(jucator om)
{
	if (om.nr_pachete == 0)
		cout << "You have to add decks in order to display them\n";
	int i;
	for (i = 0; i < om.nr_pachete; i++)
	{
		cout << "Deck " << i << endl;
		afisareCarte(om.cap->elemente);
		om.cap = om.cap->next;
	}
}


void EXIT(jucator& om) {
	pachet* current_pachet = om.cap;
	while (current_pachet != NULL) {
		carte* current_carte = current_pachet->elemente;
		while (current_carte != NULL) {
			carte* next_carte = current_carte->next;
			memset(current_carte, 0, sizeof(carte));
			delete current_carte;
			current_carte = next_carte;
		}
		pachet* next_pachet = current_pachet->next;
		current_pachet->elemente = NULL;
		memset(current_pachet, 0, sizeof(pachet));
		delete current_pachet;
		current_pachet = next_pachet;
	}
	om.cap = 0;
	om.ultimul = 0;
	om.nr_pachete = 0;
	cout << "Jocul s-a terminat. Toata memoria a fost eliberata.\n";
}

void DEL_DECK(jucator& om, int n, int afis)
{
	if (n > om.nr_pachete || n < 0)
	{
		eroare(1, -1);
		return;
	}
	else
	{
		if (n == 0)
		{
			if (om.nr_pachete == 1)
			{
				carte* current_carte = om.cap->elemente;
				while (current_carte != NULL)
				{
					carte* next_carte = current_carte->next;
					memset(current_carte, 0, sizeof(carte));
					delete current_carte;
					current_carte = next_carte;
				}
				memset(om.cap, 0, sizeof(pachet));
				delete om.cap;
				om.cap = om.ultimul = 0;
				om.nr_pachete--;
				if (afis)
					cout << "The deck " << n << " was successfully deleted.\n";
			}
			else
			{
				
				pachet* aux = om.cap;
				om.cap = om.cap->next;
				om.cap->prev = 0;
				carte* current_carte = aux->elemente;
				while (current_carte != NULL)
				{
					carte* next_carte = current_carte->next;
					memset(current_carte, 0, sizeof(carte));
					delete current_carte;
					current_carte = next_carte;
				}
				memset(aux, 0, sizeof(pachet));
				delete aux;
				om.nr_pachete--;
				if (afis)
					cout << "The deck " << n << " was successfully deleted.\n";
			}
		}		
		else
		{
			pachet* aux = om.cap;
			for (int i = 0; i < n - 1; i++)
				aux = aux->next;
			if (aux->next)
			{
				pachet* naux = aux->next;
				aux->next = naux->next;
				if (naux->next!= NULL)
					naux->next->prev = aux;
				aux = naux;
				if (aux == 0)
					return;
				carte* current_carte = aux->elemente;
				while (current_carte != NULL)
				{
					carte* next_carte = current_carte->next;
					memset(current_carte, 0, sizeof(carte));
					delete current_carte;
					current_carte = next_carte;
				}
				if (aux)
				{
					memset(aux, 0, sizeof(pachet));
				}

				delete aux;

			}
			om.nr_pachete--;
			if(afis)
				cout << "The deck " << n << " was successfully deleted.\n";
		}
	}

}


void SHOW_DECK(jucator om, int x)
{
	if (x > om.nr_pachete - 1 || x < 0)
	{
		eroare(1, -1);
		return;
	}
	else
	{
		cout << "Deck " << x << '\n';
		if (x == 0)
		{
			afisareCarte(om.cap->elemente);
		}
		else
		{
			for (int i = 0; i < x; i++)
			{
				om.cap = om.cap->next;
			}
			afisareCarte(om.cap->elemente);

		}
	}

}

void DEL_CARD(jucator& om)
{
	int index_pachet, index_carte;
	cout << "Index pachet: ";
	cin >> index_pachet;
	if (index_pachet > om.nr_pachete - 1 || index_pachet < 0)
	{
		eroare(1, -1);
		return;
	}
	else
	{
		cout << "Index carte: ";
		cin >> index_carte;
		pachet* aux = om.cap;
		for (int i = 0; i < index_pachet; i++)
			aux = aux->next;
		if (aux->nr_carti < (index_carte+1) || index_carte < 0)
		{
			eroare(2, index_pachet);
			return;
		}
		else
		{
			if (aux->nr_carti == 1)
				DEL_DECK(om, index_pachet, 0);
			else
			{
				carte* aux2 = aux->elemente;
				for (int i = 0; i < index_carte-1; i++)
					aux2 = aux2->next;
				carte* ce_vom_sterge = aux2->next;
				aux2->next = ce_vom_sterge->next;
				if (ce_vom_sterge->next)
					ce_vom_sterge->next->prev = aux2;
				if(ce_vom_sterge)
					memset(ce_vom_sterge, 0, sizeof(carte));
				delete ce_vom_sterge;
				aux->nr_carti--;

			}
			cout << "The card was successfully deleted from deck "<< index_pachet<<".\n";
		}
	}
}


void ADD_CARDS(jucator& om)
{
	int index_pachet, nr_carti;
	cout << "Index pachet :";
	cin >> index_pachet;
	if (index_pachet > om.nr_pachete - 1 || index_pachet < 0)
	{
		eroare(1, -1);
		return;
	}
	else
	{
		pachet* aux = 0;
		aux=om.cap;
		for (int i = 0; i < index_pachet; i++)
			aux = aux->next;
		cout << "Numarul de carti pe care doriti sa le adaugati :";
		cin >> nr_carti;
		aux->nr_carti += nr_carti;
		/// inserare_stanga(carte * &nod_initial, info cartea_noua)
		cout << "Introduceti valoarea cartii din pachet (numar de la 1 la 14), respectiv Simbolul: PICA, CUPA, CARO, TREFLA\n";
		for (int i = 0; i < nr_carti; i++)
		{
			cout << "Introduceti carte " << i + 1 << ": ";
			info carte_curenta;
			cin >> carte_curenta.val;
			cin >> carte_curenta.simbol;
			if (isValid(carte_curenta))  // verificare validitate carte
			{// adauga nodul la dreapta in lista dublu inlantuita de carti
				inserareStanga(aux->elemente, carte_curenta); 
			}
			else 
			{

				eroare(3, -1);
				i--; // decrementare index pentru a reîncerca să adăugați aceeași carte
			}
			
		}
		cout << "The cards were successfully added to deck " << index_pachet << ".\n";
	}

}

void DECK_NUMBER(jucator om)
{
	cout << "The number of decks is " << om.nr_pachete << ".\n";
}

void DECK_LEN(jucator om)
{
	int index_pachet;
	pachet* aux;
	cout << "Index pachet: ";
	cin>> index_pachet;
	if (index_pachet > om.nr_pachete - 1 || index_pachet < 0)
	{
		eroare(1, -1);
		return;
	}
	aux = om.cap;
	for (int i = 0; i < index_pachet; i++)
		aux = aux->next;
	cout << "The length of deck " << index_pachet << " is " << aux->nr_carti << ".\n";
}

void SHUFFLE_DECK(jucator& om)
{
	int index_pachet;
	cout << "Index pachet: ";
	cin >> index_pachet;
	if (index_pachet > om.nr_pachete - 1 || index_pachet < 0)
	{
		eroare(1, -1);
		return;
	}
	pachet *aux = om.cap;
	for (int i = 0; i < index_pachet; i++)
		aux = aux->next;
	carte* carte_curenta = aux->elemente;
	for (int i = 0; i < aux->nr_carti / 2; i++)
		carte_curenta = carte_curenta->next;
	carte_curenta->next->prev=0;
	aux->elemente->prev = aux->ultima;
	aux->ultima->next = aux->elemente;
	aux->elemente = carte_curenta->next;
	carte_curenta->next = 0;
	aux->ultima = carte_curenta;
	cout << "The deck " << index_pachet << " was succesfully shuffled.\n";
}


void MERGE_DECKS(jucator& om) {
	int index1, index2;
	cout << "Index 1 :";
	cin >> index1;
	cout << "Index 2 :";
	cin >> index2;
	if (index1<0 || index2<0 || index1>om.nr_pachete - 1 || index2>om.nr_pachete - 1)
	{
		eroare(1, -1);
		return;
	}
	else
	{
		pachet *p1 = om.cap;
		pachet* p2 = om.cap;
		for (int i = 0; i < index1; i++)
			p1 = p1->next;
		for (int i = 0; i < index2; i++)
			p2 = p2->next;
		carte* e1 = p1->elemente;
		carte* e2 = p2->elemente;
		pachet* nou=0;
		nou = new pachet;
		if (nou == 0)
		{
			cout << "eroare cu memorie!";
			return;
		}
		if (nou)
		{
			nou->elemente = 0;
			nou->ultima = 0;
		}
		
		nou->nr_carti = p1->nr_carti + p2->nr_carti;
		while (e2 && e1)
		{
			inserareDreapta(nou->ultima, e1->face);
			if (nou->elemente == 0)
				nou->elemente = nou->ultima;
			inserareDreapta(nou->ultima, e2->face);
			e1 = e1->next;
			e2 = e2->next;
		}
		while (e1)
		{
			inserareDreapta(nou->ultima, e1->face);
			e1 = e1->next;
		}
		while (e2)
		{
			inserareDreapta(nou->ultima, e2->face);
			e2 = e2->next;
		}
		if(nou->ultima)
			nou->ultima->next = 0;
		if (index1 > index2)
		{
			DEL_DECK(om, index1, 0);
			DEL_DECK(om, index2, 0);
		}
		else
		{
			DEL_DECK(om, index2, 0);
			DEL_DECK(om, index1, 0);
		}
		if (om.cap == 0)
		{
			om.cap = nou;
			om.cap->next = 0;
			om.cap->prev = 0;
			om.ultimul = nou;
			om.nr_pachete++;

		}
		else
		{			
			++om.nr_pachete;
			if (om.nr_pachete == 2)
				om.cap->next = nou;
			nou->prev = om.ultimul;
			om.ultimul->next = nou;
			om.ultimul = nou;
		}
		afisareCarte(nou->elemente);
	}	
	cout << "the deck " << index1 << " and the deck " << index2 << " were successfully merged.\n";
}




void inserareStanga(carte*& cap, info val) 
{
	carte* nod_nou = new carte;
	nod_nou->face = val;
	nod_nou->prev = NULL;
	nod_nou->next = cap;
	if (cap != NULL) {
		cap->prev = nod_nou;
	}
	cap = nod_nou;
}


void inserareDreapta(carte*& ultima, info val)
{
	if (ultima == 0)
	{
		ultima = new carte;
		ultima->next = ultima->prev = 0;
		ultima->face = val;
	}
	else
	{
		carte* p = 0;
		p = new carte;
		p->face = val;
		p->next = 0;
		p->prev = ultima;
		ultima->next = p;
		ultima = p;
	}
}
void inversare_pachet(pachet* &p) {
	
		if (!p || !p->elemente) return; 
		carte* current = p->elemente;
		carte* temp = nullptr;
		while (current != nullptr) {
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;
			current = current->prev;
		}
		if (temp != nullptr) {
			p->elemente = temp->prev;  
		}
		carte* aux = p->elemente;
		while (aux && aux->next)
		{
			aux = aux->next;
		}
		p->ultima = aux;
}

void REVERSE_DECK(jucator &om) {
	int index_pachet;
	cout << "Index: ";
	cin >> index_pachet;
	if (index_pachet > om.nr_pachete - 1 || index_pachet < 0)
	{
		eroare(1, -1);
		return;
	}
	pachet* aux = om.cap;
	for (int i = 0; i < index_pachet; i++)
		aux = aux->next;
	inversare_pachet(aux);
	cout << "The deck " << index_pachet << " was succesfully reversed.\n";
}

void SPLIT_DECK(jucator& om)
{
	int index_pachet, index_carte;
	cout << "Index pachet: ";
	cin >> index_pachet;
	if (index_pachet > om.nr_pachete - 1 || index_pachet < 0)
	{
		eroare(1, -1);
		return;
	}
	pachet* aux = om.cap;
	for (int i = 0; i < index_pachet; i++)
		aux = aux->next;
	cout << "Index carte: ";
	cin >> index_carte;
	if (aux->nr_carti - 1 < index_carte || index_carte < 0)
	{
		eroare(2, index_pachet);
		return;
	}
	if (index_carte == 0 || index_carte == aux->nr_carti )
	{
		cout << "The deck " << index_pachet << " was succesfully split by index " << index_carte << ".\n";
		return;
	}
	pachet* nou = 0;
	nou = new pachet;
	if (nou == 0)
	{
		cout << "eroare la alocarea memoriei!";
		return;
	}
	carte* crt_carte = aux->elemente;
	for (int i = 1; i < index_carte; i++)
	{
		crt_carte = crt_carte->next;
	}
	nou->elemente = crt_carte->next;
	crt_carte->next = 0;
	nou->ultima = aux->ultima;
	aux->ultima = crt_carte;
	nou->elemente->prev = 0;
	nou->nr_carti = aux->nr_carti - index_carte;
	aux->nr_carti = index_carte;
	nou->next = aux->next;
	if (nou->next)
	{
		nou->next->prev = nou;
	}
	nou->prev = aux;
	if(aux)
		aux->next = nou;
	++om.nr_pachete;
	cout << "The deck " << index_pachet << " was succesfully split by index " << index_carte << ".\n";
}

int prioritate_string(char a[])
{
	if (strcmp(a, "PICA") == 0)
		return 4;
	if (strcmp(a, "CUPA") == 0)
		return 3;
	if (strcmp(a, "CARO") == 0)
		return 2;
	if (strcmp(a, "TREFLA") == 0)
		return 1;
	return 0;
}

bool prioritate(info x, info z)
{
	if (x.val > z.val)
		return true;
	else if (x.val < z.val)
		return false;
	else
	{
		if (prioritate_string(x.simbol) > prioritate_string(z.simbol))
			return true;
	}
	return false;
}

void SORT_DECK(jucator& om)
{	
	int index_pachet;
	cout << "Index: ";
	cin >> index_pachet;
	if (index_pachet > om.nr_pachete - 1 || index_pachet < 0)
	{
		eroare(1, -1);
		return;
	}
	pachet* aux = om.cap;
	for (int i = 0; i < index_pachet; i++)
		aux = aux->next;
	if (aux->nr_carti == 1)
	{
		cout<< "The deck " << index_pachet << " was successfully sorted.\n";
		return;
	}
	carte* current;
	bool swapped = true;
	while (swapped) {
		swapped = false;
		current = aux->elemente;
		while (current->next) 
		{
			if (prioritate(current->face, current->next->face) )
			{
				info auxiliar = current->face;
				current->face = current->next->face;
				current->next->face = auxiliar;
				swapped = true;
			}
			else {
				current = current->next;
			}
		}
	}
	cout << "The deck " << index_pachet << " was successfully sorted.\n";
	
}