#include "klient.h"
#include <fstream>
using namespace std;

std::vector<Klient> Klient::klienci;

string Klient::wyswietlPlec() const
{
    if (plec == Plec::Mezczyzna) {
        return "Mezczyzna";
    } else if (plec == Plec::Kobieta) {
        return "Kobieta";
    }
    return "";
}

Klient::Klient(std::string imie, std::string nazwisko, std::string adres, Plec plec)
    :imie(imie), nazwisko(nazwisko), adres(adres), plec(plec)
{
    klienci.push_back(*this); // bez tego nie działa zapis
}


void Klient::wyswietlKlienta()
{
    cout << "Imie: " << imie << endl
         << " Nazwisko: " << nazwisko << endl
         << " Adres: " << adres << endl
         << " Plec: " << wyswietlPlec() << endl;
}

void Klient::edytujKlienta(std::string imie, std::string nazwisko, std::string adres, Plec plec)
{
    if (!imie.empty())
        this->imie = imie;
    if (!nazwisko.empty())
        this->nazwisko = nazwisko;
    if (!adres.empty())
        this->adres = adres;
    if (plec == Plec::Mezczyzna || plec == Plec::Kobieta)
        this->plec = plec;
}

void Klient::zapiszPlik()
{
    ofstream plik("klienci.txt");
    if (plik.is_open()){
        for (const auto& klient : klienci){
            plik << klient.imie << " "
                 << klient.nazwisko << " "
                 << klient.adres << " "
                 << klient.wyswietlPlec() << "\n";
        }

        plik.close();
    }

    ofstream plikBinarny("klienciBin.txt", ios_base::out|ios_base::binary);


    if(plikBinarny.is_open()){
        for (const auto& klient : klienci)
            plikBinarny.write(reinterpret_cast<const char*>(&klient), sizeof(Klient));
    }

    plikBinarny.close();
}

void Klient::dodajZamowienie(Zamowienie& zamowienie)
{
    zamowienia.push_back(zamowienie);
}

void Klient::wyswietlZamowienia()
{
    int i = 0;
    std::cout << "Zamowienia dla klienta: " << imie << " " << nazwisko << std::endl;
    for (auto& zamowienie : zamowienia) {
        cout << "[" << i << "]";
        zamowienie.wyswietlZamowienie();
        i++;
        std::cout << "---------------------" << std::endl;
    }
}

void Klient::edytujZamowienie(Zamowienie &noweZamowienie, unsigned int indeks)
{
    if (indeks < zamowienia.size()){
        zamowienia[indeks] = noweZamowienie;
        cout << "Zamowienie zostalo zaktualizowane" << endl;;
    }else
        cout << "Blad podczas aktualizowania" << endl;
}
