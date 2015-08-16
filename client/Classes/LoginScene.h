#ifndef __LOGINSCENE__
#define __LOGINSCENE__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "NetworkProxy.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginScene : public cocos2d::Layer, public TextFieldDelegate, public NetworkProxy
{
public:
	LoginScene(void);
	~LoginScene(void);

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoginScene);

	 /**
    @brief    If the sender doesn't want to attach to the IME, return true;
    */
	virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief    If the sender doesn't want to detach from the IME, return true;
    */
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

	void starMenuCallback(Object* pSender);

	void touchDown(Ref* pSender, Control::EventType type);

	virtual void OnNetData(int nReqId, Response *pResponse);

private:
	ui::TextField* m_txtUserName;
	ui::TextField* m_txtPassword;
};

#endif