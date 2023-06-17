#ifndef KLIENT_H
#define KLIENT_H
#include <iostream>
#include <vector>
#include "zamowienie.h"

enum Plec{
    Mezczyzna,
    Kobieta
};

class Klient
{
private:
    std::string imie;
    std::string nazwisko;
    std::string adres;
    Plec plec;
    std::string wyswietlPlec() const;
public:
    std::vector<Zamowienie> zamowienia;
    static std::vector<Klient> klienci;
    Klient(std::string imie, std::string nazwisko, std::string adres, Plec plec);
    void wyswietlKlienta();
    void edytujKlienta(std::string imie, std::string nazwisko, std::string adres, Plec plec);
    void static zapiszPlik();
    void dodajZamowienie(Zamowienie& zamowienie);
    void wyswietlZamowienia();
    void edytujZamowienie(Zamowienie& noweZamowienie, unsigned int indeks);
};

#endif // KLIENT_H
