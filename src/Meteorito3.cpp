#include "Meteorito3.h"

Meteorito3::Meteorito3(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Meteorito3";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.2.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.2.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.3.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.3.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.4.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.4.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.5.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.5.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.6.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.6.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.7.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.7.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.8.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.8.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.9.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito3.9.png"));


    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    x = 100+rand()%1000;
    y = 0;
    rect.x=x;
    rect.y=y;
    rect.w=96;
    rect.h=190;

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

Meteorito3::~Meteorito3()
{
    //dtor
}

void Meteorito3::logica()
{
        y+=velocity;

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
