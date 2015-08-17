#include "LoginScene.h"
#include "StringResUtil.h"
#include "TcpClient.h"
#include "Global.h"
#include "CardScene.h"

extern CGlobal G;

#define REQ_LOGIN	1001

Scene* LoginScene::createScene()
{
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

LoginScene::LoginScene(void)
{

}


LoginScene::~LoginScene(void)
{

}

bool LoginScene::init()
{
	if (!Layer::init())
		return false;
	Size winSize = Director::getInstance()->getWinSize();

	auto pBckSprite = Scale9Sprite::create("green_edit.png");
	addChild(pBckSprite);
	pBckSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 25));
	pBckSprite->setContentSize(Size(winSize.width / 2, 35));

	m_txtUserName = ui::TextField::create(StringResUtil::instance()->getStringForKey("username"), "Arial",30);
	
	m_txtUserName->setPlaceHolderColor(Color4B::WHITE);
	m_txtUserName->setTextColor(Color4B::WHITE);
	addChild(m_txtUserName);
	m_txtUserName->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 25));

	auto pPwdBckSprite = Scale9Sprite::create("green_edit.png");
	addChild(pPwdBckSprite);
	pPwdBckSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 25));
	pPwdBckSprite->setContentSize(Size(winSize.width / 2, 35));

	m_txtPassword = ui::TextField::create(StringResUtil::instance()->getStringForKey("password"), "Arial",30);
	m_txtPassword->setPlaceHolderColor(Color4B::WHITE);
	m_txtPassword->setTextColor(Color4B::WHITE);
	m_txtPassword->setPasswordEnabled(true);
	addChild(m_txtPassword);
	m_txtPassword->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 25));

	/*auto starMenuItem = MenuItemImage::create(
		"button.png",
		"button.png", CC_CALLBACK_1(LoginScene::starMenuCallback, this));
	starMenuItem->setPosition(Point::ZERO);
	starMenuItem->setContentSize(Size(80, 30));
	auto starMenu = Menu::create(starMenuItem, NULL);
	starMenu->setPosition(Point(winSize.width / 2, winSize.height / 2 - 80));
	this->addChild(starMenu, 1);*/

	LabelTTF *label = LabelTTF::create("login", "Marker Felt", 30);
	Scale9Sprite *normalBck = Scale9Sprite::create("button.png");
	ControlButton *button = ControlButton::create(label, normalBck);
	button->setContentSize(Size(80, 30));
	button->setPosition(Point(winSize.width / 2, winSize.height / 2 - 80));
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(LoginScene::touchDown), Control::EventType::TOUCH_DOWN);
	addChild(button);
	return true;
}

void LoginScene::starMenuCallback(Object* pSender)
{

}

void LoginScene::touchDown(Ref* pSender, Control::EventType type)
{
	G.m_strUserName = m_txtUserName->getString();
	G.m_strPassword = m_txtPassword->getString();
	
	if (G.m_nStatus & STATUS_CONNECTED)
	{		
		TcpClient::instance()->requestLogin();
	}
	else
	{

	}

}

void LoginScene::OnNetData(int nReqId, Response *pResponse)
{
	if (nReqId == REQ_LOGIN)
	{
		if (pResponse->response_code() == OK)
		{			
			G.m_nStatus = STATUS_AUTHED;
			for (int idx = 0; idx < pResponse->data_size(); idx++)
			{
				card_protobuf::Data crdata = pResponse->data(idx);
				ProtobufResponseData pbrd;

				if (idx == 0)
				{
					if(crdata.type() == PROTOBUF)
					{
						if (!pbrd.ParseFromString(crdata.value()))
							continue;
					}
					else
						continue;

					for(int i = 0; i < pbrd.rowvalue_size(); i++)
					{
						RowValue rowValue = pbrd.rowvalue(i);
						for(int j = 0; j < rowValue.columnvalue_size(); j++)
						{
							RowValue_ColumnValue columnValue = rowValue.columnvalue(j);
							if (pbrd.columninfo(j).name() == "money")
							{

							}
							else if (pbrd.columninfo(j).name() == "username")
							{
								G.m_strUserName = columnValue.stringvalue();
							}
							else if (pbrd.columninfo(j).name() == "userid")
							{
								G.m_strUserId = columnValue.stringvalue();
							}
						}
					}
				}
			}

			auto scene = CardScene::createScene();
			cocos2d::Director::getInstance()->replaceScene(scene);
		}
		else
		{

		}
	}
}

//  不断监视G.status 查看状态
void LoginScene::update(float fDelta)
{

}