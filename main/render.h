#include <iostream>
#include <SDL.h>
#include <vector>

using namespace std;

void renderPlayer(SDL_Renderer* renderer, SDL_Rect snakeBlock, int x, int y, int scale, vector <int> tailX, vector<int> tailY, int slength, int frame, int state, bool checkCol);

void renderFood(SDL_Renderer* renderer, SDL_Rect food);

