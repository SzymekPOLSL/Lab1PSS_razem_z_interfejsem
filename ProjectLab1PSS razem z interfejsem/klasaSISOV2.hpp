#include <iostream>
#pragma once

class SISO {
public:
    virtual ~SISO();
    //Metoda czysto wirtualna, zwraca próbkê wyjœcia
    virtual double Symuluj(double s_u) = 0;
};