#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "Keyboard.h"
#include "Map.h"
#include "Text.h"
#include "StageManager.h"

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

	virtual ~GameState()
	{
	}

protected:
	static GameState*	_gameState;
	static LPD3DXSPRITE _spriteHandler;
	static Text* _text;
	static DWORD _startTime;

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

private:
	StartingState();
	~StartingState();

private:
	static StartingState* _instance;
	LPDIRECT3DDEVICE9 _d3ddevice;
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
	void setEndAfter(bool isEnd);

	void addResultState(int numtank[4]);

private:
	bool _isEnd;
	int _numTank[4];
	int _totalScore;
	Sprite* _iconTankScore;
	ScoreState();
	~ScoreState();

private:
	static ScoreState* _instance;

};
#pragma endregion

#pragma region Dead State

class EndState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static EndState* get();

private:
	EndState();
	~EndState();

private:
	static EndState* _instance;
	Sprite* _endImage;
	DWORD _timeCounter;
};
#pragma endregion

#endif // GameState_h__
