#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

string imiona[5];
int proby[5];
string poziomy[5];
int liczbaWynikow = 0;

string zaMale[3] = {
    "Za mala liczba! Sprobuj jeszcze raz.",
    "Troche wieksza liczba.",
    "To za malo."
};

string zaDuze[3] = {
    "Za duza liczba! Sprobuj ponownie.",
    "Troszke mniej!",
    "Za wysoko! Celuj nizej."
};

void pokazTop5() {
    if (liczbaWynikow == 0) {
        cout << "\nBrak zapisanych wynikow.\n";
        return;
    }

    cout << "\n=-=-=-=-= TOP 5 =-=-=-=-=\n";
    for (int i = 0; i < liczbaWynikow; i++) {
        cout << i + 1 << ". ";
        cout << "Imie: " << imiona[i]
             << " | Proby: " << proby[i]
             << " | Poziom: " << poziomy[i]
             << endl;
    }

    cout << "\nWcisnij ENTER, aby wrocic do menu...";
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

    for (int i = 0; i < liczbaWynikow - 1; i++) {
        for (int j = 0; j < liczbaWynikow - i - 1; j++) {
            if (proby[j] > proby[j + 1]) {
                swap(proby[j], proby[j + 1]);
                swap(imiona[j], imiona[j + 1]);
                swap(poziomy[j], poziomy[j + 1]);
            }
        }
    }
}

void nowaGra() {
    int maxZakres;
    string poziom;
    string input;
    int wybor;

    cout << "\nWybierz poziom trudnosci:\n";
    cout << "1 - Latwy (1-50)\n";
    cout << "2 - Sredni (1-100)\n";
    cout << "3 - Trudny (1-250)\n";
    cout << "Twoj wybor: ";

    getline(cin, input);

    if (input.length() != 1 || (input[0] < '1' || input[0] > '3')) {
        cout << "Podaj tylko jedna cyfre od 1 do 3!\n";
        return;
    }

    wybor = input[0] - '0'; // konwersja znaku na int

    if (wybor == 1) {
        maxZakres = 50;
        poziom = "Latwy";
    } else if (wybor == 2) {
        maxZakres = 100;
        poziom = "Sredni";
    } else if (wybor == 3) {
        maxZakres = 250;
        poziom = "Trudny";
    }

    int wylosowana = rand() % maxZakres + 1;
    int licznikProb = 0;
    int liczba;

    cout << "\nZgadnij liczbe od 1 do " << maxZakres << endl;

    while (true) {
        licznikProb++;
        cout << "\nProba nr: " << licznikProb << endl;
        cout << "Podaj liczbe: ";

        if (!(cin >> liczba)) { // walidacja liczby
            cout << "Podaj poprawna liczbe!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (liczba < wylosowana) {
            cout << zaMale[rand() % 3] << endl;
        } else if (liczba > wylosowana) {
            cout << zaDuze[rand() % 3] << endl;
        } else {
            cout << "\nBrawo! Zgadles w " << licznikProb << " probach.\n";
            cout << "Podaj swoje imie: ";

            string imie;
            cin >> imie;
            cin.ignore(); // czyścimy bufor

            dodajWynik(imie, licznikProb, poziom);
            break;
        }
    }
}

int main() {
    srand(time(NULL));

    string input;
    char opcja;

    do {
        cout << "\n=-=-=-=-= MENU =-=-=-=-=\n";
        cout << "Wpisz 1 - Aby rozpoczac nowa gre\n";
        if (liczbaWynikow > 0) {
            cout << "Wpisz 2 - Aby pokazac TOP5\n";
        }
        cout << "Wpisz 3 - Aby wyjsc\n";
        cout << "Wybierz opcje: ";

        getline(cin, input);

        if (input.length() != 1 || (input[0] < '1' || input[0] > '3')) {
            cout << "Podaj tylko jedna cyfre od 1 do 3!\n";
            continue;
        }

        opcja = input[0];

        if (opcja == '1') {
            nowaGra();
        } else if (opcja == '2' && liczbaWynikow > 0) {
            pokazTop5();
        } else if (opcja == '3') {
            cout << "Koniec programu.\n";
        } else {
            cout << "Niepoprawna opcja.\n";
        }

    } while (opcja != '3');

    return 0;
}
