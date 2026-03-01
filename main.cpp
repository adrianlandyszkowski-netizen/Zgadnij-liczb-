#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

string imiona[5];
int proby[5];
string poziomy[5];
int liczbaWynikow = 0;

string zaMale[3] = {
    "Za mała liczba! Spróbuj jeszcze raz.",
    "Troche wieksza liczba.",
    "To za mało."
};

string zaDuze[3] = {
    "Za duża liczba! Spróbuj ponownie.",
    "Troszkę mniej!",
    "Za wysoko! Celuj niżej."
};

void pokazTop5() {
    if (liczbaWynikow == 0) {
        cout << "\nBrak zapisanych wyników.\n";
        return;
    }

    cout << "\n=-=-=-=-= TOP 5 =-=-=-=-=\n";
    for (int i = 0; i < liczbaWynikow; i++) {
        cout << i + 1 << ". ";
        cout << "Imie: " << imiona[i]
             << " | Próby: " << proby[i]
             << " | Poziom: " << poziomy[i]
             << endl;
    }

    cout << "\nWciśnij ENTER, aby wrócic do menu...";
    cin.ignore();
    cin.get();
}

void dodajWynik(string imie, int liczbaProb, string poziom) {

    if (liczbaWynikow < 5) {
        imiona[liczbaWynikow] = imie;
        proby[liczbaWynikow] = liczbaProb;
        poziomy[liczbaWynikow] = poziom;
        liczbaWynikow++;
    } else {
        int najgorszy = 0;
        for (int i = 1; i < 5; i++) {
            if (proby[i] > proby[najgorszy]) {
                najgorszy = i;
            }
        }

        if (liczbaProb < proby[najgorszy]) {
            imiona[najgorszy] = imie;
            proby[najgorszy] = liczbaProb;
            poziomy[najgorszy] = poziom;
        }
    }
}

void nowaGra() {

    int wybor;
    int maxZakres;
    string poziom;

    cout << "\nWybierz poziom trudnosci:\n";
    cout << "1 - Latwy (1-50)\n";
    cout << "2 - Sredni (1-100)\n";
    cout << "3 - Trudny (1-250)\n";
    cout << "Twoj wybor: ";
    cin >> wybor;

    if (wybor == 1) {
        maxZakres = 50;
        poziom = "Łatwy";
    } else if (wybor == 2) {
        maxZakres = 100;
        poziom = "Średni";
    } else if (wybor == 3) {
        maxZakres = 250;
        poziom = "Trudny";
    } else {
        cout << "Błędny wybór.\n";
        return;
    }

    int wylosowana = rand() % maxZakres + 1;
    int licznikProb = 0;
    int liczba;

    cout << "\nZgadnij liczbę od 1 do " << maxZakres << endl;

    while (true) {
        licznikProb++;
        cout << "\nPróba nr: " << licznikProb << endl;
        cout << "Podaj liczbę: ";
        cin >> liczba;

        if (liczba < wylosowana) {
            cout << zaMale[rand() % 3] << endl;
        } 
        else if (liczba > wylosowana) {
            cout << zaDuze[rand() % 3] << endl;
        } 
        else {
            cout << "\nBrawo! Zgadłes w " << licznikProb << " próbach.\n";
            cout << "Podaj swoje imię: ";

            string imie;
            cin >> imie;

            dodajWynik(imie, licznikProb, poziom);
            break;
        }
    }
}

int main() {

    srand(time(NULL));

    char opcja;

    do {
        cout << "\n=-=-=-=-= MENU =-=-=-=-=\n";

        cout << "Wpisz a - Aby rozpocząć nową gre\n";

        if (liczbaWynikow > 0) {
            cout << "Wpisz b - Aby pokazać TOP5\n";
        }

        cout << "Wpisz x - Aby wyjść\n";
        cout << "Wybierz opcje: ";
        cin >> opcja;

        if (opcja == 'a') {
            nowaGra();
        } else if (opcja == 'b' && liczbaWynikow > 0) {
            pokazTop5();
        } else if (opcja == 'x') {
            cout << "Koniec programu.\n";
        } else {
            cout << "Niepoprawna opcja.\n";
        }

    } while (opcja != 'x');

    return 0;
}
