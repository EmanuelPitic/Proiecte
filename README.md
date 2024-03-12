
# Simulare joc de cărți

Acest proiect reprezintă o aplicație dezvoltată pentru simularea acțiunilor unui participant la un joc de cărți în grup. În cadrul acestui joc, fiecare jucător primește mai multe pachete de cărți, iar acestea sunt ținute într-o listă dublu înlănțuită. În cadrul fiecărui pachet, cărțile sunt reprezentate tot sub forma unei liste dublu înlănțuite. Fiecare carte are două proprietăți: valoare (în intervalul [1, 14]) și simbol (PICĂ, CUPĂ, CARO, TREFLĂ).

## Comenzi disponibile
- `ADD_DECK <număr_cărți>`: Adaugă un nou pachet de cărți la finalul listei de pachete.
- `DEL_DECK <index_pachet>`: Șterge pachetul cu indexul specificat din lista de pachete.
- `DEL_CARD <index_pachet> <index_carte>`: Șterge cartea cu indexul specificat din pachetul cu indexul specificat.
- `ADD_CARDS <index_pachet> <număr_cărți>`: Adaugă un număr specificat de cărți în pachetul cu indexul specificat.
- `DECK_NUMBER`: Afișează câte pachete de cărți se află în listă.
- `DECK_LEN <index_pachet>`: Afișează lungimea pachetului cu indexul specificat.
- `SHUFFLE_DECK <index_pachet>`: Inversează prima și a doua jumătate a pachetului cu indexul specificat.
- `MERGE_DECKS <index_pachet_1> <index_pachet_2>`: Combină două pachete luând câte o carte din fiecare pachet, rând pe rând.
- `SPLIT_DECK <index_pachet> <index_split>`: Împarte pachetul cu indexul specificat după indexul specificat.
- `REVERSE_DECK <index_pachet>`: Inversează ordinea cărților din pachetul cu indexul specificat.
- `SHOW_DECK <index_pachet>`: Afișează cărțile din pachetul cu indexul specificat.
- `SHOW_ALL`: Afișează toate cărțile din toate pachetele.
- `SORT_DECK <index_pachet>`: Sortează pachetul cu indexul specificat.

## Tratarea erorilor
- `DECK_INDEX_OUT_OF_BOUNDS`: Eroare apărută atunci când indexul pachetului din comandă nu există.
- `CARD_INDEX_OUT_OF_BOUNDS`: Eroare apărută atunci când indexul cărții din comandă nu există.
- `INVALID_CARD`: Eroare apărută dacă se încearcă introducerea unei cărți care nu este validă.
- `INVALID_COMMAND`: Eroare apărută atunci când este introdusă o comandă inexistentă sau atunci când numărul de parametri este incorect.

## Implementare și detalii tehnice
Proiectul este implementat în limbajul C++. Acesta constă din trei fișiere: `amazon v2.cpp`, `functii.h` și `functii.cpp`. Fișierul `amazon v2.cpp` conține funcția `main()` care este punctul de intrare în program. Funcția `main()` apelează funcția `menu()`, care implementează logica jocului. Fișierele `functii.h` și `functii.cpp` conțin definițiile structurilor și funcțiilor necesare funcționării jocului.

## Dificultăți întâmpinate
Una dintre provocările principale în implementarea acestui proiect a fost gestionarea corectă a structurilor de date și manipularea acestora în conformitate cu cerințele jocului. De asemenea, tratarea corectă a erorilor și asigurarea unui cod curat și ușor de înțeles au fost aspecte importante în dezvoltarea acestui proiect.

