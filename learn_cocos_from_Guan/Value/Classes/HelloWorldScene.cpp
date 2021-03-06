#include "HelloWorldScene.h"

USING_NS_CC;

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
	return true;
}


void HelloWorld::menuCloseCallback()
{
	Value v1;
	CCASSERT(v1.isNull(),"");

	Value v2(100);
	log("The description of the integer value:%s",v2.getDescription().c_str());
	log("v2.asByte()=%c",v2.asByte());

	Value v3(104.1f);
	log("The description of the float value:%s",v3.getDescription().c_str());

	Value v4(104.1);
	log("The description of the double value:%s",v4.getDescription().c_str());
	log("v4.asInt():%d",v4.asInt());

	unsigned char by= 50;
	Value v5(by);
	log("The description of the byte value:%s",v5.getDescription().c_str());

	Value v6(true);
	log("The description of the Boolean value:%s",v6.getDescription().c_str());

	Value v7("123");
	log("The description of the string value:%s",v7.getDescription().c_str());
	log("v7.asInt():%d",v7.asInt());
}
