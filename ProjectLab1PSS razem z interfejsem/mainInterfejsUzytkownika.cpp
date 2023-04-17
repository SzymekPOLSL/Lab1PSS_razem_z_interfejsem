#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <locale>
#include "klasaARXV2.hpp"
#include "klasaSISOV2.hpp"

//W pierwszej cz�ci przechodzimy przez zadane parametry obiektu.
//W drugiej mo�liwa jest zmiana parametr�w obiektu oraz ponowna symulacja.

//Zapis wyj�cia modelu ARX do pliku
void zapiszDoPliku(std::vector<double> dane);

//Uzupe�nienie wsp�czynnik�w wielomianu
void uzupelnijWsplWielomianu(std::vector<double> &wielomian);

int main() {
    std::locale::global(std::locale("pl_PL"));
    std::wcout.imbue(std::locale());
    std::vector<double> wyjscie_y;
    std::vector<double> paramA;
    std::vector<double> paramB;
    int k;
    double varE = 0;

    std::cout << "Uzupe�nij wsp�czynniki wielomianu A." << std::endl;
    uzupelnijWsplWielomianu(paramA);
    std::cout << "Uzupe�nij wsp�czynniki wielomianu B." << std::endl;
    uzupelnijWsplWielomianu(paramB);

    do {
        std::cout << "Podaj warto�� op�nienia (warto�� >=0): \n";
        std::cin >> k;
    } while (k < 0);

    //Stworzenie obiektu klasy ARX
    ARX arx = { paramA, paramB, k, varE};
    arx.wyswietlParametry();

    //Symulacja dla zadanej liczby pr�bek i wej�cia w postaci skoku jednostkowego
    for (int i = 0; i < 25; i++)
    {   
        if (i == 0){
            double y_i = arx.Symuluj(0.0);
            std::cout << "wyj�cie: " << y_i << std::endl;
            wyjscie_y.push_back(y_i);
        }
        else {
            double y_i = arx.Symuluj(1.0);
            std::cout << "wyj�cie: " << y_i << std::endl;
            wyjscie_y.push_back(y_i);
        }
    }

    zapiszDoPliku(wyjscie_y);
    arx.wyswietlParametry();

    char wybor;
    do {
        std::cout << "Czy chcia�by� zmieni� parametr obiektu? \n";
        std::cout << "k - zmiana op�nienia \n";
        std::cout << "v - zmiana wariancji \n";
        std::cout << "w - zmiana wielomianu \n";
        std::cout << "x - wy�wietl parametry \n";
        std::cout << "s - symuluj obiekt \n";
        std::cout << "t - wyjd� z programu \n";
        std::cin >> wybor;

        //Zmiana parametr�w obiektu
        if (wybor == 'k')
        {
            //Opoznienie
            arx.aktualizujParametr(k);
        }
        else if (wybor == 'v')
        {
            //Wariancja
            arx.aktualizujParametr(varE);
        }
        else if (wybor == 'w')
        {
            //Wybrany wielomiany
            arx.aktualizujWielomianyAB(paramA, paramB);
        }
        else if (wybor == 'x')
        {
            arx.wyswietlParametry();
        }
        else if (wybor == 's')
        {
            //Symulacja dla zadanej liczby pr�bek i wej�cia w postaci skoku jednostkowego
            for (int i = 0; i < 25; i++)
            {
                if (i == 0) {
                    double y_i = arx.Symuluj(0.0);
                    std::cout << "wyj�cie: " << y_i << std::endl;
                    wyjscie_y.push_back(y_i);
                }
                else {
                    double y_i = arx.Symuluj(1.0);
                    std::cout << "wyj�cie: " << y_i << std::endl;
                    wyjscie_y.push_back(y_i);
                }
            }
        }
        else if (wybor == 't')
        {
            std::cout << "Wychodz� z programu! \n";
        }
        else
        {
            std::cout << "B��dny wyb�r! \n";
        }
    } while (wybor != 't');





    return 0;
}

void zapiszDoPliku(std::vector<double> dane) {

    std::ofstream plik("Dane.txt", std::ios::out);

    if (plik.is_open())
    {
        std::cout << "Nast�pi zapis danych do pliku!" << std::endl;

        // Zapisanie danych do pliku
        for (const auto& d : dane)
        {
            plik << d << "\n"; // Zapisanie danych, oddzielaj�c je znakiem nowej linii
        }

        // Zamkni�cie pliku
        plik.close();
    }
    else
    {
        std::cout << "Nie uda�o si� otworzy� pliku do zapisu!" << std::endl;
    }

}

void uzupelnijWsplWielomianu(std::vector<double> &wielomian) {
    
    int wybor = -1;
    int i = 1;
    double wartosc;

    //Uzupe�nianie wsp�czynnik�w wielomianu do momentu, a� u�ytkownik zako�czy proces.
    do {
        std::cout << "Podaj warto�� wsp�czynnika wielomianu. Numer wsp�czynnika: " << i << " \n";
        std::cin >> wartosc;
        wielomian.push_back(wartosc);
        i++;

        std::cout << "Aby zako�czy� dodawanie wsp�czynnik�w wpisz '0', aby kontynuowa� wpisz '1'" << std::endl;
        std::cin >> wybor;

    } while (wybor != 0);

}