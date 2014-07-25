#include "HelloWorldScene.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	auto sp1=Sprite::create("BoxA2.png");
	auto body1=PhysicsBody::createBox(sp1->getContentSize());

	sp1->setPhysicsBody(body1);
	sp1->setPosition(pos);
	sp1->setTag(Tag);
	this->addChild(sp1);

	auto sp2=Sprite::create("BoxB2.png");
	auto body2=PhysicsBody::createBox(sp2->getContentSize());

	sp2->setPhysicsBody(body2);
	sp2->setPosition(pos+Vec2(-10,100));
	sp2->setTag(Tag);
	this->addChild(sp2);

	auto joint=PhysicsJointDistance::construct(body1,body2,Vec2(0,0),Vec2(0,sp2->getContentSize().height/2));
	auto world=this->getScene()->getPhysicsWorld();
	world->addJoint(joint);
}

