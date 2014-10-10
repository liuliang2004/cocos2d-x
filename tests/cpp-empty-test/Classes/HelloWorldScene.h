#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "EffectSprite.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
    void sliderAction4(Ref* sender, Control::EventType);
    void sliderAction1(Ref* sender, Control::EventType);
    void sliderAction2(Ref* sender, Control::EventType);
    void sliderAction3(Ref* sender, Control::EventType);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    EffectSprite*  _sprite;
    PointLight*    _pointLight; 
    Sprite*        _lightsprite;
    ControlSlider* _slider1;
    ControlSlider* _slider2;
    ControlSlider* _slider3;
    ControlSlider* _slider4;
    EffectNormalMapped*  effectNormalMapped;
};

#endif // __HELLOWORLD_SCENE_H__
