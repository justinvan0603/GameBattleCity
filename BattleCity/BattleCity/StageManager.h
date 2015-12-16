#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__

class StageManager
{
public:
	static StageManager* getInstance();
	void nextStage();
	int getStage();
	void reset();
private:
	StageManager();
	~StageManager();
	static StageManager* _instance;
	int _maxStage;					//Stage toi da
	int _currentStage;				//Stage hien tai
};
#endif

