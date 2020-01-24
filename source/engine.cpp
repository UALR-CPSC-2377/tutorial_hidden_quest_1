#include <fstream>
#include <string>
#include <iostream>
#include <random>

#include "engine.h"
#include "constants.h"
#include "GUI.h"

using namespace std;


int loadBlockData(const string & gameFile, Object objects[], const GUI & gui)
{
	//Declare and open filestream
	fstream fin;
	fin.open(gameFile.c_str(), ios::in);

	//topCheck keeps track of whether there was a block in this column on the previous row 
	//to decide Block::top
	bool topCheck[gui.numColumns]{};
	int numObjects{ 0 };
	//while we are not past the edge of the screen.
	for (int row{ 0 }; row < gui.numRows; row++)
	{
		for (int column{ 0 }; column < gui.numColumns; column++)
		{
			int temp;
			fin >> temp;
			if ((Type)temp == Type::none)
			{
				topCheck[column] = true;
			}
			else
			{
				objects[numObjects].type = (Type) temp;
				objects[numObjects].position.x = column * gui.getObjectDimensions(objects[numObjects]).width;
				objects[numObjects].position.y = row * gui.getObjectDimensions(objects[numObjects]).height;
				objects[numObjects].top = topCheck[column];
				objects[numObjects].dimensions = gui.getObjectDimensions(objects[numObjects]);
				topCheck[column] = false;

				++numObjects;
			}
		}
	}
	fin.close();
	return numObjects;
}

void randomPlayerData(const int numObjects, Object objects[], const GUI & gui)
{
	//find the player
	int playerID{ 0 };
	while(objects[playerID].type != Type::player)
	{
		playerID++;
	}

	//create the random engine and distributions
	random_device seed;
	default_random_engine engine(seed());
	uniform_int_distribution<int> rSimonSprite(0, gui.getNumPlayerSprites() - 1);
	//Pick a random sprite from the sprite sheet
	objects[playerID].spriteID = rSimonSprite(engine);
	objects[playerID].dimensions = gui.getObjectDimensions(objects[playerID]);

	uniform_int_distribution<int> rSimonX(0, GUI::screenDimensions.width - objects[playerID].dimensions.width);	

	//Pick a random center x location for the sprite.
	objects[playerID].position.x = rSimonX(engine);
	//Figure out what the highest height below the sprite would be.
	objects[playerID].position.y = 
		getMaxYOfBlock(objects[playerID], objects, numObjects) - objects[playerID].dimensions.height;
}

bool isInSameColumn(const Object & player, const Object & block)
{
	auto playerLeft{ player.position.x };
	auto playerRight{ player.position.x + player.dimensions.width};

	auto blockLeft{ block.position.x };
	auto blockRight{ block.position.x + block.dimensions.width };

	return
		(
			//left side of block under player
		(blockLeft >= playerLeft && blockLeft <= playerRight)
			//or right side of block under player
			|| (blockRight >= playerLeft && blockRight <= playerRight)
			// or player in between block's left and right
			|| (playerLeft >= blockLeft && playerLeft <= blockRight)
			);

}

int getMaxYOfBlock(const Object & player, const Object objects[], int numObjects)
{
	int maxY{ GUI::screenDimensions.height };
	for (int i{ 0 }; i < numObjects; i++)
	{//the order is carefully chosen so that the most blocks are eliminated with each comparison!
		if (
			objects[i].type != Type::player 
			&& objects[i].top
			&& maxY > objects[i].position.y
			&& isInSameColumn(player, objects[i]))
		{
			maxY = objects[i].position.y;
		}
	}
	return(maxY);

}


