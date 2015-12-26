#ifndef __DEFAULTCONSTANT_H__
#define __DEFAULTCONSTANT_H__

#define WINDOWS_NAME "Battle City"
#define FPS 60

#define Win_WIDTH 664
#define Win_HEIGHT 600
#define FRAME_RATE 30
#define FOR_A(start,stop)	for(auto i = start; i != stop; ++i)
#define SAFE_RELEASE(A)		{if (A) {delete A; A = 0;}}
#define WARNING_BOX(A) MessageBox(0, A, ("Error"), MB_OK)
#define WARNING_MAP_FILE_NOT_FOUND	"File map not found!\n"
#define WARNING_GAME_CAN_NOT_INIT_WINDOW "Init windows fail!\n"
#define WARNING_GAME_CAN_NOT_INIT_D3D "Init Direct3D fail!\n"
#define WARNING_GAME_CAN_NOT_INIT_KEYBOARD "Init Keyboard fail!\n"
#define WARNING_CAN_NOT_READ_KEYBOARD	"Unable to read keyboard status.\n"
#define WARNING_CAN_NOT_INIT_SOUND "Init Sound fail!\n"

// Default audio setting.
#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL

#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#endif