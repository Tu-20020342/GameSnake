#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include "SoundTheme.h"

using namespace std;

Mix_Music* gMusic = NULL;

Mix_Chunk* gScratch = NULL;

Mix_Chunk* MoveEffect = NULL;

Mix_Chunk* yahEffect = NULL;

void closeMusic() {
    Mix_FreeChunk(gScratch);
    gScratch = NULL;

    Mix_FreeMusic(gMusic);
    gMusic = NULL;
}

bool loadMusicMedia() {
    bool success = true;

    gMusic = Mix_LoadMUS("maintheme.wav");
    if (gMusic == NULL) {
        cout << "could not load the beat music" << endl;
    }

    gScratch = Mix_LoadWAV("scratch.wav");
    if (gScratch == NULL) {
        cout << "could not load the scratch sound effect" << endl;
    }

    MoveEffect = Mix_LoadWAV("move.wav");
    if (MoveEffect == NULL) {
        cout << "could not load the move sound effect" << endl;
    }

    yahEffect = Mix_LoadWAV("yah.wav");
    if (yahEffect == NULL) {
        cout << "could not load the yah sound effect" << endl;
    }
    return success;
}

void PlayMainTheme() {
    Mix_PlayMusic(gMusic, -1);
}

void PlaySoundEffect(int track) {
    switch (track) {
    case 1:
        Mix_PlayChannel(-1, MoveEffect, 0);
        break;
    case 2:
        Mix_PlayChannel(-1, yahEffect, 0);
    }
}

void StopMainTheme() {
    Mix_PauseMusic();
}

