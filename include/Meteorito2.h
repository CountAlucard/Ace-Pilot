#ifndef METEORITO2_H
#define METEORITO2_H


#include "Personaje.h"
#include "Jugador.h"
#include <stdlib.h>
#include <list>

class Jugador;

class Meteorito2 : public Personaje
{
    public:
        Jugador* jugador;
        Meteorito2(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Meteorito2();
        void logica();
    protected:
    private:
};
#endif // METEORITO2_H
