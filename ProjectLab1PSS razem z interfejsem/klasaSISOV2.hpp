#include <iostream>
#pragma once

class SISO {
public:
    virtual ~SISO();
    //Metoda czysto wirtualna, zwraca pr�bk� wyj�cia
    virtual double Symuluj(double s_u) = 0;
};