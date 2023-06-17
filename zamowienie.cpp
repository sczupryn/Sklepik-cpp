#include "zamowienie.h"

std::vector<Zamowienie> Zamowienie::zamowienia;

float Zamowienie::obliczWartoscCalkowita()
{
    float wartoscNetto = produkt.pobierzCene() * ilosc;
    float vat = wartoscNetto * (produkt.pobierzVAT() / 100);
    return wartoscNetto + vat;
}

std::string Zamowienie::wyswietlPlatnosc(Sposob_platnosci sposob_platnosci)
{
    switch(sposob_platnosci){
    case Sposob_platnosci::Gotowka:
        return "Gotowka";
    case Sposob_platnosci::Karta:
        return "Karta";
    case Sposob_platnosci::Przelew:
        return "Przelew";
    default:
        return "Blad";
    }
}

Zamowienie::Zamowienie(Produkt& produkt, int ilosc, std::string data, Sposob_platnosci sposob_platnosci)
    :ilosc(ilosc), data(data), sposob_platnosci(sposob_platnosci), produkt(produkt)
{
    zamowienia.push_back(*this);
}

void Zamowienie::wyswietlZamowienie()
{
    std::cout << "Produkt: " << produkt.pobierzNazwe() << std::endl;
    std::cout << "Ilosc: " << ilosc << std::endl;
    std::cout << "Cena: " << produkt.pobierzCene() << std::endl;
    std::cout << "Stawka VAT: " << produkt.pobierzVAT() << std::endl;
    std::cout << "Data zamowienia: " << data << std::endl;
    std::cout << "Wartosc calkowita: " << obliczWartoscCalkowita() << std::endl;
    std::cout << "Sposob platnosci: " << wyswietlPlatnosc(sposob_platnosci) << std::endl;
}

void Zamowienie::zapiszPlik()
{
    std::ofstream plik("zamowienia.txt");
    if (plik.is_open()) {
        for (const auto& zamowienie : zamowienia) {
            plik << zamowienie.produkt.pobierzNazwe() << " "
                 << zamowienie.ilosc << " "
                 << zamowienie.data << " "
                 << zamowienie.sposob_platnosci << "\n";
        }

        plik.close();
    }
    std::ofstream plikBin("zamowieniaBin.txt", std::ios::binary);
    if (plikBin.is_open()) {
        for (const auto& zamowienie : zamowienia) {
            plikBin.write(reinterpret_cast<const char*>(&zamowienie), sizeof(Zamowienie));
        }

        plikBin.close();
    }
}
