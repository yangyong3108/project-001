#ifndef __GAMEOBJCARD__
#define __GAMEOBJCARD__

#include "cocos2d.h"

enum CARD_TYPE
{
	MEIHUA = 0,
	HONGTAO,
	HEITAO,
	FANGKUAI,
	XIAOGUI,
	DAGUI,
};

class GameObjCard : public cocos2d::Node
{
public:
	GameObjCard(void);
	~GameObjCard(void);

	virtual bool init();
	virtual void onEnter();

	void setCardInfo(int nIdx, CARD_TYPE type);
	CREATE_FUNC(GameObjCard);

private:
	int m_nIdx;
	CARD_TYPE m_cardType;
};


#endif