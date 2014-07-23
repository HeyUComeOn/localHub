#include "HelloWorldScene.h"

USING_NS_CC;
using namespace ui;

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

	auto sp=Sprite::create("HelloWorld.png");
	sp->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(sp);

	auto text=Text::create();
	text->setColor(Color3B(255,255,0));
	text->setFontSize(60);
	text->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+150));
	text->setFontName("Marker Felt.ttf");
	text->setText("The First");
	addChild(text);

	auto atlas =TextAtlas::create();
	atlas->setProperty("0123456789","fonts/labelatlas.png",16,20,".");
	atlas->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+200));
	atlas->setScale(3);
	addChild(atlas);

	auto bmFont=TextBMFont::create();
	bmFont->setFntFile("fonts/bm01.fnt");
	bmFont->setText("WCT");
	bmFont->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-150));
	addChild(bmFont);




	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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

void HelloWorld::touchLabelCallback(Ref*pSender)
{
	auto node=static_cast<MenuItemLabel*>(pSender);
	auto label=dynamic_cast<LabelProtocol*>(node->getLabel());

	log("%s",label->getString().c_str());
}

