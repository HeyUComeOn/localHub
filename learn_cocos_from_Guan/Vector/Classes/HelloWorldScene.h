#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#define MAX_COUNT 50

class HelloWorld : public cocos2d::Layer
{
	cocos2d::Vector<cocos2d::Sprite*> ballVec;//成员不能在此处初始化
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	HelloWorld();
};

#endif // __HELLOWORLD_SCENE_H__
