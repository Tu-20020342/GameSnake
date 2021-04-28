#include <iostream>
#include <SDL.h>
#include "MenuEffect.h"
#include "Sprite.h"

using namespace std;
// 5 - 15
// 5  - 15
int x = 5;
int y = 5;

int frameEffect = 0;
int frameEffectY = 0;
int frameRate = 100000;
int BomberFrame = 0;

bool toTheRight = false;
bool toTheLeft = false;
bool toUp = false;
bool toDown = false;

SDL_Rect LineMenuEffect;


void LineEffectXH1(SDL_Renderer* gRenderer, int frame) {
    LineMenuEffect.h = 5;
    if (frame - 20 > 0) {
        LineMenuEffect.w = frame - 20;
    }
    else {
        LineMenuEffect.w = 0;
    }
    LineMenuEffect.x = 4 * 24;
    LineMenuEffect.y = 8 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}


void LineEffectXH(SDL_Renderer* gRenderer) {
    LineMenuEffect.h = 5;
    LineMenuEffect.w = 14 * 24;
    LineMenuEffect.x = 4 * 24;
    LineMenuEffect.y = 8 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}

void LineEffectXH2(SDL_Renderer* gRenderer, int frame) {
    LineMenuEffect.h = 5;
    if (14 * 24 - frame - 20 < 0) {
        LineMenuEffect.w = 0;
    }
    else {
        LineMenuEffect.w = 14 * 24 - frame - 20;
    }
    LineMenuEffect.x = 4 * 24 + frame + 20;
    LineMenuEffect.y = 8 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}

void LineEffectXL(SDL_Renderer* gRenderer) {
    LineMenuEffect.h = 5;
    LineMenuEffect.w = 14 * 24;
    LineMenuEffect.x = 4 * 24;
    LineMenuEffect.y = 18 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}

// first
void LineEffectXL1(SDL_Renderer* gRenderer, int frame) {
    LineMenuEffect.h = 5;
    if (frame - 24 > 0) {
        LineMenuEffect.w = frame - 24;
    }
    else {
        LineMenuEffect.w = 0;
    }
    LineMenuEffect.x = 4 * 24;
    LineMenuEffect.y = 18 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}

// seoond
void LineEffectXL2(SDL_Renderer* gRenderer, int frame) {
    LineMenuEffect.h = 5;

    if (14 * 24 - frame - 20 < 0) {
        LineMenuEffect.w = 0;
    }
    else {
        LineMenuEffect.w = 14 * 24 - frame - 20;
    }
    LineMenuEffect.x = 4 * 24 + frame + 20;

    LineMenuEffect.y = 18 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}

void LineEffectYL(SDL_Renderer* gRenderer) {
    LineMenuEffect.h = 10 * 24;
    LineMenuEffect.w = 5;
    LineMenuEffect.x = 4 * 24;
    LineMenuEffect.y = 8 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}



void LineEffectYL1(SDL_Renderer* gRenderer, int frame) {

    if (frame - 24 > 0) {
        LineMenuEffect.h = frame - 24;
    }
    else {
        LineMenuEffect.h = 0;
    }

    LineMenuEffect.w = 5;
    LineMenuEffect.x = 4 * 24;
    LineMenuEffect.y = 8 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}


void LineEffectYL2(SDL_Renderer* gRenderer, int frame) {
    if (10 * 24 - frame - 20 < 0) {
        LineMenuEffect.h = 0;
    }
    else {
        LineMenuEffect.h = 10 * 24 - frame - 20;
    }

    LineMenuEffect.w = 5;
    LineMenuEffect.x = 4 * 24;

    LineMenuEffect.y = 8 * 24 + frame + 20;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}


void LineEffectYH(SDL_Renderer* gRenderer) {
    LineMenuEffect.h = 10 * 24 + 5;
    LineMenuEffect.w = 5;
    LineMenuEffect.x = 18 * 24;
    LineMenuEffect.y = 8 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}


void LineEffectYH1(SDL_Renderer* gRenderer, int frame) {
    if (frame - 24 > 0) {
        LineMenuEffect.h = frame - 24 + 5;
    }
    else {
        LineMenuEffect.h = 0;
    }

    LineMenuEffect.w = 5;
    LineMenuEffect.x = 18 * 24;
    LineMenuEffect.y = 8 * 24;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}


void LineEffectYH2(SDL_Renderer* gRenderer, int frame) {
    if (10 * 24 - frame - 20 < 0) {
        LineMenuEffect.h = 0;
    }
    else {
        LineMenuEffect.h = 10 * 24 - frame - 20 + 5;
    }

    LineMenuEffect.w = 5;
    LineMenuEffect.x = 18 * 24;

    LineMenuEffect.y = 8 * 24 + frame + 20;
    SDL_RenderFillRect(gRenderer, &LineMenuEffect);
}

void renderPlayerEffect(SDL_Renderer* renderer) {



    if (frameEffect / 5 == 0 && frameEffectY / 5 == 10 * 24) {
        toTheLeft = false;
        toTheRight = false;
        toUp = true;
        toDown = false;
    }
    else if (frameEffect / 5 == 0 && frameEffectY / 5 == 0) {

        toTheRight = true;
        toTheLeft = false;
        toUp = false;
        toDown = false;
    }
    else if (frameEffect / 5 == 14 * 24 && frameEffectY / 5 == 0) {
        toTheLeft = false;
        toTheRight = false;
        toDown = true;
        toUp = false;
    }
    else if (frameEffectY / 5 == 10 * 24 && frameEffect / 5 == 14 * 24) {
        toTheLeft = true;
        toTheRight = false;
        toUp = false;
        toDown = false;
    }

    if (toUp) {
        renderSpritePlayer(3 * 24 + (frameEffect) / 5 + 10, 7 * 24 + frameEffectY / 5, BomberFrame, renderer, 4);
    }
    else if (toDown) {
        renderSpritePlayer(3 * 24 + (frameEffect) / 5 + 10, 7 * 24 + frameEffectY / 5, BomberFrame, renderer, 1);
    }
    else if (toTheLeft) {
        renderSpritePlayer(3 * 24 + (frameEffect) / 5, 7 * 24 + frameEffectY / 5, BomberFrame, renderer, 2);
    }
    else if (toTheRight) {
        renderSpritePlayer(3 * 24 + (frameEffect) / 5, 7 * 24 + frameEffectY / 5, BomberFrame, renderer, 3);
    }

    if (toTheRight) {
        // first line
        LineEffectXH1(renderer, frameEffect / 5);
        LineEffectXH2(renderer, frameEffect / 5);
        LineEffectXL(renderer);
        LineEffectYL(renderer);
        LineEffectYH(renderer);
    }
    else if (toDown) {
        LineEffectYH1(renderer, frameEffectY / 5);
        LineEffectYH2(renderer, frameEffectY / 5);
        LineEffectXL(renderer);
        LineEffectXH(renderer);
        LineEffectYL(renderer);
    }
    else if (toTheLeft) {
        LineEffectXL1(renderer, frameEffect / 5);
        LineEffectXL2(renderer, frameEffect / 5);
        LineEffectXH(renderer);
        LineEffectYL(renderer);
        LineEffectYH(renderer);
    }
    else if (toUp) {
        LineEffectXH(renderer);
        LineEffectXL(renderer);
        LineEffectYL1(renderer, frameEffectY / 5);
        LineEffectYL2(renderer, frameEffectY / 5);
        LineEffectYH(renderer);
    }

    //cout<<frameEffectY<<endl;
    if (toTheLeft) {
        frameEffect--;
    }
    else if (toUp) {
        frameEffectY--;
    }
    else if (toDown) {
        frameEffectY++;
    }
    else if (toTheRight) {
        frameEffect++;
    }

    BomberFrame++;
    if (BomberFrame / 200 >= 3) {
        BomberFrame = 0;
    }
}
