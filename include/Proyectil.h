#ifndef PROJECTIL_H
#define PROJECTIL_H

#include <list>
#include "Entidad.h"
#include "Enemigo.h"
#include "Meteorito2.h"
#include "Meteorito3.h"

using namespace std;

class Jugador;

class Proyectil : public Entidad
{
    public:
        Jugador* jugador;
        SDL_Renderer* renderer;
        list<Entidad*>* entidades;
        SDL_Texture* texture;
        SDL_Rect rect;
        string state;
        Proyectil(list<Entidad*>* entidades,SDL_Renderer* renderer, int x, int y, string state);
        virtual ~Proyectil();
        void dibujar();
        void logica();
    protected:
    private:
};

#endif // PROJECTIL_H
