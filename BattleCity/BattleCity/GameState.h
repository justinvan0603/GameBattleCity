#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "Map.h"
#include "Text.h"

#pragma region Game State

class GameState
{
public:
	
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void reset() = 0;
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
	int _delayTime;
};
#pragma endregion

#pragma region Main Menu


class MainMenu : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void reset();

	static MainMenu* get();

private:
	MainMenu();
	~MainMenu();

private:
	static MainMenu* _instance;
	Sprite* _menuImage;
	Sprite* _selector;
	float _posYMenu;
	D3DXVECTOR3 _selectorPosition;
};
#pragma endregion

#pragma region Instruction


class Instruction : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void reset();

	static Instruction* get();

private:
	Instruction();
	~Instruction();

private:
	static Instruction* _instance;
	
	int _currentTab;
	Sprite* _imageTabStory;
	Sprite* _imageTabControl;
	Sprite* _imageBulletRight;
	Sprite* _imageTabEmies;
	Sprite* _imageTabPowerUp;
	Sprite* _imageTabEnvironment;
};
#pragma endregion

#pragma region Starting State

class StartingState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void reset();

	static StartingState* get();

private:
	StartingState();
	~StartingState();

private:
	static StartingState* _instance;
	LPDIRECT3DDEVICE9 _d3ddevice;
};
#pragma endregion

#pragma region Playing State
class PlayingState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void reset();

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

	virtual void reset();

	static ScoreState* get();

	void setEndAfter(bool isEnd);

	void writeFile();

private:
	bool _isEnd;
	int _numTypeEnemy;
	Sprite* _iconTankScore;
	ScoreState();
	~ScoreState();

private:
	static ScoreState* _instance;

};
#pragma endregion

#pragma region GameOverState

class GameOverState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void reset();

	static GameOverState* get();

private:
	GameOverState();
	~GameOverState();

private:
	static GameOverState* _instance;
	Sprite* _gameOverImage;
};
#pragma endregion

#pragma region EndGameState

class EndGame : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void reset();

	static EndGame* get();

private:
	EndGame();
	~EndGame();

private:
	static EndGame* _instance;
	bool _isFlash;
	int _score;
	D3DCOLOR _congraColor;
	D3DCOLOR _arrayColor[5];
	int _colorIndex;
};
#pragma endregion

#endif // GameState_h__
