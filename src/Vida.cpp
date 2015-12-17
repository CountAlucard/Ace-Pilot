#include "Vida.h"

Vida::Vida(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    this->entidades = entidades;
    this->renderer = renderer;
    texture = IMG_LoadTexture(renderer,"nave.png");

    gameover = IMG_LoadTexture(renderer,"Gameover.png");
    rect.x=0;
    rect.y=0;
    SDL_QueryTexture(texture,NULL,NULL,&rect.w,&rect.h);

    for(list<Entidad*>::iterator e=entidades->begin();
            e!=entidades->end();
            e++)
    {
        if((*e)->tipo=="Jugador")
        {
            jugador = (Jugador*)*e;
        }
    }
    capa=1;
}

Vida::~Vida()
{
    //dtor
}

void Vida::dibujar()
{
    SDL_Rect rect_aux = rect;
    for(int i=0; i<jugador->vidas; i++)
    {
        rect_aux.x+=rect_aux.w;
        SDL_RenderCopy(renderer,texture,NULL,&rect_aux);
    }

    if(jugador->vidas<=0)
    {
        rect.x=300;
        rect.y=50;

        SDL_QueryTexture(gameover,NULL,NULL,&rect.w,&rect.h);
        SDL_RenderCopy(renderer,gameover,NULL,&rect_aux);
    }
    else
    {
        SDL_QueryTexture(texture,NULL,NULL,&rect.w,&rect.h);
        rect.x=0;
        rect.y=0;
    }
//    if(jugador->vidas<=0)
//        exit(0);
    //cout<<"dibujando"<<endl;
}

void Vida::logica()
{

}
