#include "StrategiaStrzałuBota.h"
#pragma once
class KontekstStrategiiBota
{
public:
    KontekstStrategiiBota() { KontekstStrategiiBota(new StrategiaBota_StrzałLosowy()); };
    KontekstStrategiiBota(IStrategiaStrzałuBota* const s) : obecna_strategia(s) {}



    OstatnioTrafionePole* następnyStrzałBota(char plansza1[10][10], char plansza2[10][10], int x, int y)
    {
        return obecna_strategia->strzał_bota(plansza1, plansza2, x, y);
    }
    // ...

    void zmień_strategię(IStrategiaStrzałuBota* nowa_strategia) {
        cout << "Zmiana strategii!";
        //delete this->obecna_strategia;
        this->obecna_strategia = nowa_strategia;
    }

    IStrategiaStrzałuBota *obecna_strategia;
    
};
