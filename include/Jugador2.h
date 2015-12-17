#ifndef JUGADOR2_H
#define JUGADOR2_H

#include <list>
#include "Personaje.h"
#include "Proyectil.h"

class Enemigo;

class Jugador2 : public Personaje
{
    public:
        Enemigo* enemigo;
        int proyectil_cooldown;
        Jugador2(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Jugador2();
        void logica();
        void logicaPush();
        void dibujar();
    protected:
    private:
};

#endif // JUGADOR_H
