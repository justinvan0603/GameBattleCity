#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "Map.h"
#include "Text.h"
#include "ScoreManager.h"
#include "StageManager.h"
#include "GameSound.h"

#pragma region Game State
class GameState		//Base Object
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
	static Text* _text;		//Doi tuong ve chu len man hinh
	int _delayTime;			//Khoang thoi gian delay giua cac State
};
#pragma endregion


#pragma region Main Menu
class MainMenu : public GameState	//Menu game
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
	Sprite* _menuImage;				//anh battle city
	Sprite* _selector;				//con tro chon chay chay
	float _posYMenu;				//su dung de lam HU menu chay tu duoi len
	D3DXVECTOR3 _selectorPosition;	//Danh dau vi tri con tro de vao game hoac instruction
};
#pragma endregion

#pragma region Instruction
class Instruction : public GameState	//Huong dan choi
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

	int _currentTab;			//Tab duoc chon
	Sprite* _imageTabStory;
	Sprite* _imageTabControl;
	Sprite* _imageBulletRight;
	Sprite* _imageTabEmies;
	Sprite* _imageTabPowerUp;
	Sprite* _imageTabEnvironment;
};
#pragma endregion

#pragma region Starting State
class StartingState : public GameState		//Man hinh bao Stage, chuan bi vao game
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
	LPDIRECT3DDEVICE9 _d3ddevice;	//Dung de clear nen mau xam
};
#pragma endregion

#pragma region Playing State
class PlayingState : public GameState		//Man hinh chinh choi game
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
	Map* _map;		//Ban do game, bao gom cac doi tuong player, static/Dynamic object ..
};
#pragma endregion

#pragma region Score State
class ScoreState : public GameState		//tinh diem sau moi man choi
{
public:
	virtual void update();

	virtual void draw();

	virtual void reset();

	static ScoreState* get();

	void setEndAfter(bool isEnd);

	void writeFile();

private:
	bool _isEnd;				//kiem tra ng choi co bi thua truoc khi vao state nay khong
	int _numTypeEnemy;			//so luong loai enemy tinh diem
	Sprite* _iconTankScore;
	ScoreState();
	~ScoreState();

private:
	static ScoreState* _instance;

};
#pragma endregion

#pragma region GameOverState
class GameOverState : public GameState		//Ket thuc game (Bi GameOver)
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

class EndGame : public GameState	//ket thuc game khi pha dao
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
	bool _isFlash;				//Chu nhap nhay ESC
	int _score;					//Diem cua nguoi choi
	D3DCOLOR _congraColor;
	D3DCOLOR _arrayColor[5];	//Mau cua chu nhap nhay
	int _colorIndex;
};
#pragma endregion

#endif // GameState_h__