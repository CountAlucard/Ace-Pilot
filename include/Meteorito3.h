#ifndef METEORITO3_H
#define METEORITO3_H


#include "Personaje.h"
#include "Jugador.h"
#include <stdlib.h>
#include <list>

class Jugador;

class Meteorito3 : public Personaje
{
    public:
        Jugador* jugador;
        Meteorito3(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Meteorito3();
        void logica();
    protected:
    private:
};
#endif // METEORITO3_H
