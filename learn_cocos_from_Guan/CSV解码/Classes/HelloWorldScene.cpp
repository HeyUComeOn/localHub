#include "HelloWorldScene.h"
#include "CSVParser.h"
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
	auto label1=Label::createWithBMFont("fonts/fnt8.fnt","DECODING DATA");
	/*auto label2=Label::createWithBMFont("fonts/fnt8.fnt","Insert Data");*/

	auto mnItem1=MenuItemLabel::create(label1,CC_CALLBACK_1(HelloWorld::menuCloseCallback1,this));
	/*auto mnItem2=MenuItemLabel::create(label2,CC_CALLBACK_1(HelloWorld::menuCloseCallback2,this));*/

	auto menu=Menu::create(mnItem1/*,mnItem2*/,NULL);
	menu->alignItemsVerticallyWithPadding(40);
	addChild(menu);
	return true;
}

/*
主要注意解码格式
*/
void HelloWorld::menuCloseCallback1(Ref*pSender)
{
	__Array *datas	= CSVParser::parse("Note.csv");

	for (int i = 0;	i<datas->count();	i++)
	{
		log("--------Recorder--(%d)-----",i);
		__Array *row= static_cast<__Array*>(datas->getObjectAtIndex(i));
		for(int j = 0;	j<row->count(); j++)
		{
			__String *str = static_cast<__String*>(row->getObjectAtIndex(j));
			log("%s",str->getCString());
		}
	}
}

/*
void HelloWorld::menuCloseCallback2(Ref*pSender)
{
	NoteDAO::create("2019-1-9","my insert data");
}

*/