#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <ctime>
#include <vector>
#include "render.h"
#include "State.h"
#include "Sprite.h"
#include "SoundTheme.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;


bool checkCollision(int foodx, int foody, int snakeblockx, int snakeblocky) {
    if (foodx == snakeblockx && foody == snakeblocky) {
        return true;
    }
    return false;
}

pair <int, int> getFoodSpawn(vector<int>tailX, vector<int>tailY, int playerx, int playery, int scale, int wScale, int slength) {

    srand(time(NULL));
    bool test = false;
    int x = scale * (rand() % wScale);
    int y = scale * (rand() % wScale);
    test = true;

    for (int i = 0; i < slength; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            test = false;
        }
    }

    if (test == false) {
        x = -100;
        y = -100;
    }

    pair <int, int> foodloca;
    foodloca = make_pair(x, y);
    return foodloca;
}

void youWin(SDL_Renderer* renderer, SDL_Event event, int scale, int wscale, int slength) {

    renderLetter("Game Over", 20, 100, renderer);
    renderLetter("Press Enter to retry", 20, 200, renderer);
    renderLetter((string("Score: ") + to_string(slength * 10)).c_str(), 20, 300, renderer);

    // Show game over screen while space has not been pressed
    while (true) {
        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                exit(0);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                return;
            }
        }
    }
}


void renderScore(SDL_Renderer* renderer, int slength, int scale, int wscale) {
    renderLetter((string("Score:") + to_string(slength * 10)).c_str(), -1, 5, renderer);

}

bool initial(int scale, int wscale) {
    bool success = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize! SDL error" << endl;
        success = false;
    }
    else {
        window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scale * wscale + 1, scale * wscale + 1, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            cout << "Window could not be created! SDL error" << endl;
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                cout << "Renderer could not be created! SDL error" << endl;
                success = false;
            }
            else {
                // Initialize the renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                // Initialize the PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) && imgFlags)) {
                    cout << "SDL_image could not initialize! SDL_image error" << endl;
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    cout << "SDL_mixer could not initialize! SDL_mixer error" << endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool FileSetUp() {
    bool success = true;

    if (!loadMedia(renderer)) {
        cout << "failed to load bFont.png" << endl;
        success = false;
    }
    else if (!loadFoodMedia(renderer)) {
        cout << "failed to load classic.png" << endl;
        success = false;
    }
    else if (!loadPlayerMedia(renderer)) {
        cout << "failed to load Sbomber.png" << endl;
        success = false;
    }
    else if (!loadBackMedia(renderer)) {
        cout << "failed to load Back.png" << endl;
        success = false;
    }
    else if (!loadMusicMedia()) {
        cout << "failed to load music and sound" << endl;
    }
    PlayMainTheme();

    return success;
}

void Menu(SDL_Renderer* gRenderer) {
    SDL_RenderClear(gRenderer);
    renderBack(24, 24, gRenderer);
    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* argv[]) {


    int slength = 0;

    vector <int> tailX;
    vector <int> tailY;

    int scale = 24;
    int wscale = 24;

    // saving the snake previous state
    int x = 0;
    int y = 0;
    int preX = 0;
    int preY = 0;

    bool UP = false;
    bool DOWN = false;
    bool RIGHT = false;
    bool LEFT = false;

    bool inPutThisFrame = false;
    bool relapse = false;

    // window
    //renderer

    if (!initial(scale, wscale)) {
        cout << "could not...." << endl;
    }

    if (!FileSetUp()) {
        cout << "failed to load file!" << endl;
    }

    // the snake cell rectangles detail
    SDL_Rect snakeBlock;
    snakeBlock.x = 0;
    snakeBlock.y = 0;
    snakeBlock.h = 0;
    snakeBlock.w = 0;

    // the food rectangle detail
    SDL_Rect food;
    food.x = 0;
    food.y = 0;
    food.h = scale;
    food.w = scale;

    pair <int, int> foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
    food.x = foodloca.first;
    food.y = foodloca.second;

    cout << food.x << "   " << food.y << endl;

    float time = SDL_GetTicks() / 100;

    int frame = 0;

    bool MenuPlay = true;
    bool quit = false;

    while (!quit) {

        float newtime = SDL_GetTicks() / 75;
        float deltatime = newtime - time;
        time = newtime;
        bool checkCol = false;

        inPutThisFrame = false;


        if (MenuPlay) {

            while (SDL_PollEvent(&event) != 0) {
                //User requests quit
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            if (!MenuState(renderer, scale, wscale, event)) {
                MenuPlay = false;
                StopMainTheme();
            }

        }
        else {


            if (slength > 575) {
                youWin(renderer, event, scale, wscale, slength);
                x = 0;
                y = 0;
                UP = false;
                RIGHT = false;
                DOWN = false;
                LEFT = false;
                slength = 0;
                relapse = false;

                foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
                if (food.x == -100, food.y == -100) {
                    relapse = true;
                }
                food.x = foodloca.first;
                food.y = foodloca.second;
            }


            if (SDL_PollEvent(&event)) {

                if (event.type == SDL_QUIT) {
                    exit(0);
                }


                if (event.type == SDL_KEYDOWN && inPutThisFrame == false) {
                    if (DOWN == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
                        UP = true;
                        LEFT = false;
                        RIGHT = false;
                        DOWN = false;
                        inPutThisFrame = true;

                        PlaySoundEffect(1);
                    }
                    else if (RIGHT == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        UP = false;
                        LEFT = true;
                        RIGHT = false;
                        DOWN = false;
                        inPutThisFrame = true;
                        PlaySoundEffect(1);
                    }
                    else if (UP == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        UP = false;
                        LEFT = false;
                        RIGHT = false;
                        DOWN = true;
                        inPutThisFrame = true;
                        PlaySoundEffect(1);
                    }
                    else if (LEFT == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        UP = false;
                        LEFT = false;
                        RIGHT = true;
                        DOWN = false;
                        inPutThisFrame = true;
                        PlaySoundEffect(1);
                    }
                }
            }

            // if snake go beyond the map, let it go out of the wall being opposite to its direction

            if (x >= scale * 24)
                x = 0;
            if (x < 0)
                x = (scale - 1) * 24;
            if (y >= scale * 24)
                y = 0;
            if (y < 0)
                y = (scale - 1) * 24;

            preX = x;
            preY = y;

            if (UP)
                y -= deltatime * scale;
            else if (DOWN)
                y += deltatime * scale;
            else if (RIGHT)
                x += deltatime * scale;
            else if (LEFT)
                x -= deltatime * scale;


            if (relapse == true) {

                relapse = false;
                foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
                food.x = foodloca.first;
                food.y = foodloca.second;

                if (food.x == -100 && food.y == -100) {
                    relapse = true;
                }

            }

            if ((checkCol = checkCollision(food.x, food.y, x, y)) == true) {
                foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
                food.x = foodloca.first;
                food.y = foodloca.second;

                if (food.x == -100 && food.y == -100) {
                    relapse = true;
                }

                slength++;
            }

            if (deltatime * scale == 24) {

                if (tailX.size() != slength) {
                    tailX.push_back(preX);
                    tailY.push_back(preY);
                }

                for (int i = 0; i < slength; i++) {
                    if (i > 0) {
                        tailX[i - 1] = tailX[i];
                        tailY[i - 1] = tailY[i];
                    }
                }
                if (slength > 0) {
                    tailX[slength - 1] = preX;
                    tailY[slength - 1] = preY;
                }
            }

            for (int i = 0; i < slength; i++) {
                if (x == tailX[i] && y == tailY[i]) {
                    gameOver(renderer, event, scale, wscale, slength);
                    x = 0;
                    y = 0;
                    UP = false;
                    RIGHT = false;
                    DOWN = false;
                    LEFT = false;
                    slength = 0;
                    relapse = false;

                    foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
                    if (food.x == -100, food.y == -100) {
                        relapse = true;
                    }
                    food.x = foodloca.first;
                    food.y = foodloca.second;
                }
            }

            //down: 1;
            //left: 2;
            //right: 3;
            //up: 4

            renderBack(scale, wscale, renderer);

            renderFoodSprite(foodloca.first - 55, foodloca.second - 55, frame, renderer);

            if (UP) {
                renderPlayer(renderer, snakeBlock, x, y, scale, tailX, tailY, slength, frame, 4, checkCol);
            }
            else if (DOWN) {
                renderPlayer(renderer, snakeBlock, x, y, scale, tailX, tailY, slength, frame, 1, checkCol);
            }
            else if (LEFT) {
                renderPlayer(renderer, snakeBlock, x, y, scale, tailX, tailY, slength, frame, 2, checkCol);
            }
            else if (RIGHT) {
                renderPlayer(renderer, snakeBlock, x, y, scale, tailX, tailY, slength, frame, 3, checkCol);
            }

            renderScore(renderer, slength, scale, wscale);

            SDL_RenderDrawLine(renderer, 0, 0, 0, scale * wscale);
            SDL_RenderDrawLine(renderer, 0, scale * wscale, scale * wscale, scale * wscale);
            SDL_RenderDrawLine(renderer, scale * wscale, scale * wscale, scale * wscale, 0);
            SDL_RenderDrawLine(renderer, scale * wscale, 0, 0, 0);


            SDL_RenderPresent(renderer);

            //SDL_SetRenderDrawColor (renderer, 255, 105, 105, 255);

            SDL_RenderClear(renderer);

            ++frame;
            if (frame / 1000 >= 4) {
                frame = 0;
            }
        }
    }

    SDL_DestroyWindow(window);
    closeSprite();
    closeMusic();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
