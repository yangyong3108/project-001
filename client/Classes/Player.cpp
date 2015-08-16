#include "Player.h"
#include "vld.h"
#include "GameObjCard.h"
#include <algorithm>
#include "UserData.h"
#include "ConstUtil.h"

USING_NS_CC;

#define TAG_PHOTO	10

#define PHOTO_WIDTH	50
#define CARD_WIDTH  20

bool compare(int i, int j)
{
	int a = i % 54;
	int b = j % 54;
	if (a >= 52)
	{
		if (b < 52)
			return false;
		else
			return a < b;
	}
	else
	{
		if (b >= 52)
			return true;
		else
		{
			a = a % 13;
			b = b % 13;
			return a < b;
		}
	}
}

Player::Player(void)
	:m_gamePosition(GP_BOTTOM)
{

}

Player::~Player(void)
{

}

bool Player::init()
{
	if (!Node::init())
		return false;

	Sprite *photo = Sprite::create(BOY_IMAGE);
	photo->setTag(TAG_PHOTO);
	photo->setContentSize(Size(PHOTO_WIDTH, PHOTO_WIDTH));
	addChild(photo);

	return true;
}

void Player::addCard(int nIdx)
{
	m_vctCard.push_back(nIdx);

	if (m_nId == UserData::instance()->m_nUserId)
	{
		GameObjCard *card = GameObjCard::create();
		int nCardIdx(nIdx % 54);
		if (nCardIdx == 52)  // Ð¡¹í
			card->setCardInfo(-1, XIAOGUI);
		else if (53 == nCardIdx)
			card->setCardInfo(-1, DAGUI);
		else
		{
			int nType(nCardIdx / 13);
			nCardIdx = nCardIdx % 13;
			if (nType == 0)
				card->setCardInfo(nCardIdx, MEIHUA);
			else if (1 == nType)
				card->setCardInfo(nCardIdx, HONGTAO);
			else if (2 == nType)
				card->setCardInfo(nCardIdx, HEITAO);
			else if (3 == nType)
				card->setCardInfo(nCardIdx, FANGKUAI);
		}

		int posionX(getPositionX() - (CARD_WIDTH + (m_vctCard.size() - 1) * CARD_WIDTH + PHOTO_WIDTH) / 2);
		setPositionX(posionX);
		
		Node *pPhoto(getChildByTag(TAG_PHOTO));
		int x(PHOTO_WIDTH / 2);
		pPhoto->setPositionX(x);
		x += PHOTO_WIDTH;		

		
		card->setPositionX(x + (m_vctCard.size() - 1) * CARD_WIDTH);
		
		addChild(card);

	}
	else
	{
		Sprite *card = Sprite::create(CARD_BACK);
		if (m_gamePosition != GP_LEFT)
		{
			int posionX(getPositionX() - (CARD_WIDTH + (m_vctCard.size() - 1) * CARD_WIDTH + PHOTO_WIDTH) / 2);
			setPositionX(posionX);

			Node *pPhoto(getChildByTag(TAG_PHOTO));
			int x(PHOTO_WIDTH / 2);
			pPhoto->setPositionX(x);
			x += PHOTO_WIDTH;		


			card->setPositionX(x + (m_vctCard.size() - 1) * CARD_WIDTH);
		}
		else
		{
			card->setPositionX(getPositionX() + (m_vctCard.size() - 1) * CARD_WIDTH);
		}
		
		addChild(card);
	}
}

void Player::finishDeal()
{
	//std::sort(m_vctCard.begin(), m_vctCard.end(), compare);
	
	
	
}

int Player::points()
{
	int nPoints(0);
	for (int i = 0; i < m_vctCard.size(); i++)
	{
		nPoints += (m_vctCard[i] % 54) % 13;
	}
	return nPoints % 13;
}