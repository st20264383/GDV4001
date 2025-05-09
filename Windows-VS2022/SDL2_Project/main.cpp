#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "SDL_image.h"
#include "ctime"

#include "SDL.h"


int main(int argc, char** argv)
{
	// Window Control //
	SDL_Event event;
	bool quit = false;

	// Keyboard States //
	const Uint8* keyStates;

	// Time Variables //
	unsigned int currentTimeIndex;
	unsigned int prevTimeIndex = 0;
	unsigned int timeDelta;
	float timeDeltaInSeconds;

	// Create The game Window //
	SDL_Window* gameWindow = nullptr;
	SDL_Renderer* gameRenderer = nullptr;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	IMG_Init(IMG_INIT_JPG);
	int sdl_status = SDL_Init(SDL_INIT_EVERYTHING);

	gameWindow = SDL_CreateWindow
	(
		"Polygon Assault",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_SHOWN
	);

	gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);

	// Track Keystates //
	keyStates = SDL_GetKeyboardState(NULL);

	// Movement Variables //
	float verticalInput;
	float horizontalInput;
	float playerSpeed = 250.0f;
	float playerX = 400.0f;
	float playerY = 400.0f;

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

	const int PLAYER_W = 64;
	const int PLAYER_H = 64;

	SDL_Rect playerDestRectangle;

	temp = IMG_Load("assets/images/playerSpritesheet.png");
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

	prevTimeIndex = SDL_GetTicks();

	// Event loop //
	
	while (!quit)
	{
		currentTimeIndex = SDL_GetTicks();
		timeDelta = currentTimeIndex - prevTimeIndex;
		timeDeltaInSeconds = timeDelta * 0.001f;

		prevTimeIndex = currentTimeIndex;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					quit = true;
				break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
					}
				break;

				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
					default:
						break;
					}
				break;
				default:
					break;
			}
		}

		if (keyStates[SDL_SCANCODE_UP])
			verticalInput = -1.0f;
		else
		{
			if (keyStates[SDL_SCANCODE_DOWN])
				verticalInput = 1.0f;
			else
				verticalInput = 0.0f;
		}
		if (keyStates[SDL_SCANCODE_LEFT])
			horizontalInput = -1.0f;
		else
		{
			if (keyStates[SDL_SCANCODE_RIGHT])
				horizontalInput = 1.0f;
			else
				horizontalInput = 0.0f;
		}

		float xVelocity = verticalInput * playerSpeed;
		float yVelocity = horizontalInput * playerSpeed;

		float yMovement = timeDeltaInSeconds * xVelocity;
		float xMovement = timeDeltaInSeconds * yVelocity;

		playerX += xMovement;
		playerY += yMovement;

		playerDestRectangle.y = round(playerY);
		playerDestRectangle.x = round(playerX);

		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gameRenderer);
		SDL_RenderCopy(gameRenderer, backgroundTexture, NULL, NULL);
		SDL_RenderCopy(gameRenderer, playerTexture, &playerSourceRectangle, &playerDestRectangle);
		SDL_RenderPresent(gameRenderer);
	}

	//Clean up
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	exit(EXIT_SUCCESS);
}