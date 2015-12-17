#ifndef FIREBALL_H
#define FIREBALL_H


#include "Personaje.h"
#include "Jugador.h"
#include <stdlib.h>
#include <list>

class Jugador;

class Fireball : public Personaje
{
    public:
        Jugador* jugador;
        Fireball(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Fireball();
        void logica();
    protected:
    private:
};

#endif // ENEMIGO_H
