#define _USE_MATH_DEFINES
#include<math.h>
#include <fstream>
#include<stdio.h>
#include<string.h>
#include <iostream>
#include<time.h>
#include<Windows.h>
#include "Unicorn.h"
#include "Board.h"
#include "Obstacle.h"
#include "Platform.h"
#include "Dolphin.h"
#include "Winx.h"
#include "Stalaktyt.h"
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#ifdef __cplusplus
extern "C"
#endif
using namespace std;
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	640

SDL_Window* window = NULL;
SDL_Surface* ekran = NULL;
SDL_Surface* charset = SDL_LoadBMP("cs8x8.bmp");

void DrawString(SDL_Surface* screen, int x, int y, const char* text,
    SDL_Surface* charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += 8;
        text++;
    };
};
void bubbleSort(int* arr, char** arr2)
{
    int i, j;
    for (i = 0; i < 10 - 1; i++)
    {
        for (j = 0; j < 10 - i - 1; j++)
        {
            if ((arr[j]&&arr[j+1])&& arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swap(arr2[j], arr2[j + 1]);
            }
        }
            
    }
        
}
void setRecord(Unicorn* unicorn) {
    SDL_FillRect(ekran, NULL, 0);
    fstream plik;
    plik.open("records.txt", ios::in | ios::out | ios::app);
    if (plik.good()) {
        char nickname[20];
        int wynik = unicorn->points;
        cout << "Wpisz swoj nick!" << endl;
        cin >> nickname;
        plik << nickname << " " << wynik << " ";
        plik.close();

    }
}
void readRecord() {
    SDL_FillRect(ekran, NULL, 0);
    fstream plik;
    char tab[10][50];
    int y = 100;
    plik.open("records.txt", ios::in | ios::out | ios::app);
    if (plik.good()) {
        int wynik[10];
        char** nickname = new char* [10];
        for (int i = 0; i < 10; i++) {
            nickname[i] = new char[20];
        }
        for (int i = 0; i < 10; i++) {
            plik >> nickname[i] >> wynik[i];
        }
        bubbleSort(wynik, nickname);
        for (int i = 0; i < 10; i++) {
            if (wynik[i]>0) {
                sprintf(tab[i], "%s %d", nickname[i], wynik[i]);
                DrawString(ekran, ekran->w / 2 - strlen(tab[i]) * 8 / 2, y, tab[i], charset);
                y += 20;
            }
            
        }
        
    }
    SDL_UpdateWindowSurface(window);
    SDL_Event e;
    bool menu = true;
    while (menu) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                menu = false;
            }
            SDL_UpdateWindowSurface(window);
        }
    }
    

}
void init()
{
	window = SDL_CreateWindow("Unicorn Attack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	ekran = SDL_GetWindowSurface(window);
    SDL_SetColorKey(charset, SDL_TRUE, SDL_MapRGB(charset->format, 0, 0, 0));
}

void changeSteering(bool& steering) {
    steering = !steering;
}



int main(int argc, char** argv) {
start:
    
    init();
    bool menu = true;
    SDL_Surface* menubmp = SDL_LoadBMP("menu.bmp");
    
    //------------- START MENU
    while (menu) {

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > 11 && x < 241 && y>357 && y < 453)menu = false;
                if (x > 270 && x < 600 && y>356 && y < 453)readRecord();
            }
            SDL_BlitSurface(menubmp, NULL, ekran, NULL);
            SDL_UpdateWindowSurface(window);
        }
        
    }
    






    int lives = 3;
    //-------------------------
    float others_speed = 0.15;
    bool default_steering = true;
    char text[128];
    char text2[128];
    
    Unicorn* unicorn = new Unicorn();
    Dolphin* dolphinarray[12];
    for (int i = 0; i < 12; i++) {
        dolphinarray[i] = NULL;
    }
    Stalaktyt* stalaktyt = NULL;
    Dolphin* dolphin = NULL;
    Board* board = new Board();
    Platform* platform = NULL;
    Obstacle* obstacle = NULL;
    Winx* winx = NULL;
    int x = 0;
    int points = 100;
    int winxpoints = 10;
    srand(time(NULL));
    int randomSpawn = rand() % 10000;
    int quit = 1;
    SDL_Event e;
    int position = 0;
    while (quit)
    {

        int ticks = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0)
        {
            SDL_FillRect(ekran, NULL, 0);
            if (e.type == SDL_QUIT)
            {
                quit = 0;
            }
            else if (e.type == SDL_KEYDOWN && default_steering)
            {
                switch (e.key.keysym.sym)
                {

                case 'z': {
                    if ((!unicorn->dash && unicorn->jumpcounter != 2) || (unicorn->jumpcounter == 1 && unicorn->touched_ground == false))
                        unicorn->jumped = true; break;
                }
                case SDLK_ESCAPE: {quit = 0; break; }
                case 'n': {board->reset(dolphinarray, points, unicorn, obstacle,platform);
                    unicorn->points = 0;
                    position = 0;

                    break; }
                case 'x': {if (ticks - board->ticks > 3000) { unicorn->dash = true; board->ticks = ticks; break; }}
                case 'd': {changeSteering(default_steering); break; }
                }
            }
            else if (e.type == SDL_KEYDOWN && !default_steering)
            {
                switch (e.key.keysym.sym) {
                case SDLK_UP: {
                    if ((!unicorn->dash && unicorn->jumpcounter != 2) || (unicorn->jumpcounter == 1 && unicorn->touched_ground == false))
                        unicorn->jumped = true; break;
                }
                case 'q': {quit = 0; break; }
                case 'w': {board->reset(dolphinarray, points, unicorn, obstacle,platform);
                    unicorn->points = 0;
                    position = 0;
                    break; }
                case SDLK_SPACE: {if (ticks - board->ticks > 3000) { unicorn->dash = true; board->ticks = ticks; break; }}
                case 'd': {changeSteering(default_steering); break; }
                }

            }
            else if (e.type == SDL_KEYUP && default_steering) {
                switch (e.key.keysym.sym) {
                case 'z': {
                    if (unicorn->getJumped() == true && unicorn->jumpcounter < 2)
                        unicorn->jumped = false;
                    unicorn->rememberjump = unicorn->coords.y;
                    unicorn->jumpcounter++;  break;
                }
                case 'x': {
                    if (unicorn->jumpcounter > 0)
                        unicorn->jumpcounter--;
                }
                }
            }
            else if (e.type == SDL_KEYUP && !default_steering) {
                switch (e.key.keysym.sym) {
                case SDLK_UP: {
                    if (unicorn->getJumped() == true && unicorn->jumpcounter < 2)
                        unicorn->jumped = false;
                    unicorn->jumpcounter++;  break;
                }
                case SDLK_SPACE: {
                    if (unicorn->jumpcounter > 0)
                        unicorn->jumpcounter--;
                }
                }
            }
        }
        if (ticks %50 == 0)
        {
            unicorn->points += 1;
        }
        board->draw(ekran);

        unicorn->draw(ekran);

        board->dash(unicorn);
        board->move(unicorn);
        unicorn->jump(ticks);

        if (randomSpawn == 0 && (obstacle == NULL || obstacle->spawn_allowed) && (platform == NULL || platform->coords.x < 800)) {
            obstacle = new Obstacle();
        }
        if (randomSpawn == 2 && (stalaktyt == NULL || stalaktyt->spawn_allowed)) {
            stalaktyt = new Stalaktyt();
        }
        if (randomSpawn == 1 && (platform == NULL || platform->spawn_allowed) && (obstacle==NULL || obstacle->coords.x < 800)) {
            platform = new Platform();
        }
        if (randomSpawn == 200 && (winx == NULL || winx->spawn_allowed)) {
            winx = new Winx();
        }
        
        randomSpawn = rand() % 10000;
        if(winx!=NULL)
        {
            winx->move(others_speed,ekran, unicorn);
            winx->collision(unicorn, winxpoints);
            winx->subpoints(unicorn, winxpoints);
        }
        if (platform != NULL) {
            platform->move(ekran, unicorn);
            platform->collision(unicorn);
        }
        
        obstacle->subpoints(unicorn, points);
        obstacle->move(obstacle, ekran, unicorn, others_speed);
        obstacle->collision(unicorn, points);
        stalaktyt->move(ekran, unicorn, others_speed);
        stalaktyt->collision(unicorn, quit);
        if ((unicorn->points) > (500*x/50)) {
            dolphin = new Dolphin(dolphinarray, position);
            x += 50;
            position += 50;
            board->speed_offset += 0.05;
            others_speed += 0.05;
        }
        for (int i = 0; i < 12; i++) {
            if(dolphinarray[i]!=NULL)
            dolphinarray[i]->draw(ekran);
        }
        if (winx != NULL && winx->collided == true) {
            sprintf(text, "Added points: %d", winxpoints - 10);
            DrawString(ekran, ekran->w / 2 - strlen(text) * 8 / 2, 100, text, charset);
        }
        if (obstacle != NULL && obstacle->show == true) {
            sprintf(text, "Added points: %d", points-100);
            DrawString(ekran, ekran->w / 2 - strlen(text) * 8 / 2, 120, text, charset);
        }

        sprintf(text2, "Points: %d", unicorn->points);
        if (unicorn->lives == 0) {
            setRecord(unicorn);
            goto start;
        }
        if (lives != unicorn->lives) {
            bool pause = true;
            sprintf(text, "Continue? Click c");
            sprintf(text2, "Points: %d", unicorn->points);
            DrawString(ekran, ekran->w / 2 - strlen(text) * 8 / 2, 20, text, charset);
            DrawString(ekran, ekran->w / 2 - strlen(text2) * 8 / 2, 40, text2, charset);
            SDL_UpdateWindowSurface(window);
            while (pause) {
                
                SDL_Event e;
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                        case 'c':pause = false; break;
                        }
                    }
                }

            }

            board->reset(dolphinarray, points, unicorn, obstacle,platform);
            lives = unicorn->lives;
            position = 0;
        }
        DrawString(ekran, ekran->w / 2 - strlen(text2) * 8 / 2, 20, text2, charset);
        
        SDL_UpdateWindowSurface(window);
    }
    return 0;
}
