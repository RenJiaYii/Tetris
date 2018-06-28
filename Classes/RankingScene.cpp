#include "RankingScene.h"

using namespace cocos2d;

Scene* RankingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = RankingLayer::create();
	scene->addChild(layer);
	return scene;
}
bool RankingLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}