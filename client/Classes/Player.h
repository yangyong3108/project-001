#ifndef __PLAYER__
#define __PLAYER__

#include "cocos2d.h"
#include <vector>
#include <string>

enum GAME_POSITON
{
	GP_LEFT = 0,
	GP_TOP,
	GP_RIGHT,
	GP_BOTTOM,
};

class Player : public cocos2d::Node
{
public:
	Player(void);
	~Player(void);

	bool init();
	void addCard(int nIdx);
	void finishDeal();
	int points();
	void setGamePosition(GAME_POSITON l) { m_gamePosition = l; }

	CREATE_FUNC(Player);

public:
	std::string			m_strName;
	int					m_nId;

private:
	std::vector<int>	m_vctCard;
	GAME_POSITON		m_gamePosition;
};

#endif