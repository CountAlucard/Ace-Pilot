#include "Proyectil.h"
#include <fstream>

Proyectil::Proyectil(list<Entidad*>* entidades, SDL_Renderer* renderer, int x, int y, string state)
{
    tipo = "Proyectil";
    this->entidades = entidades;
    this->renderer = renderer;
    this->state = state;
    texture = IMG_LoadTexture(renderer,"Disparo.png");
    rect.x=x;
    rect.y=y;
    rect.w=64;
    rect.h=64;

    for(list<Entidad*>::iterator e=entidades->begin(); e!=entidades->end(); e++)
    {
        if((*e)->tipo=="Jugador")
        {
            jugador = (Jugador*)*e;
        }
    }
}

Proyectil::~Proyectil()
{
    //dtor
}

void Proyectil::dibujar()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Proyectil::logica()
{
    int velocity = 3;

    if(state=="left")
    {
        rect.y-=velocity;
    }



    for(list<Entidad*>::iterator e=entidades->begin(); e!=entidades->end(); e++)
    {
        if((*e)->tipo=="Enemigo")
        {
            Enemigo* enemigo = (Enemigo*)(*e);
            if(colision(rect,enemigo->rect))
            {
                enemigo->delete_flag = true;
                this->delete_flag = true;
                cout<<"Colision con proyectil"<<endl;

                jugador->puntos+=10;
            }
        }
        if((*e)->tipo=="Meteorito2")
        {
            Meteorito2* meteorito2 = (Meteorito2*)(*e);
            if(colision(rect,meteorito2->rect))
            {
                meteorito2->delete_flag = true;
                this->delete_flag = true;
                cout<<"Colision con proyectil"<<endl;

                jugador->puntos+=50;
            }
        }
        if((*e)->tipo=="Meteorito3")
        {
            Meteorito3* meteorito3 = (Meteorito3*)(*e);
            if(colision(rect,meteorito3->rect))
            {
                meteorito3->delete_flag = true;
                this->delete_flag = true;
                jugador->vidas++; //---------------------   + 1 VIDA----
                cout<<"Colision con proyectil"<<endl;

                jugador->puntos+=500;
            }
        }
    }

    if(rect.y<0)
    {
        this->delete_flag=true;
        cout<<"Borrando bala"<<endl;
    }

}





