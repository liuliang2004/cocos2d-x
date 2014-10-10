#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    //
    //// position the label on the center of the screen
    //label->setPosition(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height);
    
    //// add the label as a child to this layer
    //this->addChild(label, 1);
    auto s = Director::getInstance()->getWinSize();
     _sprite = EffectSprite::create("fish2.png");
    _sprite->setPosition(Vec2(s.width/2, s.height/2));
    addChild(_sprite);
    //// add "HelloWorld" splash screen"
    _lightsprite = Sprite::create("light.png");

    //// position the sprite on the center of the screen
    _lightsprite->setPosition3D(Vec3(s.width/2, s.height/2,50));

    //// add the sprite as a child to this layer
    this->addChild(_lightsprite);
    LabelTTF* plightLabel = LabelTTF::create("light", "Arial", 20);
    plightLabel->setPosition(Point(0,0));
    _lightsprite->addChild(plightLabel, 1);
    _pointLight = PointLight::create(Vec3(s.width/4, s.height/4*3,50), Color3B(200, 0, 0), 10000.0f);
    _pointLight->retain();
    _pointLight->setEnabled(true);
    _pointLight->setCameraMask(1);
    addChild(_pointLight);
    _lightsprite->setColor(Color3B(200, 0, 0));
    effectNormalMapped = EffectNormalMapped::create("fish2_normal.png");
    effectNormalMapped->setPointLight(_pointLight);
    _sprite->setEffect(effectNormalMapped);

    Size winSize = Director::getInstance()->getWinSize();
      _slider1 = ControlSlider::create("sliderTrack.png",
        "sliderProgress.png",
        "sliderThumb.png");
    _slider1->setAnchorPoint(Point(0.5f, 0.5f));
    _slider1->setMinimumValue(0); // Sets the min value of range
    _slider1->setMaximumValue(255); // Sets the max value of range
    _slider1->setValue(_pointLight->getDisplayedColor().r);
    _slider1->setPosition(Point(winSize.width *0.5, 180));
    _slider1->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction1), Control::EventType::VALUE_CHANGED);
    addChild(_slider1,40);
    LabelTTF* pLabel1 = LabelTTF::create("R ", "Arial", 40);
    pLabel1->setPosition(Point(_slider1->getPositionX()-_slider1->getContentSize().width/2-pLabel1->getContentSize().width/2, _slider1->getPositionY()));
    this->addChild(pLabel1, 1);
      _slider2 = ControlSlider::create("sliderTrack.png",
        "sliderProgress.png",
        "sliderThumb.png");
    _slider2->setAnchorPoint(Point(0.5f, 0.5f));
    _slider2->setMinimumValue(0); // Sets the min value of range
    _slider2->setMaximumValue(255); // Sets the max value of range
    _slider2->setValue(_pointLight->getDisplayedColor().g);
    _slider2->setPosition(Point(winSize.width *0.5, 180-40));
    _slider2->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction2), Control::EventType::VALUE_CHANGED);
    addChild(_slider2,60);
     LabelTTF* pLabel2 = LabelTTF::create("G ", "Arial", 40);
    pLabel2->setPosition(Point(_slider2->getPositionX()-_slider2->getContentSize().width/2-pLabel2->getContentSize().width/2, _slider2->getPositionY()));
    this->addChild(pLabel2, 1);

    _slider3 = ControlSlider::create("sliderTrack.png",
        "sliderProgress.png",
        "sliderThumb.png");
    _slider3->setAnchorPoint(Point(0.5f, 0.5f));
    _slider3->setMinimumValue(0); // Sets the min value of range
    _slider3->setMaximumValue(255); // Sets the max value of range
    _slider3->setValue(_pointLight->getDisplayedColor().b);
    _slider3->setPosition(Point(winSize.width *0.5, 180-80));
    _slider3->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction3), Control::EventType::VALUE_CHANGED);
    addChild(_slider3,80);
    LabelTTF* pLabel3 = LabelTTF::create("B ", "Arial", 40);
    pLabel3->setPosition(Point(_slider3->getPositionX()-_slider3->getContentSize().width/2-pLabel3->getContentSize().width/2, _slider3->getPositionY()));
    this->addChild(pLabel3, 1);

    _slider4 = ControlSlider::create("sliderTrack.png",
        "sliderProgress.png",
        "sliderThumb.png");
    _slider4->setAnchorPoint(Point(0.5f, 0.5f));
    _slider4->setMinimumValue(1); // Sets the min value of range
    _slider4->setMaximumValue(10); // Sets the max value of range
    _slider4->setValue(effectNormalMapped->getKBump());
    _slider4->setPosition(Point(winSize.width *0.5, 180-120));
    _slider4->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction4), Control::EventType::VALUE_CHANGED);
    addChild(_slider4,100);
    //title
    LabelTTF* pLabel4 = LabelTTF::create("kBump ", "Arial", 40);
    pLabel4->setPosition(Point(_slider4->getPositionX()-_slider4->getContentSize().width/2-pLabel4->getContentSize().width/2, _slider4->getPositionY()));
    this->addChild(pLabel4, 1);
     auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HelloWorld::sliderAction4(Ref* sender, Control::EventType)
{
    ControlSlider* slider = (ControlSlider*)sender;
    float value=slider->getValue();
    effectNormalMapped->setKBump(value);  
}
void HelloWorld::sliderAction1(Ref* sender, Control::EventType)
{
    ControlSlider* slider = (ControlSlider*)sender;
    float value=slider->getValue();
    Color3B color=_pointLight->getColor();
    color.r= value;
    _pointLight->updateDisplayedColor(color);  
      _lightsprite->setColor(color);
}
void HelloWorld::sliderAction2(Ref* sender, Control::EventType)
{
    ControlSlider* slider = (ControlSlider*)sender;
    float value=slider->getValue();
    Color3B color=_pointLight->getColor();
    color.g= value;
    _pointLight->setColor(color);
    _lightsprite->setColor(color);
}
void HelloWorld::sliderAction3(Ref* sender, Control::EventType)
{
    ControlSlider* slider = (ControlSlider*)sender;
    float value=slider->getValue();
    Color3B color=_pointLight->getColor();
    color.b= value;
    _pointLight->setColor(color);
    _lightsprite->setColor(color);
}
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
     Point loc_winSpace = touch->getLocationInView();
     Point loc_GLSpace = Director::getInstance()->convertToGL(loc_winSpace);
     _lightsprite->setPosition(loc_GLSpace);
    return true;
}
void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
     Point loc_winSpace = touch->getLocationInView();
     Point loc_GLSpace = Director::getInstance()->convertToGL(loc_winSpace);
        
     _lightsprite->setPosition(loc_GLSpace);
}
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
     Point loc_winSpace = touch->getLocationInView();
     Point loc_GLSpace = Director::getInstance()->convertToGL(loc_winSpace); 
    _lightsprite->setPosition(touch->getLocation());
}
void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        Point loc_winSpace = touch->getLocationInView();
        Point loc_GLSpace = Director::getInstance()->convertToGL(loc_winSpace);
        _lightsprite->setPosition(loc_GLSpace);
        _pointLight->setPosition(loc_GLSpace);
    }
}
void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        Point loc_winSpace = touch->getLocationInView();
        Point loc_GLSpace = Director::getInstance()->convertToGL(loc_winSpace);
        _lightsprite->setPosition(loc_GLSpace);
        _pointLight->setPosition(loc_GLSpace);
    }
}
void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        Point loc_winSpace = touch->getLocationInView();
        Point loc_GLSpace = Director::getInstance()->convertToGL(loc_winSpace);
        _lightsprite->setPosition(loc_GLSpace);
        _pointLight->setPosition(loc_GLSpace);
    }
}