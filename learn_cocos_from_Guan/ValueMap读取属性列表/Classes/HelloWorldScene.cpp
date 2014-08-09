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
	ValueMap root;
	ValueVector arry;
	
	std::string currentTime =MyUtility::getCurrentTime();
	log("%s", currentTime.c_str());

	// the first elements
	ValueMap dict;
	dict["date"]=currentTime;
	dict["content"]="the third element";
	arry.push_back(Value(dict));//the key step "Value(dict)"
	root["root"]=arry;
	
	//write the dictionary object to the plist file
	auto writepath=FileUtils::getInstance()->getWritablePath();
	auto path=writepath+"NoteList.plist";
	FileUtils::getInstance()->writeToFile(root,path);

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
	ValueMap root = FileUtils::getInstance()->getValueMapFromFile(path1);
	ValueVector arry=root["root"].asValueVector();

	ValueMap dict;
	dict["date"]="2014-08-07 21:06";
	dict["content"]="the third element";
	arry.push_back(Value(dict));//the key step "Value(dict)"
	root["root"]=arry;

	FileUtils::getInstance()->writeToFile(root,path1);

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
	ValueMap root = FileUtils::getInstance()->getValueMapFromFile(path1);
	ValueVector arry=root["root"].asValueVector();

	if (arry.size()>0)
	{
		arry.pop_back();
		root["root"]=arry;
	}

	FileUtils::getInstance()->writeToFile(root,path1);

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
	ValueMap root = FileUtils::getInstance()->getValueMapFromFile(path1);
	ValueVector arry=root["root"].asValueVector();
	for(auto& v:arry)
	{
		log("==============");
		auto dict=v.asValueMap();
		auto date=dict["date"].asString();
		auto content=dict["content"].asString();
		log("====>content:%s",content.c_str());
		log("====>date:%s",date.c_str());
	}

}
