#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#define KEYDOWN(name, key) (name[key] & 0x80)
#define APP_CLASS "BattleCity"
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define FRAME_RATE			20
#define UNIT_SIZE			32
#define NROWS				18
#define NCOLS				18

#define TOP_OUTSIDESCREEN   5
#define LEFT_OUTSIDESCREEN  5
#define PLAY_FIELD_WIDTH	576
#define PLAY_FIELD_HEIGHT	576

#define ONE_CLICK_STEP		70
//--------------------------------------
//Objects' IDs
//--------------------------------------
#define ID_NONE						0
#define ID_PLAYER_TANK				1
#define ID_SIMPLE_TANK				2
#define ID_SMART_TANK				3
#define ID_BULLET					4
#define ID_DURABLE_WALL				5
#define ID_WALL						6
#define ID_FOREST					7
#define ID_SEA						8
#define ID_SAND						9
#define ID_SWAMP					10
#define ID_HOME						11
#define ID_HOME_DESTROYED_ITEM		12

#define ID_INVULERABLE_ITEM 		13
#define ID_LIFE_ITEM				14
#define ID_CLOCK_ITEM				15
#define ID_SHOVEL_ITEM				16
#define ID_BOMB_ITEM				17
#define ID_STAR_ITEM				18
#define ID_SHIELD_ITEM				19

#define ID_PLAYER_TANK_SHIELD		20

#define ITEM_LIFE_TIME			5
#define NRANDITEM				7

//--------------------------------------
//Images 'paths
//--------------------------------------

//--------------------------------------
//Objects' directions
//--------------------------------------
#define MOTIONLESS		-10
#define MOVINGTOP		10
#define MOVINGDOWN		11
#define MOVINGLEFT		12
#define MOVINGRIGHT		13

//--------------------------------------
//The settings of all sprite in the image
//--------------------------------------

#define SPRITE_WIDTH	33
#define SPRITE_HEIGHT	33
#define SPRITE_COUNT	264//12*22
#define SPRITE_PER_ROW	22

#define SPRITE_PATH		"images\\modernSprites.PNG"

//#define SPRITE_PATH1	"images\\BCSprites.PNG"
//--------------------------------------
//Error messages
//--------------------------------------
#define ERR_INIT				"Initialization of Direct3D Failed!!\n(You Probably don't have DirectX 9.0c or higher installed,\nyou can find DirectX 9.0c at www.microsoft.com )"
#define IDERR_INIT				"ERROR 0"
#define ERR_CREATE_D3DDV		"Fail to create device!"
#define IDERR_CREATE_D3DDV		"ERROR 1"
#define ERR_CREATE_KEYBOARD		"Fail to initalize keyboard!"
#define IDERR_CREATE_KEYBOARD	"ERROR 2"
#define ERR_CREATE_SURFACE		"Fail to create off screen plain surface"
#define IDERR_CREATE_SURFACE	"ERROR 3"
#define ERR_CREATE_SPRITE		"Fail to create Sprite"
#define IDERR_CREATE_SPRITE		"ERROR 4"
#define ERR_LOAD_FILE			"Fail to load image"
#define IDERR_LOAD_FILE			"ERROR 5"
#define ERR_CREATE_MOUSE		"Fail to initalize mouse!"
#define IDERR_CREATE_MOUSE		"ERROR 6"
#define ERR_CREATE_WINDOW		"Initialization of Window Failed!"
#define IDERR_CREATE_WINDOW		"ERROR 7" 
#define ERR_BEGIN_SCENE			"Beginning Scene Failed!"
#define IDERR_BEGIN_SCENE		"ERROR 8" 
#define ERR_LOAD_PLAYFIELD		"Cannot Load PlayField!"
#define IDERR_LOAD_PLAYFIELD	"ERROR 9" 
#define ERR_CREATE_FONT			"Call to D3DXCreateFont failed!"
#define IDERR_CREATE_FONT		"ERROR 10" 

#endif
