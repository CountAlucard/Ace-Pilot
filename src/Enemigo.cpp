#include "Enemigo.h"

Enemigo::Enemigo(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Enemigo";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito1.png"));


    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    rect.x=x;
    rect.y=y;
    x = 100+rand()%1000;
    y = 0;

    vidas=1;

    velocity=1;
    animation_velocity=20;

    current_texture=0;

    state="down";

    this->entidades = entidades;

    for(list<Entidad*>::iterator e=entidades->begin();
        e!=entidades->end();
        e++)
    {
        if((*e)->tipo=="Jugador")
        {
            jugador = (Jugador*)*e;
        }
    }
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::logica()
{

        y+=velocity;


    if(colision(rect,jugador->rect))
    {
        jugador->vidas--;

        this->delete_flag= true;
        cout<<"Colision con jugador"<<endl;
    }

    frames++;
}
