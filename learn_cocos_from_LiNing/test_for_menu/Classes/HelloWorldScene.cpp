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

	auto sp=Sprite::create("HelloWorld.png");
	sp->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(sp);
	auto ttfLabel=Label::createWithTTF("fonts/Marker Felt.ttf","fonts/Marker Felt.ttf",40);
	//ttfLabel->setPosition(200,220);
	//addChild(ttfLabel);
	auto bmLabel=Label::createWithBMFont("fonts/bm01.fnt","Touh me");
	//bmLabel->setPosition(visibleSize.width/2,visibleSize.height/2);
	bmLabel->setScale(2);
	//addChild(bmLabel);

	//×ÖÌå±êÇ©
	MenuItemFont::create("fonts/bm01.fnt");
	auto fontitem=MenuItemFont::create("MenuitemFont",CC_CALLBACK_1(HelloWorld::touchLabelCallback,this));
	fontitem->setFontSizeObj(80);
	auto menuitem1=MenuItemLabel::create(bmLabel,CC_CALLBACK_1(HelloWorld::touchLabelCallback,this));
	auto menuitem2=MenuItemLabel::create(ttfLabel,CC_CALLBACK_1(HelloWorld::touchLabelCallback,this));
	Sprite* sp1=Sprite::create("CloseNormal.png");
	auto sp2=Sprite::create("CloseSelected.png");
	auto spriteItem=MenuItemSprite::create(sp1,sp2);
	auto sprite3=MenuItemImage::create("CloseNormal.png","CloseSelected.png");
	sprite3->setPosition(Vec2(110,105));
	menuitem1->setPosition(visibleSize.width/2,visibleSize.height/2);
	menuitem2->setPosition(visibleSize.width/2,visibleSize.height/2-100);
	fontitem->setPosition(visibleSize.width/2,visibleSize.height/2+100);
	spriteItem->setPosition(visibleSize.width/2,visibleSize.height/2-200);

	//toggle
	
	auto t1=MenuItemFont::create("Yes");
	auto t2=MenuItemFont::create("No");
	auto toggle=MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::toggleDown,this),t1,t2,NULL);
	toggle->setPosition(100,300);
	toggle->setTag(32);
	auto menu=Menu::create(menuitem1,menuitem2,fontitem,spriteItem,sprite3,toggle,NULL);
	menu->setPosition(0,0);
	addChild(menu);
	
	
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

void HelloWorld::toggleDown(Ref*pSender)
{
	auto node=static_cast<MenuItemToggle*>(pSender);
	switch (node->getSelectedIndex())
	{
	case 0:
			log("%s","Yes");
		break;
	case 1:
		log("%s","No");
	default:
		break;
	}
}