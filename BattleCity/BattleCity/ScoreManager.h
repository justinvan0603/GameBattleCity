#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__
#include <fstream>
#include <string>
using namespace std;
class ScoreManager
{
public:
	static ScoreManager* getInstance();
	int getPlayerScore();
	int getHighScore();
	void addKillTankScore(int typeTank);
	void addPowerUpScore();
	int getScoreTank(int typeTank);
	int getNumTank(int typeTank);
	int getNumTank();
	void renewValue();
	void reset();
private:
	ScoreManager();
	~ScoreManager();
	static ScoreManager* _instance;
	int _playerScore;		//Diem cua nguoi choi
	int _highScore;			//Diem cao nhat
	int _scoreTank[4];		//Diem tung loai tank
	int _scorePowerUp;		//Diem powerUp
	int _numTank[4];		//So luong tank bi ban chet trong 1 man choi (stage)
};
#endif
 

