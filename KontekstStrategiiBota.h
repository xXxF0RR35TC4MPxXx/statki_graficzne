#include "StrategiaStrza�uBota.h"
#pragma once
class KontekstStrategiiBota
{
public:
    KontekstStrategiiBota() { KontekstStrategiiBota(new StrategiaBota_Strza�Losowy()); };
    KontekstStrategiiBota(IStrategiaStrza�uBota* const s) : obecna_strategia(s) {}



    OstatnioTrafionePole* nast�pnyStrza�Bota(char plansza1[10][10], char plansza2[10][10], int x, int y)
    {
        return obecna_strategia->strza�_bota(plansza1, plansza2, x, y);
    }
    // ...

    void zmie�_strategi�(IStrategiaStrza�uBota* nowa_strategia) {
        cout << "Zmiana strategii!";
        //delete this->obecna_strategia;
        this->obecna_strategia = nowa_strategia;
    }

    IStrategiaStrza�uBota *obecna_strategia;
    
};
