#include "klasaSISOV2.hpp"
#include "klasaARXV2.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <numeric>

void print(std::vector<double> const& input);

ARX::ARX() : s_paramA(1.0), s_paramB(0), s_k(0), s_varE(0.0), s_u(0.0), s_y(0.0) {}
ARX::ARX(std::vector<double> nparamA, std::vector<double> nparamB, int nk, double nvarE) : s_paramA(nparamA), s_paramB(nparamB), s_k(nk), s_varE(nvarE) {
    this->s_u.resize((int)s_paramB.size() + s_k, 0);
    this->s_y.resize((int)s_paramA.size(), 0);
}
ARX::~ARX() {}

void ARX::wyswietlParametry() {
    std::cout << "Oto aktualnie wybrane parametry modelu ARX: \n";
    std::cout << "dA = " << this->s_paramA.size() << ", dB = " << this->s_paramB.size()+s_k-1 << std::endl;
    std::cout << "s_k = " << this->s_k << ", s_varE = " << this->s_varE << std::endl;
    std::cout << "Param_A: ";
    print(this->s_paramA);
    std::cout << "Param_B: ";
    print(this->s_paramB);
    std::cout << std::endl;
}

//Zmiana parametr�w powoduje wyzerowanie kolejki wyj�cia i wej�cia!
void ARX::aktualizujWielomianyAB(std::vector <double> &wielomian1, std::vector <double> &wielomian2) {
    //Usuni�cie aktualnych wsp�czynnik�w
    wielomian1.clear();
    wielomian2.clear();
    int wybor = -1;
    int i = 1;
    double wartosc;

    //Uzupe�nianie nowych wsp�czynnik�w wielomianu do momentu, a� u�ytkownik zako�czy proces.
    do {
        std::cout << "Podaj warto�� nowego wsp�czynnika wielomianu 1. Numer wsp�czynnika: " << i << " \n";
        std::cin >> wartosc;
        wielomian1.push_back(wartosc);
        i++;

        std::cout << "Aby zako�czy� dodawanie wsp�czynnik�w wpisz '0', aby kontynuowa� wpisz '1'" << std::endl;
        std::cin >> wybor;
    } while (wybor != 0);

    wybor = -1;
    i = 1;

    do {
        std::cout << "Podaj warto�� nowego wsp�czynnika wielomianu 2. Numer wsp�czynnika: " << i << " \n";
        std::cin >> wartosc;
        wielomian2.push_back(wartosc);
        i++;

        std::cout << "Aby zako�czy� dodawanie wsp�czynnik�w wpisz '0', aby kontynuowa� wpisz '1'" << std::endl;
        std::cin >> wybor;
    } while (wybor != 0);

    this->s_paramA = wielomian1;
    this->s_paramB = wielomian2;
    s_u.clear();
    s_y.clear();
    this->s_u.resize((int)s_paramB.size() + s_k, 0);
    this->s_y.resize((int)s_paramA.size(), 0);
}

void ARX::aktualizujParametr(int parametr) {
    do {
        std::cout << "Podaj now� warto�� op�nienia (warto�� >= 0): \n";
        std::cin >> parametr;
    } while (parametr < 0);
    this->s_k = parametr;
    s_u.clear();
    s_y.clear();
    this->s_u.resize((int)s_paramB.size() + s_k, 0);
    this->s_y.resize((int)s_paramA.size(), 0);
}

void ARX::aktualizujParametr(double parametr) {
    std::cout << "Podaj now� warto�� wariancji: \n";
    std::cin >> parametr;
    this->s_varE = parametr;
    s_u.clear();
    s_y.clear();
    this->s_u.resize((int)s_paramB.size() + s_k, 0);
    this->s_y.resize((int)s_paramA.size(), 0);
}

double ARX::Symuluj(double u) {
    //Usuni�cie warto�ci z ty�u i dodanie nowego wej�cia
    this->s_u.push_front(u);
    this->s_u.pop_back();
    //Obliczenie warto�ci wyj�cia w i-tej pr�bce
    double a = std::inner_product(this->s_paramB.begin(), this->s_paramB.end(), this->s_u.begin() + s_k, 0.0);
    double b = std::inner_product(this->s_paramA.begin(), this->s_paramA.end(), this->s_y.begin(), 0.0);
    double wynik = a - b;
    //Usuni�cie warto�ci z ty�u i dodanie nowego wyj�cia
    this->s_y.push_front(wynik);
    this->s_y.pop_back();
    return wynik;
}

//Wy�wietlanie wektora
void print(std::vector<double> const& input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}