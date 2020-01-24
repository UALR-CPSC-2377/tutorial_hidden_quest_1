/*
* Author:	Sean Orme (based on the work of Dr. Keith Bush)
*			UALR
* 
* Date:		September 8, 2019
*
* File:		quest.1.cpp
*
* Purpose:	The purpose of this homework is to review Programming I topics covering
*           file input/output, header/object files, random number generation seeding and
*           usage, as well as linking with the SDL graphics libraries
*/

#include <cstdlib> 
#include <ctime> 
#include <string>
#include <iostream>

#include "pch.h"
//Task 1: Install Libaries and Get the GUI Running
#include "GUI.h"

#include "engine.h"
#include "constants.h"

using namespace std;

int main(int argc, char *argv[]){
	//Construct GUI
	GUI gui;

	//Create array of Objects:
	
	const int maxObjects{ (gui.numColumns / 16)*(gui.numRows / 16) + 1 };
	Object objects[maxObjects];
	
	//Initialize the game's data source
	string gameFile("./Assets/Config/game.txt");

	//Task 3: Load block structure from a file
	int numObjects{ loadBlockData(gameFile, objects, gui) };
	
	//set last object to player!
	numObjects++;
	objects[numObjects].type = Type::player;

	//Task 4: Randomize Samus Sprite Appearance
	randomPlayerData(numObjects, objects, gui);	

	//Initialize Termination Criteria
	bool quit = false;
	
	//While the user hasn't quit
	while(quit == false){
		
		//GUI waits for mouse events
		while(gui.observeEvent()){

			//GUI transmits quit event
			if(gui.quitGame()){

				quit=true;

			}

		}

		//Task 5: Pass Game State Data to the GUI
		gui.displayGameState(numObjects, objects);
	}

	//Return
	return 0;

}