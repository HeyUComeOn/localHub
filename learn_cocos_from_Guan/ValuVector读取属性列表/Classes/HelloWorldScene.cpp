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
	auto label1=Label::createWithBMFont("fonts/fnt8.fnt","Read Data");

	auto mnItem1=MenuItemLabel::create(label1,CC_CALLBACK_1(HelloWorld::menuCloseCallback1,this));

	auto menu=Menu::create(mnItem1,NULL);
	menu->alignItemsVerticallyWithPadding(40);
	addChild(menu);
	return true;
}


void HelloWorld::menuCloseCallback1(Ref*pSender)
{
	auto fileUtils= FileUtils::getInstance();
	string fullPath=fileUtils->fullPathForFilename("NotesList.plist");
	ValueVector arry=FileUtils::getInstance()->getValueVectorFromFile(fullPath);

	for (auto&v:arry)
	{
		log("====================");
		ValueMap row=v.asValueMap();
		string date=row["date"].asString();
		string content=row["content"].asString();
		log("======>date:%s",date.c_str());
		log("======>content:%s",content.c_str());
	}

}
