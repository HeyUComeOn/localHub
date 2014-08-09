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
	auto label1=Label::createWithBMFont("fonts/fnt8.fnt","init plist");
	auto label2=Label::createWithBMFont("fonts/fnt8.fnt","Insert Data");
	auto label3=Label::createWithBMFont("fonts/fnt8.fnt","Delete Data");
	auto label4=Label::createWithBMFont("fonts/fnt8.fnt","Read data");

	auto mnItem1=MenuItemLabel::create(label1,CC_CALLBACK_1(HelloWorld::menuCloseCallback1,this));
	auto mnItem2=MenuItemLabel::create(label2,CC_CALLBACK_1(HelloWorld::menuCloseCallback2,this));
	auto mnItem3=MenuItemLabel::create(label3,CC_CALLBACK_1(HelloWorld::menuCloseCallback3,this));
	auto mnItem4=MenuItemLabel::create(label4,CC_CALLBACK_1(HelloWorld::menuCloseCallback4,this));
	auto menu=Menu::create(mnItem1,mnItem2,mnItem3,mnItem4,NULL);
	menu->alignItemsVerticallyWithPadding(40);
	addChild(menu);
	return true;
}


void HelloWorld::menuCloseCallback1(Ref*pSender)
{
	auto root = __Dictionary::create();
	auto arry = __Array::create();
	//auto dict = __Dictionary::create();
	std::string currentTime =MyUtility::getCurrentTime();
	log("%s", currentTime.c_str());

	// the first elements
	auto dict = __Dictionary::create();
	dict->setObject(__String::create(currentTime), "date");
	dict->setObject(__String::create("the third element"), "content");
	arry->addObject(dict);
	root->setObject(arry,"root");
	
	//write the dictionary object to the plist file
	auto writepath=FileUtils::getInstance()->getWritablePath();
	auto path=writepath+"NoteList.plist";
	if(root->writeToFile(path.c_str()))
	{
		log("Succeed.");
	}
	else
	{
		log("false.");
	}

}

void HelloWorld::menuCloseCallback2(Ref*pSender)
{
	auto writepath1=FileUtils::getInstance()->getWritablePath();
	auto path1=writepath1+"NoteList.plist";
	bool isExit=FileUtils::getInstance()->isFileExist(path1);
	if(!isExit)
	{
		log("NoteList.plist doesn't exit.");
	}
	auto root = __Dictionary::createWithContentsOfFile(path1.c_str());
	auto arry = static_cast<__Array*>(root->objectForKey("root"));
	//auto dict = __Dictionary::create();
	std::string currentTime =MyUtility::getCurrentTime();
	//log("%s", currentTime.c_str());

	// the first elements
	auto dict = __Dictionary::create();
	dict->setObject(__String::create(currentTime), "date");
	dict->setObject(__String::create("第三个元素"), "content");
	arry->addObject(dict);
	//root->setObject(arry,"root");

	//write the dictionary object to the plist file
	auto writepath=FileUtils::getInstance()->getWritablePath();
	auto path=writepath+"NoteList.plist";
	if(root->writeToFile(path.c_str()))
	{
		log("Succeed.");
	}
	else
	{
		log("false.");
	}

}

void HelloWorld::menuCloseCallback3(Ref*pSender)
{
	auto writepath1=FileUtils::getInstance()->getWritablePath();
	auto path1=writepath1+"NoteList.plist";
	bool isExit=FileUtils::getInstance()->isFileExist(path1);
	if(!isExit)
	{
		log("NoteList.plist doesn't exit.");
	}
	auto root = __Dictionary::createWithContentsOfFile(path1.c_str());
	auto arry = static_cast<__Array*>(root->objectForKey("root"));
	if(arry->count()>0)
	{
		arry->removeLastObject();
	}
	auto writepath=FileUtils::getInstance()->getWritablePath();
	auto path=writepath+"NoteList.plist";
	if(root->writeToFile(path.c_str()))
	{
		log("Succeed.");
	}
	else
	{
		log("false.");
	}

}

void HelloWorld::menuCloseCallback4(Ref*pSender)
{
	auto writepath1=FileUtils::getInstance()->getWritablePath();
	auto path1=writepath1+"NoteList.plist";
	bool isExit=FileUtils::getInstance()->isFileExist(path1);
	if(!isExit)
	{
		log("NoteList.plist doesn't exit.");
	}
	auto root = __Dictionary::createWithContentsOfFile(path1.c_str());
	auto arry = static_cast<__Array*>(root->objectForKey("root"));
	Ref* obj=nullptr;
	CCARRAY_FOREACH(arry,obj)
	{
		log("==============");
		auto dict=static_cast<__Dictionary*>(obj);
		auto date=static_cast<__String*>(dict->objectForKey("date"));
		auto content=static_cast<__String*>(dict->objectForKey("content"));
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
		{
			auto output=MyUtility::gbk_2_utf8(content->getCString());
			log("====>content:%s",output);
		} 
#else
		{
			log("====>content:%s",content->getCString());
		}
#endif
		log("====>date:%s",date->getCString());
	}

}
