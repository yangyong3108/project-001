#include "CardScene.h"
#include <algorithm>
#include "Player.h"
#include "vld.h"
#include "Player.h"
#include "UserData.h"
#include "ConstUtil.h"
#include "TcpClient.h"

USING_NS_CC;

CardScene::CardScene(void)
{
	for (int i = 0; i < 52; i++)
	{
		m_vctCard.push_back(i);
	}
	
}

CardScene::~CardScene(void)
{
}

Scene* CardScene::createScene()
{
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CardScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool CardScene::init()
{
	if (!Layer::init())
		return false;
	
	UserData::instance()->m_nUserId = 10001;

	Size size = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	Player* play = Player::create();
	play->m_nId = 10001;
	Player* play1 = Player::create();
	Player* play2 = Player::create();
	Player* play3 = Player::create();

	play->setPosition(size.width / 2, 100);
	play->setGamePosition(GP_BOTTOM);
	play1->setPosition(size.width - 50, size.height / 2);
	play1->setGamePosition(GP_RIGHT);
	play2->setPosition(size.width / 2, size.height - 50);
	play2->setGamePosition(GP_TOP);
	play3->setPosition(50, size.height / 2);
	play3->setGamePosition(GP_LEFT);

	addChild(play);
	addChild(play1);
	addChild(play2);
	addChild(play3);

	m_vctPlayer.push_back(play);
	m_vctPlayer.push_back(play1);
	m_vctPlayer.push_back(play2);
	m_vctPlayer.push_back(play3);

	m_cardBack = Sprite::create(CARD_BACK);
	m_cardBack->setVisible(false);

	shuffle();
	deal();	

	return true;
}

void CardScene::shuffle()
{
	std::random_shuffle(m_vctCard.begin(), m_vctCard.end());
}

void CardScene::deal() // ·¢ÅÆ
{
	int idx(0);
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_vctPlayer.size(); j++)
		{
			m_vctPlayer[j]->addCard(m_vctCard[idx++]);
		}
	}

	/*for (int i = 0; i < m_vctPlayer.size(); i++)
	{
		m_vctPlayer[i]->finishDeal();
	}*/	
}

void CardScene::showCard()
{

}

void CardScene::OnNetData(int nReqId, Response *pResponse)
{

}