#ifndef __RANKINGSCENE_SCENE_H__
#define __RANKINGSCENE_SCENE_H__

#include"cocos2d.h"

class RankingLayer :public cocos2d::Layer
{
public:
	static cocos2d::Scene*createScene();
	bool init();
	CREATE_FUNC(RankingLayer);
};
#endif
