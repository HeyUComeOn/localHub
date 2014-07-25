#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ContactListener.h"
//像素与米的比例对应关系值
#define PTM_RATIO 32
class HelloWorld : public cocos2d::Layer
{
	b2World *world;
	ContactListener* contactListener;
public:

	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	virtual void update(float);

	void initPhysics();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
	void addNewSpriteAtPos(cocos2d::Vec2 pos);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


};

#endif // __HELLOWORLD_SCENE_H__
