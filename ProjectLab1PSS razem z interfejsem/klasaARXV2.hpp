#include "klasaSISOV2.hpp"
#include <iostream>
#include <vector>
#include <deque>

class ARX : public SISO {
    int s_k;
    double s_varE;

protected:
    std::vector<double> s_paramA, s_paramB;
    std::deque<double> s_u, s_y;

public:
    ARX();
    ARX(std::vector<double> nparamA, std::vector<double> nparamB, int nk, double nvarE);
    ~ARX();

    void wyswietlParametry();
    void aktualizujWielomianyAB(std::vector <double> &wielomian1, std::vector <double> &wielomian2);
    void aktualizujParametr(int parametr);
    void aktualizujParametr(double parametr);
    double Symuluj(double s_u);
};