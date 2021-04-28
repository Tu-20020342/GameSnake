#include <SDL.h>
#include <iostream>
#include "render.h"
#include <vector>
#include "Sprite.h"

using namespace std;

int v1 = 0;
int v2 = 0;
int v3 = 0;
int v4 = 0;
int framePlayer = 0;

int timeAfterHub = 0;
bool eatTimeCount = false;


void renderPlayer(SDL_Renderer* renderer, SDL_Rect snakeBlock, int x, int y, int scale, vector <int> tailX, vector<int> tailY, int slength, int frame, int state, bool checkCol) {

    snakeBlock.w = scale;
    snakeBlock.h = scale;

    // this for after eat effects
    if (checkCol) {
        eatTimeCount = true;
    }

    if (eatTimeCount) {
        timeAfterHub++;

        if (timeAfterHub / 1000 > 2) {
            eatTimeCount = false;
            timeAfterHub = 0;
        }
    }

    for (int i = 0; i < slength; i++) {
        if (eatTimeCount) {
            if (framePlayer / 1000 == 0) {
                v1 = rand() % 255;
            }
            else if (framePlayer / 1000 == 1) {
                v2 = rand() % 255;
            }
            else if (framePlayer / 1000 == 2) {
                v3 = rand() % 255;
            }
            v4 = 1;
        }
        else {
            v1 = 255;
            v2 = 221;
            v3 = 0;
            v4 = 1;
        }

        // if(frame/1000 == 1) {
        SDL_SetRenderDrawColor(renderer, v1, v2, v3, v4);
        snakeBlock.x = tailX[i];
        snakeBlock.y = tailY[i];
        SDL_RenderFillRect(renderer, &snakeBlock);
    }
    // for the font of the snake ;
    snakeBlock.x = x;
    snakeBlock.y = y;
    // SDL_RenderFillRect (renderer, &snakeBlock);

    renderSpritePlayer(x - 5, y - 10, framePlayer, renderer, state);

    framePlayer++;
    if (framePlayer / 200 >= 3) {
        framePlayer = 0;
    }
}


void renderFood(SDL_Renderer* renderer, SDL_Rect food) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &food);
}
