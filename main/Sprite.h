#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>

using namespace std;

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y, SDL_Rect* clip = NULL, float scale = 0, SDL_Renderer* gRenderer = NULL);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(SDL_Renderer* gRenderer);

//loads food media

bool loadFoodMedia(SDL_Renderer* gRenderer);

// loads player media
bool loadPlayerMedia(SDL_Renderer* gRenderer);
//Frees media and shuts down SDL

// loads Back media
bool loadBackMedia(SDL_Renderer* gRenderer);

void closeSprite();

//Render letter sprite on the screen
void renderLetter(std::string letter, int posX, int posY, SDL_Renderer* gRenderer);

//Scene sprites

void renderFoodSprite(int posX, int posY, int frame, SDL_Renderer* gRenderer);

void renderSpritePlayer(int posX, int posY, int frame, SDL_Renderer* gRenderer, int state);

void renderBack(int width, int height, SDL_Renderer* gRenderer);

void renderLetterBiggerSize(std::string, int posX, int posY, SDL_Renderer* gRenderer);

