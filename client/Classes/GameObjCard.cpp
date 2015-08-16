#include "GameObjCard.h"
#include "ConstUtil.h"
#include "vld.h"

USING_NS_CC;

#define OFFSET_Y		17
#define OFFSET_X		9

GameObjCard::GameObjCard(void)
	:m_nIdx(0)
	,m_cardType(MEIHUA)
{
}

GameObjCard::~GameObjCard(void)
{
}

bool GameObjCard::init()
{
	if (!Node::init())
		return false;
	
	return true;
}

void GameObjCard::onEnter()
{
	Node::onEnter();
	
}

void GameObjCard::setCardInfo(int nIdx, CARD_TYPE type) 
{ 
	m_nIdx = nIdx;
	m_cardType = type; 

	int y(0);
	switch (m_cardType)
	{
	default:
		break;
	case FANGKUAI:
		y = 0;
		break;
	case MEIHUA:
		y = CARD_HEIGHT + OFFSET_Y;
		break;
	case HONGTAO:
		y = 2 * (CARD_HEIGHT + OFFSET_Y);
		break;
	case HEITAO:
		y = 3 * (CARD_HEIGHT + OFFSET_Y);
		break;
	}
	int x(m_nIdx * (CARD_WIDTH + OFFSET_X));
	auto card = Sprite::create(CARD_IMAGE, Rect(x, y, CARD_WIDTH, CARD_HEIGHT));
	card->setTag(0);
	addChild(card);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event *event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Rect rect(0, 0, target->getContentSize().width, target->getContentSize().height);

		if (rect.containsPoint(target->convertToNodeSpace(touch->getLocation())))
		{
			return true;
		}
		return false;
	};
	listener->onTouchEnded = [](Touch* touch, Event *event)
	{
		auto target = (Sprite*)event->getCurrentTarget();
		int y(0);
		if (target->getTag() == 1)
		{
			target->setTag(0);
			y = -10;
		}
		else
		{
			target->setTag(1);
			y = 10;
		}
		target->runAction(MoveBy::create(0.5, Vec2(0, y)));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, card);
}