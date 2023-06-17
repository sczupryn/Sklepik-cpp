#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H
#include <iostream>
#include "produkt.h"
#include <ctime>

enum Sposob_platnosci{
    Przelew,
    Karta,
    Gotowka
};

class Zamowienie
{
private:
    int ilosc;
    std::string data;
    Sposob_platnosci sposob_platnosci;
    float obliczWartoscCalkowita();
    std::string wyswietlPlatnosc(Sposob_platnosci sposob_platnosci);

public:
    Produkt produkt;
    static std::vector<Zamowienie> zamowienia;
    Zamowienie(Produkt& produkt, int ilosc, std::string data, Sposob_platnosci sposob_platnosci);
    void wyswietlZamowienie();
    static void zapiszPlik();
};

#endif // ZAMOWIENIE_H
