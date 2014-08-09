#include "HelloWorldScene.h"
#include "NoteDAO.h"
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
	auto label1=Label::createWithBMFont("fonts/fnt8.fnt","init DataBase");
	auto label2=Label::createWithBMFont("fonts/fnt8.fnt","Insert Data");
	auto label3=Label::createWithBMFont("fonts/fnt8.fnt","Delete Data");
	auto label4=Label::createWithBMFont("fonts/fnt8.fnt","Read data");
	auto label5=Label::createWithBMFont("fonts/fnt8.fnt","Modify data");

	auto mnItem1=MenuItemLabel::create(label1,CC_CALLBACK_1(HelloWorld::menuCloseCallback1,this));
	auto mnItem2=MenuItemLabel::create(label2,CC_CALLBACK_1(HelloWorld::menuCloseCallback2,this));
	auto mnItem3=MenuItemLabel::create(label3,CC_CALLBACK_1(HelloWorld::menuCloseCallback3,this));
	auto mnItem4=MenuItemLabel::create(label4,CC_CALLBACK_1(HelloWorld::menuCloseCallback4,this));
	auto mnItem5=MenuItemLabel::create(label5,CC_CALLBACK_1(HelloWorld::menuCloseCallback5,this));

	auto menu=Menu::create(mnItem1,mnItem2,mnItem3,mnItem4,mnItem5,NULL);
	menu->alignItemsVerticallyWithPadding(40);
	addChild(menu);
	return true;
}


void HelloWorld::menuCloseCallback1(Ref*pSender)
{
	NoteDAO::initDB();
}

void HelloWorld::menuCloseCallback2(Ref*pSender)
{
	NoteDAO::create("2019-1-9","my insert data");
}

void HelloWorld::menuCloseCallback3(Ref*pSender)
{
	
	NoteDAO::remove("2019-1-9");
}

void HelloWorld::menuCloseCallback4(Ref*pSender)
{
	
	auto ary=NoteDAO::findAll();
	for (auto& v:ary)
	{
		log("-----------");
		ValueMap row = v.asValueMap();
		log("====>date::%s",row["date"].asString().c_str());
		log("====>content::%s",row["content"].asString().c_str());
	}
	
}

void HelloWorld::menuCloseCallback5(Ref*pSender)
{

	NoteDAO::modify("2019-1-9","my insert data222");
}
