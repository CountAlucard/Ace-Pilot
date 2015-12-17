#include "Meteorito2.h"

Meteorito2::Meteorito2(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Meteorito2";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.2.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.2.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.3.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.3.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.4.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.4.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.5.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.5.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.6.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.6.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.7.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.7.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.8.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.8.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.9.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "meteorito2.9.png"));


    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    x = rand()%1280;
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

Meteorito2::~Meteorito2()
{
    //dtor
}

void Meteorito2::logica()
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
