#include "GameScene.h"
#include "InputLayer.h"

USING_NS_CC;

static Color3B s_TouchColors[EventTouch::MAX_TOUCHES] = {
    Color3B::YELLOW,
    Color3B::BLUE,
    Color3B::GREEN,
    Color3B::RED,
    Color3B::MAGENTA
};

class TouchPoint;

static cocos2d::Map<int, TouchPoint *> s_dic;
static std::vector<int> s_array;

class TouchPoint : public Node
{
public:
    TouchPoint()
    {
        setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    }

    ~TouchPoint()
    {
    }


#ifdef DEBUG_MULTI_TAP
    virtual void draw()
    {
        const GLubyte alpha = 128;
        ccDrawColor4B(m_TouchColor.r, m_TouchColor.g, m_TouchColor.b, alpha);

        glLineWidth(10);
        ccDrawLine( ccp(0, m_pTouchPoint.y), ccp(getContentSize().width, m_pTouchPoint.y) );
        ccDrawLine( ccp(m_pTouchPoint.x, 0), ccp(m_pTouchPoint.x, getContentSize().height) );

        glLineWidth(1);
        PointSize(30);
        ccDrawPoint(m_pTouchPoint);
    }
#endif

    static TouchPoint* touchPointWithParent(Node* pParent)
    {
        TouchPoint* pRet = new TouchPoint();
        if (pRet)
        {
            pRet->setContentSize(pParent->getContentSize());
            pRet->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE(pRet);
            pRet = NULL;
        }

        return pRet;
    }

public:
    CC_SYNTHESIZE(Point, m_pTouchPoint, TouchPos);
    CC_SYNTHESIZE(Color3B, m_TouchColor, TouchColor);
};

InputLayer::InputLayer()
{
    {
        s_dic.clear();
        s_array.clear();
    }
}

InputLayer::~InputLayer()
{
}

bool InputLayer::init()
{
    bool result = false;

    do
    {
        if ( !Layer::init() )
        {
            break;
        }

        {
            Touch::DispatchMode touchMode = Touch::DispatchMode::ONE_BY_ONE;
            
            this->setTouchMode(touchMode);
            
            setTouchEnabled(true);
        }

        {
            _isTapStart = false;

            _touchStatus = TouchStatus_None;
            _movePosition = Point::ZERO;

            _touchDelegate = NULL;
        }

        return true;

    } while (0);

    return result;
}

GameScene* InputLayer::getGameScene()
{
    return dynamic_cast<GameScene *>(this->getParent()->getParent());
}

void InputLayer::setTouchStatus(cocos2d::Point touchPoint, bool isTouch)
{
    TouchStatus value = TouchStatus_None;

    if (isTouch)
    {
        Size winSize = Director::getInstance()->getWinSize();
        if (touchPoint.x <= (winSize.width * 0.5f))
        {
            value = TouchStatus_Left;
        }
        else
        {
            value = TouchStatus_Right;
        }
    }
    else
    {
        value = TouchStatus_None;
    }

    if (this->getTouchDelegate())
    {
        this->getTouchDelegate()->setTouchStatus(value);
    }

    if (this->getTouchStatus() != value)
    {
        _touchStatus = value;

        if (this->getTouchDelegate())
        {
            this->getTouchDelegate()->changeTouchStatus(value);
        }
    }
}

void InputLayer::setTouchMoved(Point touchPoint)
{
    Point positon = Point::ZERO;
    if (_movePosition.distance(Point::ZERO) != 0.0f)
    {
        positon = touchPoint - _movePosition;
    }
    _movePosition = touchPoint;

    if (_touchDelegate)
    {
        _touchDelegate->changeTouchMoved(positon);
    }
}


bool InputLayer::isInGame()
{
    bool result = false;

    do
    {
        if (!_isTapStart)
        {
            break;
        }

        GameScene * hello = getGameScene();
        if (!hello)
        {
            break;
        }

        if (!hello->getIsGameStart())
        {
            break;
        }

        if (hello->getIsGameOver())
        {
            break;
        }

        result = true;
    } while (0);

    return result;
}

bool InputLayer::onTouchBegan(Touch * pTouch, Event * pEvent)
{
    Point location = pTouch->getLocation();

    do
    {
        if (!this->isInGame())
        {
            break;
        }

        if (this->getTouchDelegate())
        {
            this->getTouchDelegate()->touchBegan(location);
        }
        
        {
            this->setTouchStatus(location);
        }
    } while (0);

    return true;
}


void InputLayer::onTouchMoved(Touch * pTouch, Event * pEvent)
{
    Point location = pTouch->getLocation();

    do
    {
        if (!this->isInGame())
        {
            break;
        }

        if (this->getTouchDelegate())
        {
            this->getTouchDelegate()->touchMoved(location);
        }

        {
            this->setTouchStatus(location);
            this->setTouchMoved(location);
        }
    } while (0);
}


void InputLayer::onTouchEnded(Touch * pTouch, Event * pEvent)
{
    Point location = pTouch->getLocation();

    do
    {
        if (!this->isInGame())
        {
            if (_isTapStart)
            {
                break;
            }

            GameScene * hello = getGameScene();
            if (hello)
            {
                _isTapStart = true;

                hello->gameStart();
            }

            break;
        }

        if (this->getTouchDelegate())
        {
            this->getTouchDelegate()->touchEnded(location);
        }

        {
            this->setTouchStatus(location, false);
        }
    } while (0);
}

void InputLayer::onTouchesBegan(const std::vector<cocos2d::Touch *> &pTouches, cocos2d::Event *pEvent)
{
    do
    {
        if (!this->isInGame())
        {
            break;
        }

        if (this->getTouchDelegate())
        {
            this->getTouchDelegate()->touchesBegan(pTouches, pEvent);
        }

        {
            auto iter = pTouches.begin();
            for (; iter != pTouches.end(); iter++)
            {
                Touch* pTouch = (*iter);
                Point location = pTouch->getLocation();

                {
                    const int touchId = pTouch->getID();
                    TouchPoint* pTouchPoint = TouchPoint::touchPointWithParent(this);

                    pTouchPoint->setTouchPos(location);
                    pTouchPoint->setTouchColor(s_TouchColors[ touchId ]);

                    this->addChild(pTouchPoint, ChildTagDebug);

                    s_dic.insert(touchId, pTouchPoint);
                    s_array.push_back(touchId);
                }
            }

            if (s_array.size() > 0)
            {
                int value = s_array.back();
                TouchPoint* pTouch = s_dic.at(value);
                if (pTouch)
                {
                    Point position = pTouch->getTouchPos();
                    
                    if (this->getTouchDelegate())
                    {
                        this->getTouchDelegate()->touchBegan(position);
                    }
                    
                    {
                        this->setTouchStatus(position);
                    }
                }
            }
        }
    } while (0);
}


void InputLayer::onTouchesMoved(const std::vector<cocos2d::Touch *> &pTouches, cocos2d::Event *pEvent)
{
    do
    {
        if (!this->isInGame())
        {
            break;
        }

        if (this->getTouchDelegate())
        {
            this->getTouchDelegate()->touchesMoved(pTouches, pEvent);
        }

        {
            for (auto iter = pTouches.begin(); iter != pTouches.end(); iter++)
            {
                Touch* pTouch = (*iter);
                TouchPoint* pTP = s_dic.at(pTouch->getID());
                if (!pTP)
                {
                    continue;
                }

                Point location = pTouch->getLocation();
                Point delta = Point::ZERO;
                {
                    Point oldPos = pTP->getTouchPos();
                    delta  = location - oldPos;
                }

                pTP->setTouchPos(location);
            }

            if (s_array.size() > 0)
            {
                int value = s_array.back();
                TouchPoint* pTouch = s_dic.at(value);
                if (pTouch)
                {
                    Point position = pTouch->getTouchPos();
                    
                    if (this->getTouchDelegate())
                    {
                        this->getTouchDelegate()->touchMoved(position);
                    }
                    
                    {
                        this->setTouchStatus(position);
                        this->setTouchMoved(position);
                    }
                }
            }
        }
    } while (0);
}

void InputLayer::onTouchesEnded(const std::vector<cocos2d::Touch *> &pTouches, cocos2d::Event *pEvent)
{
    do
    {
        if (!this->isInGame())
        {
            if (_isTapStart)
            {
                break;
            }

            GameScene * hello = getGameScene();
            if (hello)
            {
                _isTapStart = true;

                hello->gameStart();
            }

            break;
        }

        if (this->getTouchDelegate())
        {
            this->getTouchDelegate()->touchesEnded(pTouches, pEvent);
        }

        int lastTouchId = -1;
        if (s_array.size() > 0)
        {
            int value = s_array.back();
            lastTouchId = value;
        }

        Point lastTouchPos = Point::ZERO;

        {
            for (auto iter = pTouches.begin(); iter != pTouches.end(); iter++)
            {
                Touch* pTouch = (*iter);
                const int touchId = pTouch->getID();

                TouchPoint* pTP = s_dic.at(touchId);
                if (!pTP)
                {
                    continue;
                }

                if (touchId == lastTouchId)
                {
                    lastTouchPos = pTP->getTouchPos();
                }


                removeChild(pTP, true);
                s_dic.erase(touchId);

                {
                    for (auto iterator = s_array.begin(); iterator != s_array.end(); iterator ++){
                        int tID = *iterator;
                        if (tID == touchId)
                        {
                            s_array.erase(iterator);
                            break;
                        }
                    }
                }
            }
        }

        {
            if (s_dic.size() <= 0)
            {
                s_array.clear();
            }

            bool isMessage = false;
            if (s_array.size() > 0)
            {
                int value = s_array.back();
                TouchPoint* pTouch = s_dic.at(value);
                if (pTouch)
                {
                    Point position = pTouch->getTouchPos();
                    
                    if (this->getTouchDelegate())
                    {
                        this->getTouchDelegate()->touchBegan(position);
                    }
                    
                    {
                        this->setTouchStatus(position);
                    }
                    
                    isMessage = true;
                }
            }

            if (!isMessage)
            {
                Point position = lastTouchPos;

                if (this->getTouchDelegate())
                {
                    this->getTouchDelegate()->touchEnded(position);
                }

                {
                    this->setTouchStatus(position, false);
                }
            }
        }

    } while (0);
}

void InputLayer::onTouchesCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *pEvent)
{

}
