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
	auto label1=Label::createWithTTF("Write File","fonts/Marker Felt.ttf",80);
	auto label2=Label::createWithTTF("Search File","fonts/Marker Felt.ttf",80);
	

	auto mnItem1=MenuItemLabel::create(label1,CC_CALLBACK_1(HelloWorld::menuCloseCallback1,this));
	auto mnItem2=MenuItemLabel::create(label2,CC_CALLBACK_1(HelloWorld::menuCloseCallback2,this));
	
	auto menu=Menu::create(mnItem1,mnItem2,NULL);
	menu->alignItemsVerticallyWithPadding(60);
	addChild(menu);
	return true;
}


void HelloWorld::menuCloseCallback1(Ref*pSender)
{
	std::string writepath =FileUtils::getInstance()->getWritablePath();
	std::string filename = writepath+"test.txt";//如果不存在，会创建
	char szBuf[100] ="This is in the Writable directory.";

	FILE *fp =fopen(filename.c_str(),"wb");
	if (fp)
	{
		size_t ret = fwrite(szBuf,1,strlen(szBuf),fp);
		fclose(fp);
		if (ret)
		{
			log("writing file to succeed.");
		}
	}

}

void HelloWorld::menuCloseCallback2(Ref*pSender)
{
	/*
	主要证明fileUtils->fullPathForFilename("test.txt")是有搜索路径的
	*/
	auto fileUtils=FileUtils::getInstance();
	//清理搜索路径缓存，有可能有以前的结果
	fileUtils->purgeCachedEntries();
	 std::vector<std::string> searchPaths= fileUtils->getSearchPaths();
	 std::string writablePath = fileUtils->getWritablePath();
	 searchPaths.insert(searchPaths.begin(),"dir");
	 searchPaths.insert(searchPaths.begin(),writablePath);
	 fileUtils->setSearchPaths(searchPaths);
	 std::string fullPathForFileName = fileUtils->fullPathForFilename("test.txt");
	 Data data =fileUtils->getDataFromFile(fullPathForFileName);
	 std::string content= fileUtils->getStringFromFile(fullPathForFileName);
	 log("File content is : %s",content.c_str());

}

