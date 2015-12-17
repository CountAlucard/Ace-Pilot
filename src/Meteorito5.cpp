#include "Meteorito5.h"

Meteorito5::Meteorito5(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Meteorito5";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Imagenes/FireMeteor1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Imagenes/FireMeteor1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Imagenes/FireMeteor1.png"));

    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    x = 1280;
    y = 100+rand()%1000;;
    rect.x=x;
    rect.y=y;
    //rect.w=w;
    //rect.h=h;

    velocity=.5;
    animation_velocity=20;

    current_texture=0;

    state="down";
    vidas=1;

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

Meteorito5::~Meteorito5()
{
    //dtor
}

void Meteorito5::logica()
{
        x-=velocity;

    if(colision(rect,jugador->rect))
    {
        jugador->vidas--;
        this->delete_flag= true;
        cout<<"Colision con jugador"<<endl;
    }

    if(frames%animation_velocity==0)
    {
        current_texture++;
        if(current_texture>=textures[state].size())
            current_texture=0;
    }

    frames++;
}
