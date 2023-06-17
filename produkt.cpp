#include "produkt.h"

std::vector<Produkt> Produkt::produkty;

Produkt::Produkt(const std::string& nazwa, float cena, float stawka_vat)
    : nazwa(nazwa), cena(cena), stawka_vat(stawka_vat){ }

std::string Produkt::pobierzNazwe() const
{
    return nazwa;
}

float Produkt::pobierzCene() const
{
    return cena;
}

float Produkt::pobierzVAT() const
{
    return stawka_vat;
}

void Produkt::dodajProdukt(const Produkt& produkt)
{
    produkty.push_back(produkt);
}

void Produkt::edytujProdukt(const std::string& nazwa, float cena, float stawka_vat)
{
    if (!nazwa.empty())
        this->nazwa = nazwa;
    if (cena != 0)
        this->cena = cena;
    if (stawka_vat != 0)
        this->stawka_vat = stawka_vat;
}

void Produkt::wyswietlProdukty()
{
    std::cout << "Lista wszystkich produktow:" << std::endl;
    for (const auto& produkt : produkty) {
        std::cout << "Nazwa: " << produkt.pobierzNazwe() << std::endl;
        std::cout << "Cena: " << produkt.pobierzCene() << std::endl;
        std::cout << "Stawka VAT: " << produkt.pobierzVAT() << std::endl;
        std::cout << "---------------------" << std::endl;
    }
}

void Produkt::wczytajPlik()
{
    std::ifstream plik("produkty.txt");
    if (plik.is_open()){
        produkty.clear();

        std::string nazwa;
        float cena, stawka_vat;
        while (plik >> nazwa >> cena >> stawka_vat){
            dodajProdukt(Produkt(nazwa, cena, stawka_vat));
        }

        plik.close();
        //std::cout << "Produkty zostaly wczytane z pliku." << std::endl;
    } //else
        //std::cout << "Blad podczas otwierania pliku." << std::endl;
}

void Produkt::zapiszPlik()
{
    std::ofstream plik("produkty.txt");
    if (plik.is_open()) {
        for (const auto& produkt : produkty) {
            plik << produkt.pobierzNazwe() << " "
                 << produkt.pobierzCene() << " "
                 << produkt.pobierzVAT() << "\n";
        }

        plik.close();
    }
}
