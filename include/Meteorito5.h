#ifndef METEORITO5_H
#define METEORITO5_H

#include "Personaje.h"
#include "Jugador.h"
#include <stdlib.h>
#include <list>

class Jugador;

class Meteorito5 : public Personaje
{
    public:
        Jugador* jugador;
        Meteorito5(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Meteorito5();
        void logica();
    protected:
    private:
};
#endif // METEORITO5_H
