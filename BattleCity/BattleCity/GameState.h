#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "Keyboard.h"
#include "GameDefaultConstant.h"
#include "PlayerTank.h"
#include "Map.h"

#pragma region Game State

class GameState
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void enter() = 0;

	static void initialize(LPD3DXSPRITE spriteHandler);

	static void release();

	static void switchState(GameState* newState);

	static void stateUpdate();

	static void stateDraw();

protected:
	static GameState*	_gameState;
	static PlayerTank*	_player;
	static LPD3DXSPRITE _spriteHandler;
};
#pragma endregion

#pragma region Main Menu


class MainMenu : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static MainMenu* get();

private:
	MainMenu();
	~MainMenu();

private:
	static MainMenu* _instance;
	Sprite* _menuImage;
	Sprite* _selector;
	D3DXVECTOR3 _menuImagePosition;
	D3DXVECTOR3 _selectorPosition;
	int _timeDelayChangeSelectorSprite;
};
#pragma endregion

#pragma region Starting State

class StartingState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static StartingState* get();

	int getCurrentLevelState();

private:
	StartingState();
	~StartingState();

private:
	static StartingState* _instance;
	int _currentLevelState;
	int _timeToNextLevelState;
	LPDIRECT3DDEVICE9 _d3ddevice;
	Sprite* _stateLevelImage;
	Sprite* _numLevel;
	Sprite* _bgTop;
	D3DXVECTOR3 _bgTopPos;
	Sprite* _bgBottom;
	D3DXVECTOR3 _bgBottomPos;
};
#pragma endregion

#pragma region Playing State
class PlayingState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static PlayingState* get();

private:
	PlayingState();
	~PlayingState();

private:
	static PlayingState* _instance;
	Map* _map;
};
#pragma endregion

#pragma region Score State
class ScoreState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static ScoreState* get();

private:
	ScoreState();
	~ScoreState();

private:
	static ScoreState* _instance;

};
#pragma endregion

#pragma region Dead State

class DeadScene : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static DeadScene* get();

private:
	DeadScene();
	~DeadScene();

private:
	static DeadScene* _instance;

	DWORD _timeCounter;
};
#pragma endregion

#endif // GameState_h__
