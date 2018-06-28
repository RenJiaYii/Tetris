#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "GameplayScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	auto* background = Sprite::create("background.jpg");
	background->setPosition(size.width / 2, size.height / 2);
	addChild(background, 0);

	auto hometitle = Sprite::create("title.png");
	hometitle->setPosition(size.width / 2, 560);
	hometitle->setScale(0.6f);
	addChild(hometitle, 1);

	auto producer = Label::createWithTTF("RenJiayi YouHao ChenKunyu", "fonts/arial.ttf", 36);
	producer->setPosition(size.width / 2, 440);
	producer->setScale(0.8f);
	addChild(producer, 1);

	auto startMenuItem = MenuItemImage::create("button1.png", "button1.png", CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	startMenuItem->setPosition(size.width / 2,300);
	startMenuItem->setTag(ActionType::MenuItemStart);
	startMenuItem->setScale(1.6f);

    auto settingMenuItem = MenuItemImage::create("button2.png", "button2.png", CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	settingMenuItem->setPosition(size.width / 2,150);
	settingMenuItem->setTag(ActionType::MenuItemSetting);
	settingMenuItem->setScale(1.6f);


	auto mu = Menu::create(startMenuItem,settingMenuItem, NULL);
	mu->setPosition(Point::ZERO);
	addChild(mu, 1);

	return true;
}


void HelloWorld::menuItemCallback(Ref* pSender)
{
	Scene* tsc = nullptr;
	MenuItem*menuItem = (MenuItem*)pSender;
	log("MenuItem Tag=%d", menuItem->getTag());
	switch (menuItem->getTag())
	{
	case ActionType::MenuItemStart:
		//auto scene = GamePlayLayer::createScene();
		tsc = TransitionFade::create(1.0f, GamePlayLayer::createScene());
		log("StartCallback");
		break;
	case ActionType::MenuItemSetting:
		tsc = TransitionFade::create(1.0f, SettingLayer::createScene());
		log("SettingCallback");
		break;

	}
	if (tsc)
		Director::getInstance()->pushScene(tsc);
	//auto scene = SettingLayer::createScene();
	// 让导演 用HelloWorld场景 ☆替换☆ 现在的场景，注意是替换！  
	//Director::getInstance()->replaceScene(scene);
}
