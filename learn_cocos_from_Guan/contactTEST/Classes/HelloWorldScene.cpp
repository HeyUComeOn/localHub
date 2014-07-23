#include "HelloWorldScene.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

    auto body=PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,5.0f);
	auto edgeNode=Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	
	this->setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//
    return true;
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto p=touch->getLocation();
	addNewSpriteAtPos(p);
	return true;
}

void HelloWorld::addNewSpriteAtPos(Vec2 pos)
{
	auto sp=Sprite::create("BoxA2.png");
	auto body=PhysicsBody::createBox(sp->getContentSize());
	//�Ƿ������ײ��⣬bitmask���룬������С�λ�롱���㣬�������Ƿ��㣬
	//���������������ײ����������ײ��Ĭ����0x0
	body->setContactTestBitmask(0x1);

	//��С�������������е������
	sp->setPhysicsBody(body);
	sp->setPosition(pos);
	sp->setTag(Tag);
	this->addChild(sp);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	listener=EventListenerPhysicsContact::create();
	
	listener->onContactBegin=[](PhysicsContact&connect)
	{
		log("onContactBegin");
		auto spA=static_cast<Sprite*>(connect.getShapeA()->getBody()->getNode());
		auto spB=static_cast<Sprite*>(connect.getShapeB()->getBody()->getNode());
		if (spA && spA->getTag()==Tag &&
			spB && spB->getTag()==Tag)
		{
			spA->setColor(Color3B::GREEN);
			spB->setColor(Color3B::GREEN);
		}
		
		return true;
	};

	listener->onContactPreSolve=[](PhysicsContact&connect,PhysicsContactPreSolve&solve)
	{
		log("onContactPreSolve");
		return true;
	};

	listener->onContactPostSolve=[](PhysicsContact&connect,const PhysicsContactPostSolve&solve)
	{
		log("onContactPostSolve");
	};

	listener->onContactSeperate=[](PhysicsContact&connect)
	{
		log("onContactSeperate");
		auto spA=static_cast<Sprite*>(connect.getShapeA()->getBody()->getNode());
		auto spB=static_cast<Sprite*>(connect.getShapeB()->getBody()->getNode());
		if (spA && spA->getTag()==Tag &&
			spB && spB->getTag()==Tag)
		{
			spA->setColor(Color3B::WHITE);
			spB->setColor(Color3B::WHITE);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);
}

void HelloWorld::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}