#ifndef METEORITO4_H
#define METEORITO4_H


#include "Personaje.h"
#include "Jugador.h"
#include <stdlib.h>
#include <list>

class Jugador;

class Meteorito4 : public Personaje
{
    public:
        Jugador* jugador;
        Meteorito4(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Meteorito4();
        void logica();
    protected:
    private:
};
#endif // METEORITO3_H
