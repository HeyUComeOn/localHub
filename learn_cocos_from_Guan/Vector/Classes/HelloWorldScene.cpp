#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::HelloWorld():ballVec(MAX_COUNT)
{

}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sp1 = Sprite::create("CloseNormal.png");
    auto sp2 = Sprite::create("CloseSelected.png");
	auto item=MenuItemSprite::create(sp1,sp2,CC_CALLBACK_0(HelloWorld::menuCloseCallback,this));
	item->setPosition(Vec2(visibleSize.width-sp2->getContentSize().width/2,sp2->getContentSize().height/2));
	auto menu = Menu::create(item,NULL);
	menu->setPosition(origin);
	addChild(menu,2000);
	//addChild(menu,2001);

	//创造球球的Vec
	for(int i = 0;i != MAX_COUNT;i++)
	{
		auto sp = Sprite::create("Ball.png");
		ballVec.pushBack(sp);
	}
	return true;
}


void HelloWorld::menuCloseCallback()
{
	log("%d",ballVec.size());
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	for(const auto& m:ballVec)  //const auto&
	{
		auto x=CCRANDOM_0_1()*(visibleSize.width);
		auto y=CCRANDOM_0_1()*(visibleSize.height);
		m->setPosition(Vec2(x,y));
		removeChild(m);// 源码有一句if (_children.empty()){return;}
		addChild(m); //上一步非常必要，因为同一个精灵不能重复添加
	}
}
