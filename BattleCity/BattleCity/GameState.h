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

	static void initialize(Keyboard* controler);

	static void release();

	static void switchState(GameState* newState);

	static void stateUpdate();

	static void stateDraw();

protected:
	static Keyboard* _controler;
	static GameState*	_gameState;
	static PlayerTank*	_player;
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

	int getCurrentState();

private:
	StartingState();
	~StartingState();

private:
	static StartingState* _instance;
	int _numOfState;
	int _currentState;
	DWORD _timeCounter;
	DWORD _timeCounterToNextState;
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
