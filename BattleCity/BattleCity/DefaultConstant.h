#ifndef __DEFAULTCONSTANT_H__
#define __DEFAULTCONSTANT_H__

#define WINDOWS_NAME "Battle City"
#define FPS 60

#define Win_WIDTH 664
#define Win_HEIGHT 600
#define FRAME_RATE 30
#define SAFE_RELEASE(A)		{if (A) {delete A; A = 0;}}
#define WARNING_BOX(A) MessageBox(0, A, ("Error"), MB_OK)
#define WARNING_MAP_FILE_NOT_FOUND	"File map not found!\n"
#define WARNING_GAME_CAN_NOT_INIT_WINDOW "Init windows fail!\n"
#define WARNING_GAME_CAN_NOT_INIT_D3D "Init Direct3D fail!\n"
#define WARNING_GAME_CAN_NOT_INIT_KEYBOARD "Init Keyboard fail!\n"
#define CAN_NOT_INIT_TEXT "Init Text fail!\n"

#endif