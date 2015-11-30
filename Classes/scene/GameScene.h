
#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"



class GameScene :public cocos2d::Layer{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void action(float);
	void update(float);
	void repeateAction(float);
	void judgeGame(float);

	void jumpBall(void);
	CREATE_FUNC(GameScene);



	int map[20] ;
	int preHeight = 0;
	int nowHeight = 0;

	int count;
	int ballHight;
};

#endif