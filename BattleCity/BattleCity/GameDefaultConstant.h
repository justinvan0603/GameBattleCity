#ifndef  __GAME_DEFAULT_CONSTANT__
#define  __GAME_DEFAULT_CONSTANT__
#include <sstream>
#include <iostream>
#include "DefaultConstant.h"
//player default value
#define DEFAULT_PLAYER_LIFE 3
#define DEFAULT_PLAYER_POSITION_X	243
#define DEFAULT_PLAYER_POSITION_Y	434
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
#define PLAYER_DEFAULT_BULLET_RELOAD_TIME 1800
#define PLAYER_PROMOTED_BULLET_RELOAD_TIME 100
#define PLAYER_NUMB_OF_SPRITE 8
#define PLAYER_SPRITE_PER_ROW 4
//Sprite
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32

#define NUMB_OF_SPRITE 1
#define SPRITE_PER_ROW 1
//Static Object default size
#define DEFAULT_STATIC_WIDTH 8
#define DEFAULT_STATIC_HEIGHT 8

//Dynamic Object ID
#define ID_PLAYER 4
#define ID_MEDIUM_TANK 0
#define ID_LIGHT_TANK 1
#define ID_HEAVY_TANK 2
#define ID_SUPER_HEAVY_TANK 3
#define ID_BONUS_TANK 5

//// DYNAMIC OBJECT SPEED------------------------25/11/2015
#define DYNAMIC_OBJECT_LOW_SPEED D3DXVECTOR2(2.0f,2.0f)
#define DYNAMIC_OBJECT_HIGH_SPEED D3DXVECTOR2(4.0f,4.0f)
//// DYNAMIC OBJECT LEVEL
#define LEVEL_ONE 1
#define LEVEL_TWO 2
#define LEVEL_THREE 3
#define LEVEL_FOUR 4

//Static Object
#define ID_BRICKWALL 7
#define ID_BRICKWALL_0	0
#define ID_BRICKWALL_1	1
#define ID_BRICKWALL_10	10
#define ID_BRICKWALL_11	11
#define ID_STEELWALL 8
#define ID_STEELWALL_2	2
#define ID_STEELWALL_3	3
#define ID_STEELWALL_12	12
#define ID_STEELWALL_13 13
#define ID_WATER	 9
#define ID_WATER_4	4
#define ID_WATER_5	5
#define ID_WATER_14	14
#define ID_WATER_15	15
#define ID_TREES	 10
#define ID_TREES_6	6
#define ID_TREES_7	7
#define ID_TREES_16	16
#define ID_TREES_17	17
#define ID_ICE		 11
#define ID_ICE_8	8
#define ID_ICE_9	9
#define ID_ICE_18	18
#define ID_ICE_19	19
#define ID_EAGLE  21
//Bullet
#define ID_BULLET 20
#define DEFAULT_BULLET_SPEED_X 6
#define DEFAULT_BULLET_SPEED_Y 6
#define BULLET_PROMOTED_SPEED_X 8
#define BULLET_PROMOTED_SPEED_Y 8
#define BULLET_SPRITE_UP_PATH		"Resource\\Other\\bullet\\bullet-up.png"
#define BULLET_SPRITE_DOWN_PATH		"Resource\\Other\\bullet\\bullet-down.png"
#define BULLET_SPRITE_LEFT_PATH		"Resource\\Other\\bullet\\bullet-left.png"
#define BULLET_SPRITE_RIGHT_PATH	"Resource\\Other\\bullet\\bullet-right.png"
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
#define COLOR_BLACK D3DCOLOR_XRGB(0,0,0)
#define COLOR_WHITE D3DCOLOR_XRGB(255,255,255)
#define COLOR_YELLOW D3DCOLOR_XRGB(255,255,0)
#define COLOR_GREEN D3DCOLOR_XRGB(0,255,0)
#define COLOR_BLUE D3DCOLOR_XRGB(0,0,255)
#define COLOR_RED D3DCOLOR_XRGB(255,0,0)
#define COLOR_GREY D3DCOLOR_XRGB(99,99,99)
#define COLOR_HIGHSCORE_TEXT D3DCOLOR_XRGB(184,9,9)
#define COLOR_SCORE_TEXT D3DCOLOR_XRGB(197,161,9)
	//Mainmenu
#define IMAGE_MAIN_MENU_GAME_PATH "Resource\\Other\\mainmenu.png"
#define IMAGE_MAIN_MENU_GAME_WIDTH 525
#define IMAGE_MAIN_MENU_GAME_HEIGHT 158
#define MAIN_MENU_GAME_DEFAULT_POS_Y 600.0f
#define IMAGE_MAIN_MENU_GAME_DEFAULT_SPEED_UP 3
#define IMAGE_SELECTOR_PATH		"Resource\\Other\\selector.png"
#define IMAGE_SELECTOR_WIDTH 32
#define IMAGE_SELECTOR_HEIGHT 32
#define SELECTOR_SPEED_CHANGE 200
#define IMAGE_SELECTOR_POS_PLAY D3DXVECTOR3(200.0f,300.0f,0.0f)
#define IMAGE_SELECTOR_POS_INSTRUCTION D3DXVECTOR3(200.0f,335.0f,0.0f)
#define TEXT_PlAYER_SCORE "I-"
#define TEXT_HI_SCORE "HI-"
#define TEXT_PLAY "PLAY"
#define TEXT_INSTRUCTION "INSTRUCTION"
#define TEXT_SE_UIT "SE-UIT"
#define TEXT_ABOUT "PROJECT INTRODUCTION TO \nGAME DEVELOPMENT"
	//Instruction
#define IMAGE_TAB_STORY_PATH "Resource\\Other\\Instruction\\story.png"
#define IMAGE_TAB_CONTROL_PATH "Resource\\Other\\Instruction\\tabcontrol.png"
#define IMAGE_TAB_ENEMIES_PATH "Resource\\Other\\Instruction\\tabenemy.png"
#define IMAGE_TAB_POWERUP_PATH "Resource\\Other\\Instruction\\tabpowerup.png"
#define IMAGE_TAB_ENVIRONMENT_PATH "Resource\\Other\\Instruction\\tabenvironment.png"
#define TEXT_TUT "Move: LEFT | RIGHT    Back: ESC"
#define TEXT_TAB_STORY "Story"
#define TEXT_INFO_STORY "You are the last member of your army's elite tank commanders,\nwith no choice but to defend your fortress against an entire \narmy of enemy tanks bent on your base's destruction.\nBreak holes through the walls and situate yourself\nstrategically to remove the enemy as quickly as possible, but\nstay out of their line of fire, and don't let them shoot your\nbase down."
#define TEXT_TAB_CONTROL "Control"
#define TEXT_TAB_CONTROL_ACTION "Action"
#define TEXT_TAB_CONTROL_KEY "Key"
#define TEXT_TAB_CONTROL_UP "Up"
#define TEXT_TAB_CONTROL_RIGHT "Right"
#define TEXT_TAB_CONTROL_DOWN "Down"
#define TEXT_TAB_CONTROL_LEFT "Left"
#define TEXT_TAB_CONTROL_SPACE "Space"
#define TEXT_TAB_ENEMIES "Enemies"
#define TEXT_TAB_ENEMIES_TYPETANK "Type"
#define TEXT_TAB_ENEMIES_TANKINFO "Infomation"
#define TEXT_TAB_ENEMIES_INFO_BASIC "Basic tank: Move slow"
#define TEXT_TAB_ENEMIES_INFO_FAST "Fast tank: Move fast"
#define TEXT_TAB_ENEMIES_INFO_POWER "Power tank: Shoot fast"
#define TEXT_TAB_ENEMIES_INFO_SHEILD "Armor tank: Need 3 hits to kill"
#define TEXT_TAB_POWER_UP "PowerUps"
#define TEXT_TAB_POWER_UP_GRENADE "Grenade: Destroys every enemy currently on the \nscreen"
#define TEXT_TAB_POWER_UP_HELMET "Helmet: Gives a temporary force field that \nshields from enemy shots"
#define TEXT_TAB_POWER_UP_TIMER "Timer: The timer power-up temporarily freezes \ntime, stopping all enemy tanks' movement"
#define TEXT_TAB_POWER_UP_TANK "Tank: Gives an extra life"
#define TEXT_TAB_POWER_UP_STAR "Star: Increases your offensive power by one \ntier (default, second, third, and fourth). \nPower level only resets to default when you die"
#define TEXT_TAB_ENVIRONMENT "Environment"
#define TEXT_TAB_ENVIRONMENT_BRICK "Brick: Tanks and bullets cannot pass through \nthis. Can be destroyed by being shot"
#define TEXT_TAB_ENVIRONMENT_STEEL "Steel: Stops tanks and bullets completely. Can \nonly be destroyed if hit by bullets level 4"
#define TEXT_TAB_ENVIRONMENT_TREES "Trees: Obfuscates tanks and bullets under it \nwhen moving through"
#define TEXT_TAB_ENVIRONMENT_WATER "Water: Tanks cannot traverse through at all \nbut bullets can fly across"
#define TEXT_TAB_ENVIRONMENT_ICE "Ice: Tanks can move on it. Obfuscates flying \nbullets"
#define POS_TEXT_INFO_STORY D3DXVECTOR3(25.0f, 110.0f, 0.0f)
#define POS_TEXT_STORY D3DXVECTOR3(25.0f, 50.0f, 0.0f)	
#define POS_IMAGE_STORY D3DXVECTOR3(200.0f, 210.0f, 0.0f)
#define POS_TEXT_CONTROL D3DXVECTOR3(115.0f, 50.0f, 0.0f)
#define POS_TEXT_ENEMIES D3DXVECTOR3(230.0f, 50.0f, 0.0f)
#define POS_TEXT_POWER_UP D3DXVECTOR3(350.0f, 50.0f, 0.0f)
#define POS_TEXT_ENVIRONMENT D3DXVECTOR3(475.0f, 50.0f, 0.0f)
#define POS_TUTORIAL D3DXVECTOR3(300.0f, 535.0f, 0.0f)
	//Starting
#define IMAGE_STATE_POS D3DXVECTOR3(250.0f,252.0f,0.0f)
#define DELAY_TIME_TO_START_PLAYING_STATE 2000
//#define IMAGE_BG_STARTING_STATE_PATH "Resource\\Other\\bgstartingstate.png"
//#define IMAGE_BG_STARTING_WIDTH 670
//#define IMAGE_BG_STARTING_HEIGHT 0
//#define SPEED_SCROLLING_BG 8
//#define IMAGE_BG_STARTING_TOP_POS D3DXVECTOR3(0.0f,0.0f,0.0f)
//#define IMAGE_BG_STARTING_BOTTOM_POS D3DXVECTOR3(0.0f,284.0f,0.0f)


	//Playing State
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
#define NUM_TILE_PER_SPRITE 4
#define MAP_PATH "Resource\\Map\\Level\\lv"
#define MAP_FILE_EXTENSION ".txt"
#define MAP_RESOURCE_PATH_ENVIRONMENT "Resource\\Map\\Environment.png"
#define MAP_RESOURCE_PATH_EAGLE	"Resource\\Map\\Eagle.png"
#define MAP_RESOURCE_PATH_BG	"Resource\\Map\\bg.png"
#define MAP_NUM_OF_TYPE_OBJ 20
#define MAX_ENEMY 20
#define MAX_ENEMY_ONE_TIME 4
#define NUM_TYPE_ENEMY 4
#define DELAY_TIME_END_PLAYING_STATE 5000
#define DELAY_TIME_DRAW_SCORE_POWER 2000
#define DELAY_TIME_RESPAWN_1000 1000
#define DELAY_TIME_RESPAWN_4000 4000
#define DELAY_FREEZE_TIME 20000
#define POS_RESPAWN_X 100.0f
#define POS_RESPAWN_Y 51.0f
#define POS_START_GAMEOVER D3DXVECTOR3(180.0f, 500.0f, 0.0f)
#define POS_END_GAMEOVER_Y 200.0f
#define DISTANCE_RESPAWN_POS_X 192.0f
#define MAX_RESPAWN_POS_X 384.0f
#define NUM_RESPAWN_POS 3
#define DEFINE_ZERO_VALUE 0
#define RESPAWN_SPRITE_PATH "Resource\\Other\\respawn.png"

//Info Right map default value
#define POS_LIST_ENEMY_ICON_TOP_LEFT_X 540
#define POS_LIST_ENEMY_ICON_TOP_LEFT_Y 92
#define RESOURCE_PATH_ENEMY_ICON	"Resource\\Other\\miniarmy.png"
#define RESOURCE_PATH_TANKLIFE_ICON	"Resource\\Other\\tanklife.png"
#define POS_LIFE_IMAGE D3DXVECTOR3(540.0f,316.0f,0.0f)
#define POS_NUM_LIFE D3DXVECTOR3(558.0f,332.0f,0.0f)
#define RESOURCE_PATH_FLAG_LEVEL_ICON	"Resource\\Other\\flag.png"
#define POS_FLAG_LIFE_IMAGE  D3DXVECTOR3(540.0f,412.0f,0.0f)
#define POS_NUM_LEVEL D3DXVECTOR3(556.0f,444.0f,0.0f)

//ID power up 
#define MAP_RESOURCE_PATH_POWERUP "Resource\\Other\\powerup.png"
#define ID_POWER_BOMB 0
#define ID_POWER_SHEILD 1 
#define ID_POWER_FREEZE_TIME 2 
#define ID_POWER_EXTRA_LIFE 3
#define ID_POWER_STAR 4

//Default enemy position
#define DEFAULT_TOP_LEFT D3DXVECTOR2(0.0f,200.0f)
#define DEFAULT_TOP_MIDDLE D3DXVECTOR2(Win_WIDTH/2- SPRITE_WIDTH/2, 0.0f)
#define DEFAULT_TOP_RIGHT D3DXVECTOR2(Win_WIDTH - SPRITE_WIDTH,0.0f)
#define DEFAULT_POS_ZERO D3DXVECTOR3(0.0f, 0.0f, 0.0f)

//Enemy Default
#define ENEMY_NORMAL_NUMB_OF_SPRITE 4
#define ENEMY_NORMAL_SPRITE_PER_ROW 2
#define SUPER_HEAVY_NUMB_OF_SPRITE 8
#define SUPER_HEAVY_SPRITE_PER_ROW 4
//Default Light Tank Value
#define  LIGHT_TANK_SPEED_X 4
#define	 LIGHT_TANK_SPEED_Y 4
#define  LIGHT_TANK_BULLET_SPEED_X 6
#define  LIGHT_TANK_BULLET_SPEED_Y 6
#define  LIGHT_TANK_RESOURCE_DOWN	"Resource\\Enemy\\LightTank\\down-light.png"
#define  LIGHT_TANK_RESOURCE_UP		"Resource\\Enemy\\LightTank\\up-light.png"
#define	 LIGHT_TANK_RESOURCE_LEFT	"Resource\\Enemy\\LightTank\\left-light.png"
#define  LIGHT_TANK_RESOURCE_RIGHT	"Resource\\Enemy\\LightTank\\right-light.png"
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

//Define Score State
#define TEXT_SIZE_SCORE_STATE 20
#define POS_HIGHSCORE D3DXVECTOR3(200.0f,200.0f,0.0f)
#define ICON_TANK_SCORE_PATH "Resource\\Other\\IconTankScore.png"
#define POS_HI_SCORE D3DXVECTOR3(170.0f, 50.0f, 0.0f)
#define POS_HI_SCORE_VALUE D3DXVECTOR3(370.0f, 50.0f, 0.0f)
#define POS_STAGE_TEXT D3DXVECTOR3(240.0f, 90.0f, 0.0f)
#define POS_STAGE_VALUE D3DXVECTOR3(370.0f, 90.0f, 0.0f)
#define POS_PLAYER_TEXT D3DXVECTOR3(250.0f, 130.0f, 0.0f)
#define POS_PLAYER_VALUE D3DXVECTOR3(250.0f, 160.0f, 0.0f)
#define POS_ICON_TANK_SCRORE_STATE D3DXVECTOR3(410.0f, 230.0f, 0.0f)
#define POS_LINE D3DXVECTOR3(360.0f, 400.0f, 0.0f)
#define POS_TOTAL_TEXT D3DXVECTOR3(245.0f, 430.0f, 0.0f)
#define POS_TOTAL_VALUE D3DXVECTOR3(370.0f, 430.0f, 0.0f)
#define DISTANCE_LINE 47.0f
#define BEGIN_X 240.0f
#define SCORE_POS_X 170.0f
#define PTS_POS_X 280.0f
#define NUM_TANK_POS_X 370.0f
#define SCORE_MEDIUM_TANK 100
#define SCORE_LIGHT_TANK 200
#define SCORE_HEAVY_TANK 300
#define SCORE_SUPER_HEAVY_TANK 400 
#define SCORE_POWER_UP 500

//Define End State
#define ICON_END_GAME_PATH "Resource\\Other\\gameover.png"
#define POS_ICON_END D3DXVECTOR3(170.0f, 170.0f,0.0f)

//Resource sound path
#define SOUND_START_GAME "Resource\\Sound\\levelstarting.wav"
#define SOUND_FIRE "Resource\\Sound\\shoot.wav"
#define SOUND_BRICK_EXPLODE "Resource\\Sound\\brickhit.wav"
#define SOUND_STEEL_WALL_EXPLODE "Resource\\Sound\\steelandwallhit.wav"
#define SOUND_TANK_EXPLODE "Resource\\Sound\\enemyExplosion.wav"
#define SOUND_TANK_HIT "Resource\\Sound\\shieldhit.wav"
#define SOUND_TANK_ENGINE "Resource\\Sound\\nonmove.wav"
#define SOUND_TANK_MOVE "Resource\\Sound\\move.wav"
#define SOUND_ALLY_EXPLODE "Resource\\Sound\\eagleExplosion.wav"
#define SOUND_ITEM_APPEAR "Resource\\Sound\\hitenemybonus.wav"
#define SOUND_ITEM_EAT "Resource\\Sound\\eatbonus.wav"
#define SOUND_LIFE_UP "Resource\\Sound\\eatlifebonus.wav"

#define ID_SOUND_START_GAME 1
#define ID_SOUND_FIRE 2
#define ID_SOUND_BRICK_EXPLODE 3
#define ID_SOUND_TANK_EXPLODE 4
#define ID_SOUND_TANK_ENGINE 5
#define ID_SOUND_TANK_HIT 6
#define ID_SOUND_TANK_MOVE 7
#define ID_SOUND_ALLY_EXPLODE 8
#define ID_SOUND_ITEM_APPEAR 9
#define ID_SOUND_ITEM_EAT 10
#define ID_SOUND_LIFE_UP 11
#define ID_SOUND_STEEL_WALL_EXPLODE 12
//20/11/2015
//------------game effect ID--------------------
//PATH
#define EFFECT_SHIELD "Resource\\Other\\shield.png"
#define EFFECT_SMALL_EXPLODE "Resource\\Other\\explode-mini.png"
#define EFFECT_SPECIAL_EXPLODE "Resource\\Other\\explode-big.png"
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


//define font
#define DEFAULT_FONT_COLOR 0xFFBCBCBC
#define DEFAULT_FONTSIZE 14
#define DEFAULT_FONTFACE "Press Start"
#define DEFAULT_FONTPATH "Resource\\Other\\prstart.ttf"
//define stage
#define DEFAULT_START_STAGE 1
#define DEFAULT_MAX_STAGE 3


//OBJECT TYPE
#define ENEMY_OBJECT_TYPE 1

//Score manager
#define HI_SCORE_FILE_PATH "Resource\\Other\\highscore.txt"

#endif // ! __GAME_DEFAULT_CONSTANT__

