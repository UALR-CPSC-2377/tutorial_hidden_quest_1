#ifndef CONSTANTS_H
#define CONSTANTS_H
				//0		1			2		3			4		5			6		7		8
enum class Type{none, block, belowBlock, belowBlock2, wall1, wall2, waterSurface, water, player, numTypes};
struct Position
{
	int x;
	int y;
};
struct Dimensions
{
	int width;
	int height;
};

struct Object
{
	Type type;

	Position position{ 0,0 };
	Dimensions dimensions{ 0,0 };

	bool top{ false };
	int spriteID{ 0 };
};




#endif