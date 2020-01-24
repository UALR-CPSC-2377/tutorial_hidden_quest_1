#include <iostream>
#include <fstream>
#include <string>

#include "GUI.h"
#include "Texture.h"
#include "constants.h"

using namespace std;
const Dimensions GUI::screenDimensions{ 336,224 };
;
GUI::GUI(){

	//Initialize the window
	window = nullptr;

    //Start-up the GUI!
	initGUI();

	//Load in all the images and clip (if necessary)
	loadMedia();

	//Exit criteria
	quit=false;

}

GUI::~GUI(){
	cleanUp();
}

int GUI::observeEvent(){
	return(SDL_PollEvent( &event ));
}

bool GUI::quitGame(){
	return(event.type == SDL_QUIT );
}

void GUI::initGUI(){

	//Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){

		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}

	//Construct and check window construction
	window = SDL_CreateWindow("Castlevania II Clone",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
                    screenDimensions.width, screenDimensions.height, SDL_WINDOW_SHOWN);

	if(window==nullptr){

			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			exit(1);
	}

	//Construct and check renderer construction
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr){

		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		exit(1);

	}

}

void GUI::loadMedia(){
	
	//Open Samus Sprite Sheet Forward
	objectTextures[Type::player]= new Texture();
	objectTextures[Type::player]->load(renderer,"./Assets/Images/simon.png");

	//Parse Samus Sprite Sheet Forward
	
		
	int i = 0;
	//stand Right
	//0
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 0;
	simonClips[i].y = 0;
	simonClips[i].w = 16;
	simonClips[i].h = 30;
	i++;
	//walking Right
	//1
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 30;
	simonClips[i].y = 0;
	simonClips[i].w = 11;
	simonClips[i].h = 30;
	i++;
	//2
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 55;
	simonClips[i].y = 0;
	simonClips[i].w = 16;
	simonClips[i].h = 30;
	i++;
	//crouch Right
	//3
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 86;
	simonClips[i].y = 0;
	simonClips[i].w = 16;
	simonClips[i].h = 30;
	i++;

	//attack Right
	//4
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 110;
	simonClips[i].y = 0;
	simonClips[i].w = 32;
	simonClips[i].h = 30;
	i++;
	//5
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 157;
	simonClips[i].y = 0;
	simonClips[i].w = 31;
	simonClips[i].h = 30;
	i++;
	//6
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 209;
	simonClips[i].y = 0;
	simonClips[i].w = 46;
	simonClips[i].h = 30;
	i++;

	//**************LEFT********************************************
	//stand Left
	//7
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 510;
	simonClips[i].y = 0;
	simonClips[i].w = 16;
	simonClips[i].h = 30;
	i++;
	//walking Left
	//8
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 485;
	simonClips[i].y = 0;
	simonClips[i].w = 11;
	simonClips[i].h = 30;
	i++;
	//9
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 455;
	simonClips[i].y = 0;
	simonClips[i].w = 16;
	simonClips[i].h = 30;
	i++;
	//crouch Left
	//10
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 424;
	simonClips[i].y = 0;
	simonClips[i].w = 16;
	simonClips[i].h = 30;
	i++;

	//attack Left
	//11
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 384;
	simonClips[i].y = 0;
	simonClips[i].w = 32;
	simonClips[i].h = 30;
	i++;
	//12
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 338;
	simonClips[i].y = 0;
	simonClips[i].w = 31;
	simonClips[i].h = 30;
	i++;
	//13
	simonClips.push_back(SDL_Rect());
	simonClips[i].x = 271;
	simonClips[i].y = 0;
	simonClips[i].w = 46;
	simonClips[i].h = 30;
	i++;
	   	 
	//Create the rest of the textures
	objectTextures[Type::block] = new Texture();
	objectTextures[Type::block]->load(renderer,"./Assets/Images/block.png");

	objectTextures[Type::belowBlock] = new Texture();
	objectTextures[Type::belowBlock]->load(renderer, "./Assets/Images/belowBlock.png");

	objectTextures[Type::belowBlock2] = new Texture();
	objectTextures[Type::belowBlock2]->load(renderer, "./Assets/Images/belowBlock2.png");

	objectTextures[Type::wall1] = new Texture();
	objectTextures[Type::wall1]->load(renderer, "./Assets/Images/wall1.png");

	objectTextures[Type::wall2] = new Texture();
	objectTextures[Type::wall2]->load(renderer, "./Assets/Images/wall2.png");

	objectTextures[Type::water] = new Texture();
	objectTextures[Type::water]->load(renderer, "./Assets/Images/water.png");

	objectTextures[Type::waterSurface] = new Texture();
	objectTextures[Type::waterSurface]->load(renderer, "./Assets/Images/waterSuface.png");

	
}

void GUI::cleanUp(){

	//Free the window
	SDL_DestroyWindow(window);
    window = NULL;

    //Free the renderer
   	SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //Free loaded images
	for (auto image : objectTextures)
	{
		image.second->free();
	}
	
    //Quit SDL Subsystems
   	IMG_Quit();
    SDL_Quit();

}

void GUI::displayGameState(const int numObjects, const Object objects[]){

	//Clear screen
	SDL_SetRenderDrawColor(renderer,0,0,0,255);  
	SDL_RenderClear(renderer);

    //Render Blocks
	for(int i=0;i<numObjects;i++){
		if (objects[i].type == Type::player)
		{
			//Render Player
			objectTextures[objects[i].type]->render(renderer, objects[i].position.x, objects[i].position.y, &simonClips[objects[i].spriteID]);
		}
		else
		{
			//render anything else!
			objectTextures[objects[i].type]->render(renderer, objects[i].position.x, objects[i].position.y, NULL);
		}
	}
	
	//Update the visible screen
	SDL_RenderPresent(renderer);
	
}

Dimensions GUI::getObjectDimensions(const Object & object) const
{
	Dimensions dimension;
	if (object.type == Type::player)
	{
		dimension.width = simonClips[object.spriteID].w;
		dimension.height = simonClips[object.spriteID].h;
	}
	else
	{
		dimension.width = (*objectTextures.find(object.type)).second->getWidth();
		dimension.height = (*objectTextures.find(object.type)).second->getHeight();
	}
	return dimension;
}
