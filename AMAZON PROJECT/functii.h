#pragma once

struct info {///informatia stocata pe o carte
	int val;
	char simbol[8];
};

struct carte {//structura carte, lista dublu inlantuita ce contine cartiel dintr-un pachet
	info face;
	carte* prev, * next;
};

struct pachet {//pachetul, ce contine numarul de carti din el si pointerul catre prima carte din pachet
	int nr_carti;
	carte* elemente;
	carte* ultima;
	pachet* prev, * next;///precum si legatura dintre pachetul curent si celelalte, tot fiind stocate intr-o lista dublu inlantuita
};

struct jucator {
	pachet* cap;///primul pachet de carti
	pachet* ultimul;///ultimul pachet
	int nr_pachete;//nr pachete
};
void initPachet(pachet*& cap);
void initJucator(jucator& om);
void initCarte(carte*& cards);//initializeaza cartile dintr-un pachet
int isValid(info x); //valideaza datele de pe fiecare carte
void afisareCarte(carte* cap);
void menu(void);
void eroare(int, int);
void ADD_DECK(jucator& om);
void SHOW_DECK(jucator om, int x);
void inserareStanga(carte*& cap, info val);
void SHOW_All(jucator om);
void EXIT(jucator& om);
void DEL_CARD(jucator &om);
void DEL_DECK(jucator& om, int n, int afis);
void ADD_CARDS(jucator& om);
void DECK_NUMBER(jucator om);
void DECK_LEN(jucator om);
void SHUFFLE_DECK(jucator& om);
void MERGE_DECKS(jucator& om);
void inserareDreapta(carte*& ultima, info val);
void REVERSE_DECK(jucator &om);
void inversare_pachet(pachet*& p);
void SPLIT_DECK(jucator& om);
void SORT_DECK(jucator& om);
bool prioritate(info x, info z);