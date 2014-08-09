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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("run.plist");
	auto goSp=Sprite::createWithSpriteFrameName("go.png");
	auto stopSp=Sprite::createWithSpriteFrameName("stop.png");
	auto goItem=MenuItemSprite::create(goSp,goSp);
	auto stopItem=MenuItemSprite::create(stopSp,stopSp);
	auto toggle=MenuItemToggle::createWithCallback(CC_CALLBACK_0(HelloWorld::toggleCallback,this),
		goItem,
		stopItem,
		NULL);
	toggle->setPosition(Vec2(visibleSize.width/2,origin.y+100));
	auto menu=Menu::create(toggle,NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu,100);
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::createWithSpriteFrameName("background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	//animation
	auto animation=Animation::create();
	for(int i=1;i!=5;i++)
	{
		auto s=__String::createWithFormat("h%d.png",i);
		auto spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		animation->addSpriteFrame(spf);
	}
	animation->setDelayPerUnit(0.15f);
	animation->setLoops(-1);
	//animation->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(animation,"ani");

	hero=Sprite::createWithSpriteFrameName("h1.png");
	hero->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	addChild(hero,2);

    isPlaying=false;
    return true;
}

void HelloWorld::toggleCallback()
{
	if (!isPlaying)
	{
		auto animate=Animate::create(AnimationCache::getInstance()->animationByName("ani"));
		auto move=MoveBy::create(1.5f,Vec2(100,100));
		auto sq=Spawn::create(animate,Repeat::create(move,5),NULL);
		hero->runAction(sq);
		isPlaying=true;
	} 
	else
	{
		hero->stopAllActions();
		isPlaying=false;
	}
	
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
