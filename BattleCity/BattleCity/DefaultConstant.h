#ifndef __DEFAULTCONSTANT_H__
#define __DEFAULTCONSTANT_H__

#define FPS 60

#define Win_WIDTH 664
#define Win_HEIGHT 600
#define FRAME_RATE 30
#define SAFE_RELEASE(A)		{if (A) {delete A; A = 0;}}
#define WARNING_BOX(A) MessageBox(0, A, ("Error"), MB_OK)
#define WARNING_MAP_FILE_NOT_FOUND	"Không tìm th?y file map!\n"
#define WARNING_GAME_CAN_NOT_INIT_WINDOW "Kh?i t?o c?a s? th?t b?i!\n"
#define WARNING_GAME_CAN_NOT_INIT_D3D "Kh?i t?o Direct3D th?t b?i!\n"
#define WARNING_GAME_CAN_NOT_INIT_KEYBOARD "Kh?i t?o Keyboard th?t b?i!\n"

#endif