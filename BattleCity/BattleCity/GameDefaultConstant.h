#ifndef  __GAME_DEFAULT_CONSTANT__
#define  __GAME_DEFAULT_CONSTANT__
#include <sstream>
#include <iostream>
#include "DefaultConstant.h"
//player default value
#define DEFAULT_PLAYER_LIFE 3
#define DEFAULT_PLAYER_POSITION_X	200
#define DEFAULT_PLAYER_POSITION_Y	450
#define DEFAULT_PLAYER_SPEED_X 3
#define DEFAULT_PLAYER_SPEED_Y 3
#define DEFAULT_IMMORTAL_TIME 5
#define DEFAULT_PLAYER_LEVEL 1
#define DEFAULT_PLAYER_HP 1
#define PLAYER_SPRITE_UP_PATH    "Resource\\Player\\0.png"
#define PLAYER_SPRITE_LEFT_PATH  "Resource\\Player\\1.png"
#define PLAYER_SPRITE_DOWN_PATH  "Resource\\Player\\2.png"
#define PLAYER_SPRITE_RIGHT_PATH "Resource\\Player\\3.png"
#define BULLET_DELAY_FPS 0.5
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
#define MAP_WIDTH 450
#define MAP_HEIGHT 450
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
#define RESOURCE_PATH_NUMBER	"Resource\\Other\\number.png"
#define IMAGE_NUMBER_WIDTH 16
#define IMAGE_NUMBER_HEIGHT 16
	//Mainmenu
#define IMAGE_MAIN_MENU_GAME_PATH "Resource\\Other\\mainmenu.png"
#define IMAGE_MAIN_MENU_GAME_WIDTH 670
#define IMAGE_MAIN_MENU_GAME_HEIGHT 568
#define IMAGE_MAIN_MENU_GAME_DEFAULT_POS D3DXVECTOR3(0.0f,600.0f,0.0f)
#define IMAGE_MAIN_MENU_GAME_DEFAULT_SPEED_UP 2
#define IMAGE_SELECTOR_PATH		"Resource\\Other\\selector.png"
#define IMAGE_SELECTOR_WIDTH 32
#define IMAGE_SELECTOR_HEIGHT 32
#define SELECTOR_SPEED_CHANGE 15
#define IMAGE_SELECTOR_POS_PLAY D3DXVECTOR3(200.0f,300.0f,0.0f)
#define IMAGE_SELECTOR_POS_INSTRUCTION D3DXVECTOR3(200.0f,335.0f,0.0f)
	//Starting
#define IMAGE_STATE_PATH "Resource\\Other\\state.png"
#define IMAGE_STATE_WIDTH 80
#define IMAGE_STATE_HEIGHT 16
#define IMAGE_STATE_POS D3DXVECTOR3(244.0f,252.0f,0.0f)
#define IMAGE_BG_STARTING_STATE_PATH "Resource\\Other\\bgstartingstate.png"
#define IMAGE_BG_STARTING_WIDTH 670
#define IMAGE_BG_STARTING_HEIGHT 0
#define SPEED_SCROLLING_BG 8
#define IMAGE_BG_STARTING_TOP_POS D3DXVECTOR3(0.0f,0.0f,0.0f)
#define IMAGE_BG_STARTING_BOTTOM_POS D3DXVECTOR3(0.0f,284.0f,0.0f)


//Default enemy position
#define DEFAULT_TOP_LEFT D3DXVECTOR2(0.0f,200.0f)
#define DEFAULT_TOP_MIDDLE D3DXVECTOR2(Win_WIDTH/2- SPRITE_WIDTH/2, 0.0f)
#define DEFAULT_TOP_RIGHT D3DXVECTOR2(Win_WIDTH - SPRITE_WIDTH,0.0f)
//Default Light Tank Value
#define  LIGHT_TANK_SPEED_X 1
#define	 LIGHT_TANK_SPEED_Y 1
#define  LIGHT_TANK_BULLET_SPEED_X 2
#define  LIGHT_TANK_BULLET_SPEED_Y 2
#define  LIGHT_TANK_RESOURCE_DOWN	"down-light.png"
#define  LIGHT_TANK_RESOURCE_UP		"up-light.png"
#define	 LIGHT_TANK_RESOURCE_LEFT	"left-light.png"
#define  LIGHT_TANK_RESOURCE_RIGHT	"right-light.png"
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
