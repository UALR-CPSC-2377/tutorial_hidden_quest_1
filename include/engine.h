#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "constants.h"
#include "GUI.h"

int loadBlockData(const std::string & gameFile, Object objects[], const GUI & gui);
void randomPlayerData(const int numObjects, Object objects[], const GUI & gui);
int getMaxYOfBlock(const Object & player, const Object objects[], int numObjects);

#endif