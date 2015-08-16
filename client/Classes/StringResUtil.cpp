#include "StringResUtil.h"
#include "vld.h"

using namespace cocos2d;

StringResUtil* StringResUtil::s_instance = NULL;

StringResUtil::StringResUtil(void)
{
	if (CCApplication::sharedApplication()->getCurrentLanguage() == kLanguageChinese)
	{
		m_pValueDict = CCDictionary::createWithContentsOfFileThreadSafe("string_zh.plist");
		m_pValueDict->retain();
	}
	else if (CCApplication::sharedApplication()->getCurrentLanguage() == kLanguageEnglish)
	{
		m_pValueDict = CCDictionary::createWithContentsOfFileThreadSafe("string_en.plist");
		m_pValueDict->retain();
	}
}

StringResUtil::~StringResUtil(void)
{
	m_pValueDict->release();
}

StringResUtil* StringResUtil::instance()
{
	if (s_instance == NULL)
		s_instance = new StringResUtil;

	return s_instance;
}

const char* StringResUtil::getStringForKey(const char* szKey, const char* defaultData/* = NULL*/) const
{
	CCObject* data = m_pValueDict->objectForKey(szKey);
	if (data != NULL)
	{
		if (CCString *str = dynamic_cast<CCString*>(data))
		{
			return str->getCString();
			CCAssert(false, "Key found, but from different type");
		}
	}
	return defaultData;
}