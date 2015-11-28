#ifndef  __GAME_DEFAULT_CONSTANT__
#define  __GAME_DEFAULT_CONSTANT__
#include <sstream>
#include <iostream>
#include "DefaultConstant.h"
//player default value
#define DEFAULT_PLAYER_LIFE 3
#define DEFAULT_PLAYER_POSITION_X	236
#define DEFAULT_PLAYER_POSITION_Y	410
#define DEFAULT_PLAYER_SPEED_X 4
#define DEFAULT_PLAYER_SPEED_Y 4
#define PLAYER_SPEED_PROMOTED_X 4
#define PLAYER_SPEED_PROMOTED_Y 4
#define DEFAULT_IMMORTAL_TIME 5000
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
#define ID_BONUS_TANK 6

//// DYNAMIC OBJECT SPEED------------------------25/11/2015
#define DYNAMIC_OBJECT_LOW_SPEED D3DXVECTOR2(2.0f,2.0f)
#define DYNAMIC_OBJECT_HIGH_SPEED D3DXVECTOR2(4.0f,4.0f)

//Static Object
#define ID_BRICKWALL 7
#define ID_STEELWALL 8
#define ID_TREES	 9
#define ID_WATER	 10
#define IF_ICE		 11

//Map default value
#define POS_MAP_TOP_LEFT_X 100
#define POS_MAP_TOP_LEFT_Y 51
#define NUM_ROW_TILE	52
#define NUM_COLUMN_TILE 52
#define TILE_WIDTH		8
#define TILE_HEIGHT		8
#define MAP_WIDTH 417
#define MAP_HEIGHT 417
#define POS_EAGLE_IN_MATRIX_X 48
#define POS_EAGLE_IN_MATRIX_Y 24
#define MAP_RESOURCE_PATH_ENVIRONMENT "Resource\\Map\\Environment.png"
#define MAP_RESOURCE_PATH_EAGLE	"Resource\\Map\\Eagle.png"
#define MAP_RESOURCE_PATH_BG	"Resource\\Map\\bg.png"
#define MAP_NUM_OF_TYPE_OBJ 20


//Info Right map default value
#define POS_LIST_ENEMY_ICON_TOP_LEFT_X 540
#define POS_LIST_ENEMY_ICON_TOP_LEFT_Y 92
#define RESOURCE_PATH_ENEMY_ICON	"Resource\\Other\\miniarmy.png"
#define RESOURCE_PATH_TANKLIFE_ICON	"Resource\\Other\\tanklife.png"
#define RESOURCE_PATH_FLAG_LEVEL_ICON	"Resource\\Other\\flag.png"
#define NUM_ENEMY 20
//Bullet
#define ID_BULLET 20
#define DEFAULT_BULLET_SPEED_X 6
#define DEFAULT_BULLET_SPEED_Y 6
#define BULLET_PROMOTED_SPEED_X 7
#define BULLET_PROMOTED_SPEED_Y 7
#define BULLET_SPRITE_UP_PATH		"bullet-up.png"
#define BULLET_SPRITE_DOWN_PATH		"bullet-down.png"
#define BULLET_SPRITE_LEFT_PATH		"bullet-left.png"
#define BULLET_SPRITE_RIGHT_PATH	"bullet-right.png"
#define BULLET_WIDTH 8
#define BULLET_HEIGHT 8

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
#define IMAGE_MAIN_MENU_GAME_DEFAULT_SPEED_UP 3
#define IMAGE_SELECTOR_PATH		"Resource\\Other\\selector.png"
#define IMAGE_SELECTOR_WIDTH 32
#define IMAGE_SELECTOR_HEIGHT 32
#define SELECTOR_SPEED_CHANGE 100
#define IMAGE_SELECTOR_POS_PLAY D3DXVECTOR3(200.0f,300.0f,0.0f)
#define IMAGE_SELECTOR_POS_INSTRUCTION D3DXVECTOR3(200.0f,335.0f,0.0f)
	//Starting
#define IMAGE_STATE_PATH "Resource\\Other\\state.png"
#define IMAGE_STATE_WIDTH 80
#define IMAGE_STATE_HEIGHT 16
#define IMAGE_STATE_POS D3DXVECTOR3(250.0f,252.0f,0.0f)
#define IMAGE_NUM_LEVEL_POS D3DXVECTOR3 (346.f,253.0f,0.0f)
#define DELAY_TIME_TO_START_PLAYING_STATE 2000
//#define IMAGE_BG_STARTING_STATE_PATH "Resource\\Other\\bgstartingstate.png"
//#define IMAGE_BG_STARTING_WIDTH 670
//#define IMAGE_BG_STARTING_HEIGHT 0
//#define SPEED_SCROLLING_BG 8
//#define IMAGE_BG_STARTING_TOP_POS D3DXVECTOR3(0.0f,0.0f,0.0f)
//#define IMAGE_BG_STARTING_BOTTOM_POS D3DXVECTOR3(0.0f,284.0f,0.0f)


//Default enemy position
#define DEFAULT_TOP_LEFT D3DXVECTOR2(0.0f,200.0f)
#define DEFAULT_TOP_MIDDLE D3DXVECTOR2(Win_WIDTH/2- SPRITE_WIDTH/2, 0.0f)
#define DEFAULT_TOP_RIGHT D3DXVECTOR2(Win_WIDTH - SPRITE_WIDTH,0.0f)

//Default Light Tank Value
#define  LIGHT_TANK_SPEED_X 4
#define	 LIGHT_TANK_SPEED_Y 4
#define  LIGHT_TANK_BULLET_SPEED_X 6
#define  LIGHT_TANK_BULLET_SPEED_Y 6
#define  LIGHT_TANK_RESOURCE_DOWN	/*/"Resource\\Enemy\\LightTank\\*/"down-light.png"
#define  LIGHT_TANK_RESOURCE_UP		/*"Resource\\Enemy\\LightTank\\*/"up-light.png"
#define	 LIGHT_TANK_RESOURCE_LEFT	/*"Resource\\Enemy\\LightTank\\*/"left-light.png"
#define  LIGHT_TANK_RESOURCE_RIGHT	/*"Resource\\Enemy\\LightTank\\*/"right-light.png"
//Default Medium Tank Value
#define  MEDIUM_TANK_SPEED_X 2
#define	 MEDIUM_TANK_SPEED_Y 2
#define  MEDIUM_TANK_BULLET_SPEED_X 4
#define  MEDIUM_TANK_BULLET_SPEED_Y 4
#define  MEDIUM_TANK_RESOURCE_DOWN "Resource\\Enemy\\MediumTank\\down-medium.png"
#define  MEDIUM_TANK_RESOURCE_UP "Resource\\Enemy\\MediumTank\\up-medium.png"
#define	 MEDIUM_TANK_RESOURCE_LEFT "Resource\\Enemy\\MediumTank\\left-medium.png"
#define  MEDIUM_TANK_RESOURCE_RIGHT "Resource\\Enemy\\MediumTank\\right-medium.png"
//Default Heavy Tank Value
#define  HEAVY_TANK_SPEED_X 2
#define	 HEAVY_TANK_SPEED_Y 2
#define  HEAVY_TANK_BULLET_SPEED_X 6
#define  HEAVY_TANK_BULLET_SPEED_Y 6
#define  HEAVY_TANK_RESOURCE_DOWN "Resource\\Enemy\\HeavyTank\\down-heavy.png"
#define  HEAVY_TANK_RESOURCE_UP "Resource\\Enemy\\HeavyTank\\up-heavy.png"
#define	 HEAVY_TANK_RESOURCE_LEFT "Resource\\Enemy\\HeavyTank\\left-heavy.png"
#define  HEAVY_TANK_RESOURCE_RIGHT "Resource\\Enemy\\HeavyTank\\right-heavy.png"
//Default Super Heavy Tank Value
#define  SUPER_HEAVY_TANK_SPEED_X 2
#define	 SUPER_HEAVY_TANK_SPEED_Y 2
#define  SUPER_HEAVY_TANK_BULLET_SPEED_X 4
#define  SUPER_HEAVY_TANK_BULLET_SPEED_Y 4
#define  SUPER_HEAVY_TANK_RESOURCE_DOWN "Resource\\Enemy\\SuperHeavyTank\\down-super.png"
#define  SUPER_HEAVY_TANK_RESOURCE_UP "Resource\\Enemy\\SuperHeavyTank\\up-super.png"
#define	 SUPER_HEAVY_TANK_RESOURCE_LEFT "Resource\\Enemy\\SuperHeavyTank\\left-super.png"
#define  SUPER_HEAVY_TANK_RESOURCE_RIGHT "Resource\\Enemy\\SuperHeavyTank\\right-super.png"
//Default Bonus Tank Value
#define BONUS_TANK_SPEED_X 2
#define BONUS_TANK_SPEED_Y 2
#define BONUS_TANK_BULLET_SPEED_X 4
#define BONUS_TANK_BULLET_SPEED_Y 4
#define BONUS_TANK_RESOURCE_UP    "Resource\\Enemy\\BonusTank\\up-bonus.png"
#define BONUS_TANK_RESOURCE_LEFT  "Resource\\Enemy\\BonusTank\\left-bonus.png"
#define BONUS_TANK_RESOURCE_DOWN  "Resource\\Enemy\\BonusTank\\down-bonus.png"
#define BONUS_TANK_RESOURCE_RIGHT "Resource\\Enemy\\BonusTank\\right-bonus.png"
//Ally Bullet
#define ALLY_PLAYER 1
#define ALLY_ENEMY 2

//Resource sound path
#define SOUND_START_GAME ""
#define SOUND_FIRE ""
#define SOUND_BULLET_EXPLODE ""
#define SOUND_TANK_EXPLODE ""
#define SOUND_EAGLE_DESTROY ""
#define SOUND_TANK_HIT ""

#define ID_SOUND_START_GAME 1
#define ID_SOUND_FIRE 2
#define ID_SOUND_BULLET_EXPLODE 3
#define ID_SOUND_TANK_EXPLODE 4
#define ID_SOUND_EAGLE_DESTROY 5
#define ID_SOUND_TANK_HIT 6

//20/11/2015
//------------game effect ID--------------------
//PATH
#define EFFECT_SHIELD "Resource\\Other\\shield.png"
#define EFFECT_RESPAWN ""
#define EFFECT_SMALL_EXPLODE ""
#define EFFECT_SPECIAL_EXPLODE ""
//ID
#define ID_EFFECT_SHIELD 1
#define ID_EFFECT_RESPAWN 2
#define ID_EFFECT_SMALL_EXPLODE 3
#define ID_EFFECT_SPECIAL_EXPLODE 4
//numb of sprite
#define NUMB_OF_SPRITE_SHIELD 2
#define NUMB_OF_SPRITE_RESPAWN 6
#define NUMB_OF_SPRITE_SMALL_EXPLODE 6
#define NUMB_OF_SPRITE_SPECIAL_EXPLODE 7


//OBJECT TYPE
#define ENEMY_OBJECT_TYPE 1

#endif // ! __GAME_DEFAULT_CONSTANT__
