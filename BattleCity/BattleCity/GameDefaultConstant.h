#ifndef  __GAME_DEFAULT_CONSTANT__
#define  __GAME_DEFAULT_CONSTANT__
#include <sstream>
#include <iostream>
//player default value
#define DEFAULT_PLAYER_LIFE 3
#define DEFAULT_PLAYER_POSITION_X	100
#define DEFAULT_PLAYER_POSITION_Y	400
#define DEFAULT_PLAYER_SPEED_X 2
#define DEFAULT_PLAYER_SPEED_Y 2
#define DEFAULT_IMMORTAL_TIME 5
#define DEFAULT_PLAYER_LEVEL 1
#define DEFAULT_PLAYER_HP 1
#define PLAYER_SPRITE_UP_PATH    "0.png"
#define PLAYER_SPRITE_LEFT_PATH  "1.png"
#define PLAYER_SPRITE_DOWN_PATH  "2.png"
#define PLAYER_SPRITE_RIGHT_PATH "3.png"
//Sprite
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define NUMB_OF_SPRITE 1
#define SPRITE_PER_ROW 1

//Dynamic Object ID
#define ID_PLAYER 1
#define ID_LIGHT_TANK 2
#define ID_MEDIUM_TANK 3
#define ID_HEAVY_TANK 4
#define ID_SUPER_HEAVY_TANK 5

//Static Object
#define ID_BRICKWALL 6
#define ID_STEELWALL 7
#define ID_TREES	 8
#define ID_WATER	 9
#define IF_ICE		 10

//Map default value
#define NUM_ROW_TILE	52
#define NUM_COLUMN_TILE 52
#define TILE_WIDTH		8
#define TILE_HEIGHT		8

//Image paths
#define MAP_RESOURCE_PATH_BRICKWALL	"Resource\\Map\\Brick\\BrickWall.png"
#define MAP_RESOURCE_PATH_STEELWALL	"Resource\\Map\\Steel\\SteelWall.png"

//Bullet
#define BULLET_SPEED_X 2
#define BULLET_SPEED_Y 2
#define BULLET_SPRITE_UP_PATH		"bullet-up.png"
#define BULLET_SPRITE_DOWN_PATH		"bullet-down.png"
#define BULLET_SPRITE_LEFT_PATH		"bullet-left.png"
#define BULLET_SPRITE_RIGHT_PATH	"bullet-right.png"
#define BULLET_WIDTH 7
#define BULLET_HEIGHT 11

//Object State
#define STATE_IMMORTAL_NONE 0
#define SPEED_NO 0

#endif // ! __GAME_DEFAULT_CONSTANT__
