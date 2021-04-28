#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "State.h"
#include "Sprite.h"
#include "SoundTheme.h"
#include "MenuEffect.h"

using namespace std;

int textFrame = 0;
int directFrame = 1;

void gameOver(SDL_Renderer* renderer, SDL_Event event, int scale, int wscale, int slength) {

    PlaySoundEffect(2);

    renderLetterBiggerSize("GameOver", -1, 100, renderer);

    renderLetter((string("Score:") + to_string(slength * 10)).c_str(), -1, 230, renderer);

    renderLetter("ENTER", -1, 300, renderer);

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


//this is for effect the text:
void textingEffect(std::string text, SDL_Renderer* gRenderer, int pos) {
    // position 240:
    if (textFrame / 400 == 1) {
        renderLetter(text, -1, pos, gRenderer);
    }
}


bool onPlayEntering = true;
bool onPlayInstruction = false;
bool onPlaySetting = false;

bool HelpStateOn = false;
bool SettingStateOn = false;
bool MainMenuStateOn = true;
bool MusicStateIsOn = true;
bool MusicStateIsOff = false;


void HelpState(SDL_Renderer* renderer, SDL_Event event) {

    if (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            exit(0);
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            HelpStateOn = false;
        }
    }


    renderLetter("Help", -1, 140, renderer);

    renderLetter("Press up to move up", 10, 200, renderer);
    renderLetter("Press down to move down", 10, 260, renderer);
    renderLetter("Press left to move left", 10, 320, renderer);
    renderLetter("Press right to move", 10, 380, renderer);
    renderLetter("right", 0, 420, renderer);



    SDL_RenderPresent(renderer);
}

void SetingState(SDL_Renderer* renderer, SDL_Event event) {

    if (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            exit(0);
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            SettingStateOn = false;
        }
    }

    if (textFrame / 400 == 2 || textFrame / 400 == 3) {
        renderLetter("Main_Theme", -1, 200, renderer);
    }


    if (MusicStateIsOn) {
        renderLetter("ON", -1, 240, renderer);
    }
    else {
        renderLetter("OFF", -1, 240, renderer);
    }

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
            if (MusicStateIsOn) {
                MusicStateIsOn = false;
            }
            else {
                MusicStateIsOn = true;
            }
        }
    }

    textFrame++;
    if (textFrame / 400 >= 3) {
        textFrame = 0;
    }

    SDL_RenderPresent(renderer);
}

bool MenuState(SDL_Renderer* renderer, int scale, int wscale, SDL_Event event) {


    SDL_RenderClear(renderer);
    //render the back ground

    renderBack(scale, wscale, renderer);
    //renderLetter("Snake", 10, 30, renderer);
    renderLetterBiggerSize("Snake", 0, 30, renderer);
    renderPlayerEffect(renderer);

    if (onPlayInstruction && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
        HelpStateOn = true;
        SettingStateOn = false;
        MainMenuStateOn = false;
    }

    if (onPlaySetting && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
        SettingStateOn = true;
        HelpStateOn = false;
        MainMenuStateOn = false;
    }


    if (HelpStateOn) {
        HelpState(renderer, event);
    }
    else if (SettingStateOn) {
        SetingState(renderer, event);
    }
    else {

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) {
                exit(0);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_UP && directFrame > 1) {
                directFrame--;

            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && directFrame <= 2) {
                directFrame++;

            }

        }

        // std::cout<<directFrame<<std::endl;

        if (directFrame == 1) {
            onPlayEntering = true;
            onPlayInstruction = false;
            onPlaySetting = false;
        }
        else if (directFrame == 2) {
            onPlayEntering = false;
            onPlayInstruction = true;
            onPlaySetting = false;
        }
        else if (directFrame == 3) {
            onPlayEntering = false;
            onPlayInstruction = false;
            onPlaySetting = true;
        }

        if (onPlayEntering) {
            renderLetter("->", 120, 240, renderer);
            textingEffect("Play", renderer, 240);
            renderLetter("Help", -1, 300, renderer);
            renderLetter("Setting", -1, 360, renderer);
        }
        else if (onPlayInstruction) {
            renderLetter("->", 120, 300, renderer);
            textingEffect("Help", renderer, 300);
            renderLetter("Play", -1, 240, renderer);
            renderLetter("Setting", -1, 360, renderer);
        }
        else if (onPlaySetting) {
            renderLetter("->", 120, 360, renderer);
            textingEffect("Setting", renderer, 360);
            renderLetter("Help", -1, 300, renderer);
            renderLetter("Play", -1, 240, renderer);
        }

        SDL_RenderPresent(renderer);

        textFrame++;
        if (textFrame / 400 >= 3) {
            textFrame = 0;
        }

    }
    //SDL_SetRenderDrawColor (renderer, 255, 105, 105, 255)
    if (onPlayEntering && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
        return false;
    }

    return true;

}
