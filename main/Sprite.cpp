#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include "Sprite.h"

SDL_Rect gSpriteClips[95];
SDL_Rect gFoodSprite[5];
SDL_Rect gPlayerSprite[12];
SDL_Rect gBackSprite;

LTexture gBackSpriteSheet;
LTexture gPlayerSpriteSheet;
LTexture gFoodSpriteSheet;
LTexture gSpriteSheetTexture;


LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y, SDL_Rect* clip, float scale, SDL_Renderer* gRenderer)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w * scale;
        renderQuad.h = clip->h * scale;
    }

    //Render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}



void renderLetter(std::string letter, int posX, int posY, SDL_Renderer* gRenderer) {
    int target = 0;

    if (posX == -1) {
        target = (24 * 24 - letter.length() * 24) / 2;
    }

    for (unsigned i = 0; i < letter.length(); i++) {
        int charCode = int(letter.at(i)) - 33;
        if (letter.at(i) == ' ') {
            gSpriteSheetTexture.render(i * 24 + target + posX, 10 + posY, &gSpriteClips[95], 3, gRenderer);
        }
        else {
            gSpriteSheetTexture.render(i * 24 + target + posX, 10 + posY, &gSpriteClips[charCode], 3, gRenderer);
        }
    }
}


void renderLetterBiggerSize(std::string letter, int posX, int posY, SDL_Renderer* gRenderer) {

    // can le giua
    //width of the letter:
    //scale of the letter:
    //length of the letter:
    int target = (24 * 24 - letter.length() * 40) / 2;

    for (unsigned i = 0; i < letter.length(); i++) {
        int charCode = int(letter.at(i)) - 33;
        if (letter.at(i) == ' ') {
            gSpriteSheetTexture.render(target + i * 40, 10 + posY, &gSpriteClips[95], 7, gRenderer);
        }
        else {
            gSpriteSheetTexture.render(target + i * 40, 10 + posY, &gSpriteClips[charCode], 7, gRenderer);
        }
    }
}


void renderFoodSprite(int posX, int posY, int frame, SDL_Renderer* gRenderer) {

    gFoodSpriteSheet.render(posX + 50, posY + 50, &gFoodSprite[frame / 1000], 2, gRenderer);
}

void renderSpritePlayer(int posX, int posY, int frame, SDL_Renderer* gRenderer, int state) {

    if (state == 1) {
        gPlayerSpriteSheet.render(posX, posY, &gPlayerSprite[frame / 200], 2, gRenderer);
    }
    else if (state == 2) {
        gPlayerSpriteSheet.render(posX, posY, &gPlayerSprite[frame / 200 + 3], 2, gRenderer);
    }
    else if (state == 4) {
        gPlayerSpriteSheet.render(posX, posY, &gPlayerSprite[frame / 200 + 6], 2, gRenderer);
    }
    else if (state == 3) {
        gPlayerSpriteSheet.render(posX, posY, &gPlayerSprite[frame / 200 + 9], 2, gRenderer);
    }
}

void renderBack(int scale, int wscale, SDL_Renderer* gRenderer) {
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < wscale; j++) {
            gBackSpriteSheet.render(i * 24, j * 24, &gBackSprite, 2, gRenderer);
        }
    }
}

bool loadMedia(SDL_Renderer* gRenderer)
{
    //Loading success flag
    bool success = true;

    //Load sprite sheet texture
    if (!gSpriteSheetTexture.loadFromFile("bFont.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {

        for (int i = 0; i < 95; i++) {
            gSpriteClips[i].x = (i % 11) * 10 - 0.00001;
            gSpriteClips[i].y = (20 + (i / 11) * 10);
            gSpriteClips[i].w = 9.9999999999999;
            gSpriteClips[i].h = 9.9999999999999;
        }


        //for(int i = 0; i < )

    }

    return success;
}


bool loadFoodMedia(SDL_Renderer* gRenderer) {

    bool success = true;

    if (!gFoodSpriteSheet.loadFromFile("classic.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < 4; i++) {
            gFoodSprite[i].x = 64 + 0.0000001;
            gFoodSprite[i].y = 80 + i * 16;
            gFoodSprite[i].w = 15.999999999999999;
            gFoodSprite[i].h = 15.999999999999999;
        }
    }

    return success;
}

bool loadPlayerMedia(SDL_Renderer* gRenderer) {
    bool success = true;

    if (!gPlayerSpriteSheet.loadFromFile("PlayerS.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        gPlayerSprite[0].x = 0;
        gPlayerSprite[0].y = 0;
        gPlayerSprite[0].w = 18;
        gPlayerSprite[0].h = 22;

        gPlayerSprite[1].x = 0;
        gPlayerSprite[1].y = 21.999999999999999999;
        gPlayerSprite[1].w = 18;
        gPlayerSprite[1].h = 21;

        gPlayerSprite[2].x = 0;
        gPlayerSprite[2].y = 43;
        gPlayerSprite[2].w = 18;
        gPlayerSprite[2].h = 22;

        gPlayerSprite[3].x = 20;
        gPlayerSprite[3].y = 0;
        gPlayerSprite[3].w = 19;
        gPlayerSprite[3].h = 21;

        gPlayerSprite[4].x = 20;
        gPlayerSprite[4].y = 21.99999999999999;
        gPlayerSprite[4].w = 18;
        gPlayerSprite[4].h = 20;

        gPlayerSprite[5].x = 20;
        gPlayerSprite[5].y = 42.9999999999;
        gPlayerSprite[5].w = 18;
        gPlayerSprite[5].h = 22;



        gPlayerSprite[6].x = 42;
        gPlayerSprite[6].y = 0;
        gPlayerSprite[6].w = 19;
        gPlayerSprite[6].h = 21;

        gPlayerSprite[7].x = 42;
        gPlayerSprite[7].y = 22;
        gPlayerSprite[7].w = 18;
        gPlayerSprite[7].h = 20;

        gPlayerSprite[8].x = 42;
        gPlayerSprite[8].y = 43;
        gPlayerSprite[8].w = 18;
        gPlayerSprite[8].h = 22;



        gPlayerSprite[9].x = 63;
        gPlayerSprite[9].y = 0;
        gPlayerSprite[9].w = 19;
        gPlayerSprite[9].h = 21;

        gPlayerSprite[10].x = 63;
        gPlayerSprite[10].y = 22;
        gPlayerSprite[10].w = 18;
        gPlayerSprite[10].h = 20;

        gPlayerSprite[11].x = 63;
        gPlayerSprite[11].y = 43;
        gPlayerSprite[11].w = 18;
        gPlayerSprite[11].h = 22;
    }

    return success;
}



bool loadBackMedia(SDL_Renderer* gRenderer) {

    bool success = true;

    if (!gBackSpriteSheet.loadFromFile("terrain.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        gBackSprite.x = 99;
        gBackSprite.y = 68;
        gBackSprite.w = 20;
        gBackSprite.h = 20;
    }

    return success;
}

void closeSprite()
{
    //Free loaded images
    gSpriteSheetTexture.free();
    gFoodSpriteSheet.free();
    gPlayerSpriteSheet.free();
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
