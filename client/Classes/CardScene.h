#ifndef __CARD_SCENE__
#define __CARD_SCENE__

#include "cocos2d.h"
#include <vector>
#include "NetworkProxy.h"

class Player;
class CardScene : public cocos2d::Layer, public NetworkProxy
{
public:
	CardScene(void);
	~CardScene(void);

	static cocos2d::Scene* createScene();

	virtual bool init();
	void shuffle();
	void deal(); // ·¢ÅÆ
	void showCard();
	CREATE_FUNC(CardScene);
	
	virtual void OnNetData(int nReqId, Response *pResponse);

private:	
	std::vector<int>	m_vctCard;
	std::vector<Player*> m_vctPlayer;
	cocos2d::Sprite*				m_cardBack;
	
};


#endif
