#include "StrategiaStrza³uBota.h"
#pragma once
class KontekstStrategiiBota
{
public:
    KontekstStrategiiBota() { KontekstStrategiiBota(new StrategiaBota_Strza³Losowy()); };
    KontekstStrategiiBota(IStrategiaStrza³uBota* const s) : obecna_strategia(s) {}



    OstatnioTrafionePole* nastêpnyStrza³Bota(char plansza1[10][10], char plansza2[10][10], int x, int y)
    {
        return obecna_strategia->strza³_bota(plansza1, plansza2, x, y);
    }
    // ...

    void zmieñ_strategiê(IStrategiaStrza³uBota* nowa_strategia) {
        cout << "Zmiana strategii!";
        //delete this->obecna_strategia;
        this->obecna_strategia = nowa_strategia;
    }

    IStrategiaStrza³uBota *obecna_strategia;
    
};
