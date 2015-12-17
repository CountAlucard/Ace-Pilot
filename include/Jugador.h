#ifndef JUGADOR_H
#define JUGADOR_H

#include <list>
#include "Personaje.h"
#include "Proyectil.h"

class Enemigo;

class Jugador : public Personaje
{
    public:
        Enemigo* enemigo;
        Jugador* jugador;
        int proyectil_cooldown;
        Jugador(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Jugador();
        void logica();
        void dibujar();
    protected:
    private:
};

#endif // JUGADOR_H
