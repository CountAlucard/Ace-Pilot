#include "Jugador.h"

Jugador::Jugador(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Jugador";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "navegrande.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "navegrande.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "navegrande2.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "navegrande3.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "navegrande3.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "navegrande4.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "navegrande3.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "navegrande4.png"));

    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    x = 640;
    y = 600;
    rect.x = x;
    rect.y = y;
    rect.w = 84;
    rect.h = 64;

    velocity=1;
    animation_velocity=5;

    current_texture=0;

    state="down";
    this->entidades = entidades;

    proyectil_cooldown=150;

    vidas = 10;
    puntos=0;

    for(list<Entidad*>::iterator e=entidades->begin();e!=entidades->end();e++)
    {
        if((*e)->tipo=="Enemigo")
        {
            enemigo = (Enemigo*)*e;
        }
    }

}

Jugador::~Jugador()
{
    //dtor
}

void Jugador::logica()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        x+=velocity;
         if(x>1280)
            x=0;

        state="right";
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        x-=velocity;
        if(x<0)
            x=1280;
        state="left";
    }
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        y-=velocity;
        if(y<150)
            y=150;
        state="up";
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        y+=velocity;
        if(y>650)
            y=650;
        state="down";
    }

    if(proyectil_cooldown>0)
        proyectil_cooldown--;

    if( currentKeyStates[ SDL_SCANCODE_Z ] && proyectil_cooldown==0 && this->vidas>0)
    {
        Proyectil *p = new Proyectil(entidades,renderer,x+10,y-10,"left");
        entidades->push_back(p);
        proyectil_cooldown=150;
    }


    if(frames%animation_velocity==0)
    {
        current_texture++;
        if(current_texture>=textures[state].size())
            current_texture=0;
    }

    frames++;
}

void Jugador::dibujar()
{
    if(vidas>0)
    {

        Personaje::dibujar();
    }else{
    }
}
