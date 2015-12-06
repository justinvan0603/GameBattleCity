#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__
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
private:
	ScoreManager();
	~ScoreManager();
	static ScoreManager* _instance;
	int _playerScore;
	int _highScore;
	int _scoreTank[4];
	int _scorePowerUp;
	int _numTank[4];
};
#endif
 

