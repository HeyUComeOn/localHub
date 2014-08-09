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
	auto label1=Label::createWithTTF("TEST RESOURCES DIR INFO","fonts/Marker Felt.ttf",48);
	auto label2=Label::createWithTTF("TEST WRITABLE INFO","fonts/Marker Felt.ttf",48);
	auto label3=Label::createWithTTF("READFILE","fonts/Marker Felt.ttf",48);
	auto label4=Label::createWithTTF("WRITEFILE","fonts/Marker Felt.ttf",48);

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
	std::string path=FileUtils::getInstance()->fullPathForFilename("test.txt");
	log("fullFilePath : %s",path.c_str());

	bool isExit =FileUtils::getInstance()->isFileExist("test.txt");
	log("isExit: %d",isExit);

}

void HelloWorld::menuCloseCallback2(Ref*pSender)
{
	std::string path =FileUtils::getInstance()->getWritablePath();
	log("writable path: %s",path.c_str());


}

void HelloWorld::menuCloseCallback3(Ref*pSender)
{
	std::string path=FileUtils::getInstance()->fullPathForFilename("test.txt");
	log("fullFilePath : %s",path.c_str());

	//��һ�ִ�ӡ��Դ�ļ����ݷ�ʽ

	Data data =FileUtils::getInstance()->getDataFromFile("test.txt");//����д��������������һ�������ǲ�֪������win32��������ƽ̨�е�ͨ��
	//Data data =FileUtils::getInstance()->getDataFromFile(path);
	std::string content1= std::string((const char*)data.getBytes(),0,data.getSize());// ��ü��Ϻ�������������Ȼ����ḽ��һϵ�з���
	log("the content1 is : %s",content1.c_str());
	
	//�ڶ��ִ�ӡ��Դ�ļ����ݷ�ʽ
	std::string content2= FileUtils::getInstance()->getStringFromFile("test.txt");
	log("the content2 is : %s",content2.c_str());

}

void HelloWorld::menuCloseCallback4(Ref*pSender)
{
	std::string writepath =FileUtils::getInstance()->getWritablePath();
	std::string filename = writepath+"writeTest.txt";//��������ڣ��ᴴ��
	char szBuf[100] ="Testing write to file.";

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
