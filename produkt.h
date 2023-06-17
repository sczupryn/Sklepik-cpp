#ifndef PRODUKT_H
#define PRODUKT_H

#include <iostream>
#include <vector>
#include <fstream>

class Produkt {
private:
    std::string nazwa;
    float cena;
    float stawka_vat;

public:
    static std::vector<Produkt> produkty;
    Produkt(const std::string& nazwa, float cena, float stawka_vat);
    std::string pobierzNazwe() const;
    float pobierzCene() const;
    float pobierzVAT() const;
    static void dodajProdukt(const Produkt& produkt);
    void edytujProdukt(const std::string& nazwa, float cena, float stawka_vat);
    static void wyswietlProdukty();
    static void wczytajPlik();
    static void zapiszPlik();
};

#endif // PRODUKT_H
