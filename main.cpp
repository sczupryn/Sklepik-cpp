#include <iostream>
#include "klient.h"
#include "zamowienie.h"
#include "produkt.h"
#include <vector>

using namespace std;

string aktualnaData(){
    time_t teraz = time(NULL);
    tm* terazPtr = localtime(&teraz);
    string rok = to_string(terazPtr->tm_year + 1900);
    string miesiac = to_string(terazPtr->tm_mon + 1);
    string dzien = to_string(terazPtr->tm_mday);

    if (miesiac.length() == 1)
        miesiac = "0" + miesiac;
    if (dzien.length() == 1)
        dzien = "0" + dzien;

    string data = dzien + "-" + miesiac + "-" + rok;
    return data;
}


bool sprawdzRozmiarKlientow(vector<Klient>& klienci){
    if (klienci.size() == 0){
        cout << "Nie ma zadnego klienta" << endl;
        return false;
    } return true;
}


bool sprawdzPlecKlienta(int plec){
    if (plec == 0 || plec == 1) return true;
    cout << "Wybierz inna plec" << endl;
    return false;
}


bool sprawdzPlatnosci(int platnoscWybor){
    if (platnoscWybor >= 0 && platnoscWybor < 3) return true;
    cout << "Nie ma takiego sposobu platnosci" << endl;
    return false;
}



void dodanieKlienta(vector<Klient>& klienci){
    char wybor;

    do{
        string imie, nazwisko, adres;
        int plec;
        cout << "Dodawanie nowego klienta" << endl;
        cout << "Podaj imie: ";
        cin >> imie;

        cout << "Podaj nazwisko: ";
        cin >> nazwisko;

        cout << "Podaj adres: ";
        cin.ignore();  // Ignorowanie znaku nowej linii z poprzedniego wejścia
        getline(cin, adres);

        cout << "Wybierz plec [0] - Mezczyzna, [1] - Kobieta: ";
        cin >> plec;
        if(!sprawdzPlecKlienta(plec)) break;

        Klient klient(imie, nazwisko, adres, static_cast<Plec>(plec));
        klienci.push_back(klient);

        cout << "Dodac kolejnego klienta? [T/N]: ";
        cin >> wybor;
    } while (wybor == 'T' || wybor == 't');
}


void wyswietlanieKlientow(vector<Klient>& klienci){
    if (!sprawdzRozmiarKlientow(klienci)) return;

    int i = 0;
    for (auto& klient : klienci){
        cout << "[" << i << "] ";
        klient.wyswietlKlienta();
        i++;
        cout << endl;
    }
}


void edycjaKlienta(vector<Klient>& klienci){
    if (!sprawdzRozmiarKlientow(klienci)) return;
    wyswietlanieKlientow(klienci);

    unsigned int indeks;
    cout << "Podaj indeks klienta do edycji: ";
    cin >> indeks;

    if (indeks < klienci.size()){
        string noweImie, noweNazwisko, nowyAdres, nowaMozliwa;
        int nowaPlec = -1;

        cout << "Edytowanie klienta" << endl;
        cout << "Podaj nowe imie: ";
        cin.ignore();
        getline(cin, noweImie);

        cout << "Podaj nowe nazwisko: ";
        getline(cin, noweNazwisko);

        cout << "Podaj nowy adres: ";
        getline(cin, nowyAdres);

        cout << "Wybierz nowa plec [0] - Mezczyzna, [1] - Kobieta: ";
        getline(cin, nowaMozliwa);
        if (!nowaMozliwa.empty()){
            nowaPlec = stoi(nowaMozliwa);
            if(!sprawdzPlecKlienta(nowaPlec)) return;
        }

        if (noweImie.empty() && noweNazwisko.empty() && nowyAdres.empty() && nowaMozliwa.empty()) return;

        Klient& klient = klienci[indeks];  // Referencja do klienta w wektorze
        klient.edytujKlienta(noweImie, noweNazwisko, nowyAdres, static_cast<Plec>(nowaPlec));
    }else
        cout << "Podany indeks jest niepoprawny" << endl;
}


void dodanieProduktu(){
    string nazwa;
    float cena, stawkaVAT;

    char wybor;
    do{
        cout << "Dodawanie nowego produktu" << endl;
        cout << "Podaj nazwe: ";
        cin >> nazwa;

        cout << "Podaj cene: ";
        cin >> cena;

        cout << "Podaj stawke VAT: ";
        cin >> stawkaVAT;

        Produkt nowyProdukt(nazwa, cena, stawkaVAT);
        Produkt::dodajProdukt(nowyProdukt);

        cout << "Dodac kolejny produkt? [T/N]: ";
        cin >> wybor;
    } while (wybor == 'T' || wybor == 't');

    Produkt::wyswietlProdukty();
}


void dodanieZamowienia(Klient& klient){
    string produkt;
    int ilosc;
    Sposob_platnosci platnosc;

    char wybor;
    do{
        Produkt::wyswietlProdukty();
        cout << "Dodawanie nowego zamowienia" << endl;
        cout << "Podaj nazwe produktu: ";
        cin >> produkt;

        cout << "Podaj ilosc: ";
        cin >> ilosc;

        int platnoscWybor;
        cout << "Wybierz sposob platnosci [0 - Przelew, 1 - Karta, 2 - Gotowka]: ";
        cin >> platnoscWybor;
        if(!sprawdzPlatnosci(platnoscWybor)) break;

        platnosc = static_cast<Sposob_platnosci>(platnoscWybor);

        Produkt* wybranyProdukt = nullptr;
        for (auto& p : Produkt::produkty){
            if (p.pobierzNazwe() == produkt){
                wybranyProdukt = &p;
                break;
            }
        }

        if (wybranyProdukt != nullptr){
            Zamowienie noweZamowienie(*wybranyProdukt, ilosc, aktualnaData(), platnosc);
            klient.dodajZamowienie(noweZamowienie);
            cout << "Zamowienie zostalo dodane" << endl;
        }else
            cout << "Nie znaleziono produktu o takiej nazwie" << endl;

        cout << "Dodac kolejne zamowienie? [T/N]: ";
        cin >> wybor;
    } while (wybor == 'T' || wybor == 't');

    klient.wyswietlZamowienia();
}


void edycjaZamowienia(Klient& klient, unsigned int indeks){
    if (indeks < klient.zamowienia.size()){
        int ilosc;
        Sposob_platnosci platnosc;
        cout << "Edytowanie zamowienia" << endl;
        cout << "Podaj nowa ilosc: ";
        cin >> ilosc;

        int platnoscWybor;
        cout << "Wybierz sposob platnosci [0 - Przelew, 1 - Karta, 2 - Gotowka]: ";
        cin >> platnoscWybor;
        if(!sprawdzPlatnosci(platnoscWybor)) return;
        platnosc = static_cast<Sposob_platnosci>(platnoscWybor);

        Zamowienie noweZamowienie(klient.zamowienia[indeks].produkt, ilosc, aktualnaData(), platnosc);
        klient.edytujZamowienie(noweZamowienie, indeks);
    }else
        cout << "Bledny indeks" << endl;

}


void wyborKlienta(vector<Klient>& klienci){
    if (!sprawdzRozmiarKlientow(klienci)) return;
    // Wybór klienta i jego zamówienia
    int windeks, zam_wybor;
    wyswietlanieKlientow(klienci);

    cout << "Wybierz klienta (indeks): ";
    cin >> windeks;
    if (windeks >= static_cast<int>(klienci.size())){
        cout << "Podany indeks jest niepoprawny" << endl;
        return;
    }

    Klient& klient = klienci[windeks];
    klient.wyswietlZamowienia();

    cout << "[0] - Dodaj zamowienie" << endl
         << "[1] - Edytuj istniejace zamowienie" << endl;
    cin >> zam_wybor;

    switch (zam_wybor){
    case 0:
        dodanieZamowienia(klient);
        break;
    case 1:
        if (klient.zamowienia.size() == 0){
            cout << "Klient nie ma zadnych zamowien" << endl;
            break;
        }
        klient.wyswietlZamowienia();
        unsigned int indeks;
        cout << "Podaj indeks zamowienia do edycji: ";
        cin >> indeks;
        edycjaZamowienia(klient, indeks);
        break;
    default:
        cout << "Zly wybor" << endl;
        break;
    }
}


void menu(){
    cout << "<==========>MENU<==========>" << endl
         << "[0] - Wyjscie" << endl
         << "[1] - Dodaj nowego klienta" << endl
         << "[2] - Edytuj dane klienta" << endl
         << "[3] - Wyswietl klientow" << endl
         << "[4] - Wybierz klienta" << endl
         << "[5] - Dodaj nowy produkt" << endl
         << "<=========================>" << endl;
}


int main()
{
    Produkt::wczytajPlik();
    vector<Klient> klienci;

    int wybor;
    do{
        menu();
        cin >> wybor;
        cout << "-----" << endl;
        switch (wybor){
        case 0:
            break;
        case 1:
            dodanieKlienta(klienci);
            break;
        case 2:
            edycjaKlienta(klienci);
            break;
        case 3:
            wyswietlanieKlientow(klienci);
            break;
        case 4:
            wyborKlienta(klienci);
            break;
        case 5:
            dodanieProduktu();
            break;
        }
    }while (wybor != 0);

    Klient::zapiszPlik();
    Produkt::zapiszPlik();
    Zamowienie::zapiszPlik();
    return 0;
}
