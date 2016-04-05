#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	// TODO 5: Initialize all texture pointers to nullptr
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		textures[i] = nullptr;
	}
}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	// TODO 6: Free all textures
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		if (textures[i])
		{
			SDL_DestroyTexture(textures[i]);
		}
	}
	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	// TODO 2: Load an image from a path (must be a png)
	// and check for errors
	SDL_Surface *image;
	image = IMG_Load(path);
	if (!image) 
	{
		LOG("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}

	// TODO 3: Once your have the SDL_surface*, you need to create
	// a texture from it to return it (check for errors again)
	SDL_Texture* texture = SDL_CreateTextureFromSurface(App->render->renderer, image);
	if (!texture)
	{
		LOG("SDL_CreateTextureFromSurface: %s\n", IMG_GetError());
		// handle error
	}
	
	// TODO 4: Before leaving, remember to free the surface and
	// add the texture to our own array so we can properly free them
	SDL_FreeSurface(image);
	textures[last_texture++] = texture;
	
	return nullptr;
}
