#ifndef __GAMEPLAYSCENE_SCENE_H__
#define __GAMEPLAYSCENE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

#define LINE 32
#define COLUME 20

class GamePlayLayer : public cocos2d::CCLayerColor
{
public:
	GamePlayLayer();
	~GamePlayLayer();

	static cocos2d::CCScene* createScene();
	virtual bool init();

	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(GamePlayLayer);

	//�������
	void clearLine(int nLineStart, int nLineEnd);
	//���¿���һ��
	void copyLine(int nlineNum);
	//�����Ϸ�Ƿ����
	void checkFail();
	//��Ϸ��������
	void gameOver();
	//���·�����ʾ
	void updateScore();
	//����һ���µķ���
	void newSquareType();
	//�����һ����������
	void nextSquareType();
	//�����½�
	void updateDown(float dt);
	//��������
	void updateLeft();
	//��������
	void updateRight();

	CCSprite* m_pSquare[LINE][COLUME];	//���鵥Ԫ��
	int m_nCurline;						//����������ǰ��
	int m_nCurcolume;					//����������ǰ��
	int m_nCurSquareType;				//��ǰ��������
	int m_nCurScore;					//��ǰ��Ϸ����
	CCLabelTTF* m_pLabel;

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
};

#endif