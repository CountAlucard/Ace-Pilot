#include "Jugador2.h"

Jugador2::Jugador2(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Jugador";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipOff.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMin.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMin.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMed.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMax.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMin.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMed.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMin.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Imagenes/SpaceShipMed.png"));

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

    proyectil_cooldown=300;

    vidas = 3;

    for(list<Entidad*>::iterator e=entidades->begin();
        e!=entidades->end();
        e++)
    {
        if((*e)->tipo=="Enemigo")
        {
            enemigo = (Enemigo*)*e;
        }
    }

}

Jugador2::~Jugador2()
{
    //dtor
}

void Jugador2::logica()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    cout<<this->y<<endl;
    //logicaPush();

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
        if(y<250)
            y=250;
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

    if( currentKeyStates[ SDL_SCANCODE_Z ] && proyectil_cooldown==0)
    {
        Proyectil *p = new Proyectil(entidades,renderer,x+13,y-10,"left");
        entidades->push_back(p);
        proyectil_cooldown=300;
    }

    if(frames%animation_velocity==0)
    {
        current_texture++;
        if(current_texture>=textures[state].size())
            current_texture=0;
    }

    frames++;
}

void Jugador2::dibujar()
{
    Personaje::dibujar();
}
