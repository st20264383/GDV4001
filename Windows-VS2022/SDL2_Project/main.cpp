#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "SDL_image.h"

#include "SDL.h"


int main(int argc, char** argv)
{
	// Create The game Window //
	SDL_Window* gameWindow = nullptr;
	SDL_Renderer* gameRenderer = nullptr;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	IMG_Init(IMG_INIT_JPG);

	gameWindow = SDL_CreateWindow
	(
		"Polygon Assault",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_SHOWN
	);

	gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);

	// Draw the Background //
	SDL_Surface* temp = nullptr;
	SDL_Texture* backgroundTexture = nullptr;
	
	temp = IMG_Load("assets/images/SpaceBG.png");
	backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, temp);

	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);
	SDL_RenderCopy(gameRenderer, backgroundTexture, NULL, NULL);
	SDL_RenderPresent(gameRenderer);

	SDL_FreeSurface(temp);
	temp = nullptr;

	// Draw the player Model //
	SDL_Texture* playerTexture = nullptr;

	SDL_Rect playerSourceRectangle;

	const int PLAYER_W = 65;
	const int PLAYER_H = 65;

	SDL_Rect playerDestRectangle;

	temp = IMG_Load("assets/images/playerSprite.png");
	playerTexture = SDL_CreateTextureFromSurface(gameRenderer, temp);

	playerSourceRectangle.x = 0;
	playerSourceRectangle.y = 0;
	playerSourceRectangle.w = PLAYER_W;
	playerSourceRectangle.h = PLAYER_H;

	playerDestRectangle.x = 400;
	playerDestRectangle.y = 400;
	playerDestRectangle.w = PLAYER_W;
	playerDestRectangle.h = PLAYER_H;

	SDL_RenderCopy(gameRenderer, playerTexture, &playerSourceRectangle, &playerDestRectangle);
	SDL_RenderPresent(gameRenderer);

	SDL_FreeSurface(temp);
	temp = nullptr;

	SDL_Delay(10000); //Temp code to keep window open

	//Clean up
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	exit(EXIT_SUCCESS);
}