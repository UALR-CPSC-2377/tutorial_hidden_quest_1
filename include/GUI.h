#ifndef GUI_H
#define GUI_H


#include <vector>
#include <map>

//GUI definitions
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

//User-defined tools
#include "Texture.h"
#include "constants.h"

class GUI
{

public:
	//GUI Constant
	const static Dimensions screenDimensions;
	enum { numRows = 224 / 16, numColumns = 336 / 16 };

	GUI();
	~GUI();
	int observeEvent();
	bool quitGame();
	void displayGameState(const int numObjects, const Object objects[]);
	
	Dimensions getObjectDimensions(const Object & object) const;
	


private:

	//
	// PRIVATE METHODS
	//
	void initGUI();
	void loadMedia();
	void cleanUp();

	//
	//PRIVATE MEMBERS
	//
	bool quit;

	//Window(s) to display graphics
	SDL_Window* window;

	//Hardware accelerated renderer
	SDL_Renderer* renderer;

	
		
	//The texture to be used for drawing objects;
	std::map<Type, Texture*> objectTextures;
	
	//The clipping that will be used for player
	std::vector<SDL_Rect> simonClips;
	
	//The event structure that will be used
	SDL_Event event;

public:
	int getNumPlayerSprites() const { return simonClips.size(); }
};

#endif
