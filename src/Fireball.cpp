#include "Fireball.h"

Fireball::Fireball(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Fireball";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Imagenes/FireMeteor1.png"));
    this->textures["explode"].push_back(IMG_LoadTexture(renderer, "Imagenes/explo1.png"));
    this->textures["explode"].push_back(IMG_LoadTexture(renderer, "Imagenes/explo2.png"));
    this->textures["explode"].push_back(IMG_LoadTexture(renderer, "Imagenes/explo3.png"));
    this->textures["explode"].push_back(IMG_LoadTexture(renderer, "Imagenes/explo4.png"));
    this->textures["explode"].push_back(IMG_LoadTexture(renderer, "Imagenes/explo5.png"));
    this->textures["explode"].push_back(IMG_LoadTexture(renderer, "Imagenes/explo6.png"));
    this->textures["explode"].push_back(IMG_LoadTexture(renderer, "Imagenes/explo7.png"));


    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    rect.x=x;
    rect.y=y;
    x = 100+rand()%1000;
    y = 0;


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

Fireball::~Fireball()
{
    //dtor
}

void Fireball::logica()
{

        y+=velocity;

        if(frames%animation_velocity==0)
    {
        current_texture++;
        if(current_texture>=textures[state].size())
            current_texture=0;
    }

    frames++;


    if(colision(rect,jugador->rect))
    {
        jugador->vidas--;
        this->delete_flag= true;
        cout<<"Colision con jugador"<<endl;
    }

    frames++;
}
