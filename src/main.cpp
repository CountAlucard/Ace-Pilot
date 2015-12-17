#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include<list>
#include<stdio.h>
#include<fstream>

#include "Jugador.h"
#include "Enemigo.h"
#include "Proyectil.h"
#include "Vida.h"
#include "Meteorito2.h"
#include "Meteorito3.h"
#include "Meteorito4.h"
#include "Meteorito5.h"
#include "Windows.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character,*menu,*pausa,*level;
SDL_Rect rect_background,rect_character,rect_menu,rect_pausa,rect_level;
Mix_Music *gMusic;

int juego=0;
int a=1;
int p=0;
int pause=0;
int espera=0;
int nivel=1;
bool enter= true;

using namespace std;

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1280/*WIDTH*/, 720/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    gMusic = Mix_LoadMUS("music.ogg");

    //Init textures
    int w=0,h=0;

    menu = IMG_LoadTexture(renderer,"menu1.png");
    SDL_QueryTexture(menu, NULL, NULL, &w, &h);
    rect_menu.x = 0;
    rect_menu.y = 0;
    rect_menu.w = w;
    rect_menu.h = h;

    pausa = IMG_LoadTexture(renderer,"pause1.png");
    SDL_QueryTexture(pausa, NULL, NULL, &w, &h);
    rect_pausa.x = 0;
    rect_pausa.y = 0;
    rect_pausa.w = w;
    rect_pausa.h = h;

    background = IMG_LoadTexture(renderer,"spacebackground.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    level = IMG_LoadTexture(renderer,"level1.png");
    SDL_QueryTexture(level, NULL, NULL, &w, &h);
    rect_level.x = 900;
    rect_level.y = 0;
    rect_level.w = 3*w/4;
    rect_level.h = 3*h/4;

    list<Entidad*>entidades;
    entidades.push_back(new Jugador(&entidades,renderer));
    entidades.push_back(new Vida(&entidades,renderer));

    double last_frame=0;
    int frame=1;
    int meteoro=0;
    int vidaactual=0;
    //Main Loop
    while(true)
    {

        while(SDL_PollEvent(&Event))
        {

            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_d)
                    if(Event.key.keysym.sym == SDLK_d)
                        rect_character.x++;


                if(Event.key.keysym.sym == SDLK_e&&juego!=0)
                {
                    //pone la pausa
                    juego=3;
                }

                if(Event.key.keysym.sym == SDLK_p)
                {
                    if(p==0)
                    {
                        while(p==0)
                        {

                            while(SDL_PollEvent(&Event))
                            {
                                if(Event.type == SDL_QUIT)
                                {
                                    return 0;
                                }
                                if(Event.type == SDL_KEYDOWN)
                                {
                                    if(Event.key.keysym.sym == SDLK_p)
                                        p++;
                                }
                            }

                        }

                        p=0;
                    }

                }
                if(Event.key.keysym.sym == SDLK_DOWN)
                {
                    //maneja el estado de la pausa y menu
                    //a para menu p para pause
                    pause=1;
                    a++;
                    if(a>4)
                        a=1;
                }
                if(Event.key.keysym.sym == SDLK_UP)
                {
                    //igul que la s pero alrevez
                    pause=0;
                    a--;
                    if(a<1)
                        a=4;
                }

                if(Event.key.keysym.sym == SDLK_SPACE)
                {
                    //dependiendo si es menu o pausa que hacer al dar space
                    //son las diferentes posiciones del switch
                    if(juego==0)
                    {
                        if(a==1)
                        {
                            cout<<a;
                            Mix_PlayMusic(gMusic, -1);
                            juego=2;
                        }
                        if(a==5)
                        {
                            a=1;
                        }
                        if(a==2)
                        {
                            a=5;
                        }

                        if(a==3)
                        {
//                           //Highscores
                        }
                        if(a==4)
                        {
                            exit(0);
                        }
                        if(a==6)
                        {

                        }
                    }

                    if(juego==3)
                    {
                        if(pause==0)
                        {
                            juego=2;
                        }
                        if(pause==1)
                        {
                            exit(0);
                        }
                    }
                }
            }
        }
        if(juego==0)
        {
            //este es el menu
            // y todo su movimiento en el menu
            //control de las imagenes del menu
            switch(a)
            {
            case 1:
                menu = IMG_LoadTexture(renderer,"menu1.png");
                break;
            case 2:
                menu = IMG_LoadTexture(renderer,"menu2.png");
                break;
            case 3:
                menu = IMG_LoadTexture(renderer,"menu3.png");
                break;
            case 4:
                menu = IMG_LoadTexture(renderer,"menu4.png");
                break;
            case 5:
                menu = IMG_LoadTexture(renderer,"menu5.png");
                break;
            }
            SDL_RenderCopy(renderer, menu, NULL, &rect_menu);
            SDL_RenderPresent(renderer);
        }

        //este es el juego
        if(juego==2)
        {
            for(list<Entidad*>::iterator e = entidades.begin(); e!=entidades.end(); e++)
                (*e)->logica();

            for(list<Entidad*>::iterator e = entidades.begin(); e!=entidades.end(); e++)
            {
                if((*e)->delete_flag)
                {
                    entidades.remove(*e);
                    break;
                }
            }

            SDL_RenderCopy(renderer, background, NULL, &rect_background);
            SDL_RenderCopy(renderer, level, NULL, &rect_level);

            //-----------------Cambio de NIVELES---------------------------------------------------------------------
            //--------------------------------------NIVEL 1 ---------------------------------------------------------------
            if(nivel==1)
            {
                SDL_RenderCopy(renderer, level, NULL, &rect_level);

                if(frame%500==0 || frame%600==0 )
                {
                    entidades.push_back(new Enemigo(&entidades,renderer));
                    //entidades.push_back(new Meteorito2(&entidades,renderer));
                    meteoro+=1;
                }
//                if(frame%5000==0)
//                {
//                    entidades.push_back(new Meteorito3(&entidades,renderer));
//                    meteoro++;
//                }
                if(meteoro>= 20)
                {
                    nivel++;
                    level = IMG_LoadTexture(renderer,"level2.png");
                    meteoro=0;
                }
            }
            //--------------------------------------NIVEL 2 ---------------------------------------------------------------
            if(nivel==2)
            {
                SDL_RenderCopy(renderer, level, NULL, &rect_level);
                if(frame%500==0|| frame%600==0 || frame%700==0)
                {
                    entidades.push_back(new Enemigo(&entidades,renderer));
                    entidades.push_back(new Meteorito2(&entidades,renderer));
                    meteoro+=1;
                }
//                if(frame%5000==0)
//                {
//                    entidades.push_back(new Meteorito3(&entidades,renderer));
//                    meteoro++;
//                }
                if(meteoro>= 75)
                {
                    nivel++;
                    level = IMG_LoadTexture(renderer,"level3.png");
                    background = IMG_LoadTexture(renderer,"Imagenes/FireBckg.png");
                    meteoro=0;
                }
            }
            //--------------------------------------NIVEL 3 ---------------------------------------------------------------
            if(nivel==3)
            {
                SDL_RenderCopy(renderer, level, NULL, &rect_level);
                if(frame%400==0 || frame%500==0|| frame%600==0 )
                {
                    entidades.push_back(new Enemigo(&entidades,renderer));
                    entidades.push_back(new Meteorito2(&entidades,renderer));
                    meteoro+=1;
                }
                if(frame%800==0 || frame%1200==0 )
                    entidades.push_back(new Meteorito4(&entidades,renderer));
                if(frame%10000==0)
                {
                    entidades.push_back(new Meteorito3(&entidades,renderer));
                    meteoro++;
                }
                if(meteoro>= 100)
                {
                    nivel++;
                    level = IMG_LoadTexture(renderer,"level4.png");
                    meteoro=0;
                }
            }
            //--------------------------------------NIVEL 4 ---------------------------------------------------------------
            if(nivel==4)
            {
                SDL_RenderCopy(renderer, level, NULL, &rect_level);
                if( frame%400==0 || frame%500==0|| frame%600==0 || frame%700==0)
                {
                    entidades.push_back(new Enemigo(&entidades,renderer));
                    entidades.push_back(new Meteorito2(&entidades,renderer));
                    meteoro+=1;
                }
                if(frame%800==0 || frame%1000==0 || frame%1200==0 )
                {
                    entidades.push_back(new Meteorito4(&entidades,renderer));
                    meteoro++;
                }

                if(frame%10000==0)
                {
                    entidades.push_back(new Meteorito3(&entidades,renderer));
                    meteoro++;
                }
                if(meteoro>= 125)
                {
                    nivel++;
                    level = IMG_LoadTexture(renderer,"level5.png");
                    meteoro=0;
                }
            }
            //--------------------------------------NIVEL 5 ---------------------------------------------------------------
            if(nivel==5)
            {
                SDL_RenderCopy(renderer, level, NULL, &rect_level);
                if(frame%400==0 || frame%500==0|| frame%600==0 || frame%700==0 || frame%800==0)
                {
                    entidades.push_back(new Enemigo(&entidades,renderer));
                    entidades.push_back(new Meteorito2(&entidades,renderer));
                    meteoro+=1;
                }
                if(frame%800==0 || frame%1000==0 || frame%1200==0 || frame%1400==0 )
                {
                    entidades.push_back(new Meteorito4(&entidades,renderer));
                    entidades.push_back(new Meteorito5(&entidades,renderer));
                    meteoro++;
                }
                if(frame%3000==0 || frame%5000==0)
                {
                    entidades.push_back(new Meteorito3(&entidades,renderer));
                    meteoro++;
                }
                if(meteoro>= 150)
                {
                    nivel++;
                    level = IMG_LoadTexture(renderer,"level6.png");
                    meteoro=0;
                }
            }
            //--------------------------------------NIVEL 6 ---------------------------------------------------------------
            if(nivel==6)
            {
                SDL_RenderCopy(renderer, level, NULL, &rect_level);
                if(frame%400==0 || frame%500==0|| frame%600==0 || frame%700==0 || frame%800==0 || frame%950==0)
                {
                    entidades.push_back(new Enemigo(&entidades,renderer));
                    entidades.push_back(new Meteorito2(&entidades,renderer));
                    meteoro+=1;
                }
                if(frame%800==0 || frame%1000==0 || frame%1200==0 || frame%1400==0 ||frame%1700==0  )
                {
                    entidades.push_back(new Meteorito4(&entidades,renderer));
                    entidades.push_back(new Meteorito5(&entidades,renderer));
                    meteoro++;
                }
                if(frame%3000==0 || frame%5000==0 || frame%7000==0)
                {
                    entidades.push_back(new Meteorito3(&entidades,renderer));
                    meteoro++;
                }
                if(meteoro>= 200)
                {
                    nivel++;
                    meteoro=0;
                }
                for(list<Entidad*>::iterator e = entidades.begin(); e!=entidades.end(); e++)
                {
                    if((*e)->tipo== "Jugador")
                    {
                        vidaactual= (*e)->vidas;
                    }
                }

            }
            if(nivel==7)
            {
                for(list<Entidad*>::iterator e = entidades.begin(); e!=entidades.end(); e++)
                {
                    if((*e)->tipo== "Jugador")
                    {
                        (*e)->vidas= vidaactual;
                    }
                }
                level = IMG_LoadTexture(renderer,"YouWon.png");
                rect_level.w = 600;
                rect_level.h = 600;
                rect_level.x = 300;
                rect_level.y = 0;
                SDL_RenderCopy(renderer, level, NULL, &rect_level);
            }
            //--------------------------------------------------------------------------------------------------------------
            for(int i=0; i<2; i++)
            {
                for(list<Entidad*>::iterator e = entidades.begin(); e!=entidades.end(); e++)
                {
                    if((*e)->capa==i)
                        (*e)->dibujar();

                    if((*e)->tipo=="Jugador") // Aqui se arregla lo que deja de tirar a veces si se presiona la Z sin soltar
                    {

                        if((*e)->vidas<=0)
                        {
                            while(SDL_PollEvent(&Event))
                            {
                                if(Event.type == SDL_KEYDOWN)
                                {
                                    if(Event.key.keysym.sym == SDLK_RETURN)
                                    {

                                        WinExec("labprogra3.exe",SW_SHOW);
                                        exit(1);
                                    }
                                }
                            }
                            if (enter)
                            {
                                int contador=0;
                                int puntosfinal;
                                cout<<(*e)->puntos<<endl;
                                puntosfinal= (*e)->puntos ;
                                //--------------------PUNTOS-----------------------
                                ifstream in("Puntos");
                                vector<double> respuesta;
                                double str;
                                //CHEQUIAR PUNTOS
                                while(in>>str)
                                {
                                    respuesta.push_back(str);
                                    contador++;
                                }
                                if(respuesta.size()==0)
                                {
                                    (*e)->puntos= 0;
                                }
                                else
                                {
                                    ofstream out("Puntos");
                                    for(int i=0; i< contador; i++)
                                    {
                                        (*e)->puntos = respuesta[i];
                                        out<<(*e)->puntos<<endl;
                                    }
                                    out<<puntosfinal<<endl;
                                    out.close();
                                    //cout<<puntosfinal<<endl;
                                }

                                //Escribir nuevo puntaje

                                //-------------------------------------------------
                                frame=0;
                                //---------------------------------------------

                            }
                            enter=false;
                        }
                    }
                }
            }
            SDL_RenderPresent(renderer);
            frame+=1;
        }

        // menu de pausa
        if(juego==3)
        {
            //dibuja la pausa
            SDL_RenderCopy(renderer, pausa, NULL, &rect_pausa);
            SDL_RenderPresent(renderer);
            //control de imagenes de pausa
            switch(pause)
            {
            case 0:
                pausa = IMG_LoadTexture(renderer,"pause1.png");
                break;
            case 1:
                pausa = IMG_LoadTexture(renderer,"pause2.png");
                break;
            }
        }
    }
    return 0;
}
