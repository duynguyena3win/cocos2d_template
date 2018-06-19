#include "PauseLayer.h"
#include "MenuItemSpriteFrame.h"

USING_NS_CC;

PauseLayer::PauseLayer()
: _func(nullptr)
, _delegate(nullptr)
{

}

PauseLayer::~PauseLayer()
{

}

PauseLayer * PauseLayer::create(const std::function<void()> &func, bool isPrepare)
{
    auto pRep = new PauseLayer();
    if (pRep && pRep->init(func, isPrepare))
    {
        pRep->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRep);
    }

    return pRep;
}


bool PauseLayer::init(const std::function<void()> &func, bool isPrepare)
{
    auto result = false;

    if (this->init(nullptr, isPrepare))
    {
        _func = func;

        result = true;
    }

    return result;
}

PauseLayer * PauseLayer::create(PauseDelegate *delegate, bool isPrepare)
{
	PauseLayer * pRep = new PauseLayer();
	if (pRep && pRep->init(delegate, isPrepare))
	{
		pRep->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRep);
	}
	
	return pRep;
}


bool PauseLayer::init(PauseDelegate * delegate, bool isPrepare)
{
    if (!ModalLayer::init())
    {
        return false;
    }
    
    _delegate = delegate;
    Size winsize = Director::getInstance()->getWinSize();
    {
        MenuItem * itemTitle = NULL;
        {
            const char * fileName = "btn_menu.png";
			auto btn = MenuItemSpriteFrame::create(fileName, fileName, CC_CALLBACK_1(PauseLayer::titleTouched, this));
            btn->setSelectedColor(Color3B::GRAY);
			itemTitle = btn;
            itemTitle->setTag(ChildTagPause_Home);
        }
        
        MenuItem * itemResume = NULL;
        {
            const char * fileName = "btn_play.png";
            auto btn = MenuItemSpriteFrame::create(fileName, fileName, CC_CALLBACK_1(PauseLayer::resumeTouched, this));
            btn->setSelectedColor(Color3B::GRAY);
            itemResume = btn;
            itemResume->setTag(ChildTagPause_Resume);
        }
        
        {
            Menu * menu = Menu::create(itemTitle, itemResume, nullptr);
            if (menu)
            {
                float ds = 15.0f;
						
                menu->alignItemsHorizontallyWithPadding(ds);
                menu->setPosition(winsize.width * 0.5f, winsize.height * 0.35f);
						
                int tagId = ChildTagPause_Menu;
                this->addChild(menu, tagId, tagId);
            }
        }
    }

    return true;
}

void PauseLayer::titleTouched(Ref * sender)
{
    if (this->getDelegate()){
        this->getDelegate()->titleTouched();
    }
}

void PauseLayer::resumeTouched(Ref * sender)
{
    if (this->getDelegate()){
        this->getDelegate()->resumeTouched();
    }
}
