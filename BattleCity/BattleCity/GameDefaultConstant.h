#ifndef  __GAME_DEFAULT_CONSTANT__
#define  __GAME_DEFAULT_CONSTANT__
#include <sstream>
#include <iostream>
#include "DefaultConstant.h"
//player default value
#define DEFAULT_PLAYER_LIFE 3
#define DEFAULT_PLAYER_POSITION_X	100
#define DEFAULT_PLAYER_POSITION_Y	500
#define DEFAULT_PLAYER_SPEED_X 4
#define DEFAULT_PLAYER_SPEED_Y 4
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
//Static Object default size
#define DEFAULT_STATIC_WIDTH 8
#define DEFAULT_STATIC_HEIGHT 8
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
#define POS_MAP_TOP_LEFT_X 92
#define POS_MAP_TOP_LEFT_Y 60
#define NUM_ROW_TILE	52
#define NUM_COLUMN_TILE 52
#define TILE_WIDTH		8
#define TILE_HEIGHT		8
#define POS_EAGLE_IN_MATRIX_X 48
#define POS_EAGLE_IN_MATRIX_Y 24
#define MAP_RESOURCE_PATH_BRICKWALL	"Resource\\Map\\Brick\\BrickWall.png"
#define MAP_RESOURCE_PATH_STEELWALL	"Resource\\Map\\Steel\\SteelWall.png"
#define MAP_RESOURCE_PATH_EAGLE	"Resource\\Map\\Eagle.png"
#define MAP_RESOURCE_PATH_BG	"Resource\\Map\\bg.png"
//Info Right map default value
#define POS_LIST_ENEMY_ICON_TOP_LEFT_X 540
#define POS_LIST_ENEMY_ICON_TOP_LEFT_Y 92
#define RESOURCE_PATH_ENEMY_ICON	"Resource\\Other\\miniarmy.png"
#define RESOURCE_PATH_TANKLIFE_ICON	"Resource\\Other\\tanklife.png"
#define RESOURCE_PATH_FLAG_LEVEL_ICON	"Resource\\Other\\flag.png"
#define NUM_ENEMY 20
//Bullet
#define BULLET_SPEED_X 3
#define BULLET_SPEED_Y 3
#define BULLET_SPRITE_UP_PATH		"bullet-up.png"
#define BULLET_SPRITE_DOWN_PATH		"bullet-down.png"
#define BULLET_SPRITE_LEFT_PATH		"bullet-left.png"
#define BULLET_SPRITE_RIGHT_PATH	"bullet-right.png"
#define BULLET_WIDTH 7
#define BULLET_HEIGHT 11

//Object State
#define STATE_IMMORTAL_NONE 0
#define SPEED_NO 0

//Object type
#define DYNAMIC_OBJECT 100
#define STATIC_OBJECT 101

//GameState default
#define NUMBER_OF_STATE 3
#define IMAGE_MAIN_MENU_GAME_PATH "Resource\\Other\\mainmenu.png"
#define RESOURCE_PATH_NUMBER	"Resource\\Other\\number.png"

//Default enemy position
#define DEFAULT_TOP_LEFT D3DXVECTOR2(0.0f,200.0f)
#define DEFAULT_TOP_MIDDLE D3DXVECTOR2(Win_WIDTH/2- SPRITE_WIDTH/2, 0.0f)
#define DEFAULT_TOP_RIGHT D3DXVECTOR2(Win_WIDTH - SPRITE_WIDTH,0.0f)
//Default Light Tank Value
#define  LIGHT_TANK_SPEED_X 3
#define	 LIGHT_TANK_SPEED_Y 3
#define  LIGHT_TANK_BULLET_SPEED_X 2
#define  LIGHT_TANK_BULLET_SPEED_Y 2
#define  LIGHT_TANK_RESOURCE_DOWN "down-light.png"
#define  LIGHT_TANK_RESOURCE_UP "up-light.png"
#define	 LIGHT_TANK_RESOURCE_LEFT "left-light.png"
#define  LIGHT_TANK_RESOURCE_RIGHT "right-light.png"
//Default Medium Tank Value
#define  MEDIUM_TANK_SPEED_X 2
#define	 MEDIUM_TANK_SPEED_Y 2
#define  MEDIUM_TANK_BULLET_SPEED_X 2
#define  MEDIUM_TANK_BULLET_SPEED_Y 2
#define  MEDIUM_TANK_RESOURCE_DOWN "down-medium.png"
#define  MEDIUM_TANK_RESOURCE_UP "up-medium.png"
#define	 MEDIUM_TANK_RESOURCE_LEFT "left-medium.png"
#define  MEDIUM_TANK_RESOURCE_RIGHT "right-medium.png"
//Default Heavy Tank Value
#define  HEAVY_TANK_SPEED_X 2
#define	 HEAVY_TANK_SPEED_Y 2
#define  HEAVY_TANK_BULLET_SPEED_X 3
#define  HEAVY_TANK_BULLET_SPEED_Y 3
#define  HEAVY_TANK_RESOURCE_DOWN "down-heavy.png"
#define  HEAVY_TANK_RESOURCE_UP "up-heavy.png"
#define	 HEAVY_TANK_RESOURCE_LEFT "left-heavy.png"
#define  HEAVY_TANK_RESOURCE_RIGHT "right-heavy.png"
//Default Super Heavy Tank Value
#define  SUPER_HEAVY_TANK_SPEED_X 2
#define	 SUPER_HEAVY_TANK_SPEED_Y 2
#define  SUPER_HEAVY_TANK_BULLET_SPEED_X 2
#define  SUPER_HEAVY_TANK_BULLET_SPEED_Y 2
#define  SUPER_HEAVY_TANK_RESOURCE_DOWN "down-super.png"
#define  SUPER_HEAVY_TANK_RESOURCE_UP "up-super.png"
#define	 SUPER_HEAVY_TANK_RESOURCE_LEFT "left-super.png"
#define  SUPER_HEAVY_TANK_RESOURCE_RIGHT "right-super.png"
//Ally Bullet
#define ALLY_PLAYER 1
#define ALLY_ENEMY 2
#endif // ! __GAME_DEFAULT_CONSTANT__
